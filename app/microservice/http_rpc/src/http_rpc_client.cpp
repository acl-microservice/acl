#include "http_rpc.h"
#include "nameserver_proto.h"
#include "nameserver_proto.gson.h"

namespace acl
{
	char * var_confg_nameserver_register_find_service;

	int var_confg_rpc_conn_check_inter;
	int var_confg_rpc_conn_check_timeout;

	http_rpc_client::http_rpc_client()
	{
		init();
	}

	void http_rpc_client::init()
	{
		int  cocurrent = 100, 
			conn_timeout = 100, 
			rw_timeout = 200;

		// 创建 HTTP 请求连接池集群管理对象
		conn_manager_ = new http_request_manager();


		connect_monitor* monitor = new connect_monitor(*conn_manager_);

		(*monitor).
			set_check_inter(var_confg_rpc_conn_check_inter).
			set_conn_timeout(var_confg_rpc_conn_check_timeout);

		// 启动后台检测线程
		conn_manager_->start_monitor(monitor);
	}

	http_rpc_client::status_t 
		http_rpc_client::invoke_http_req(const string &service_name,
		const char *context_type,
		const string&req_data,
		string &resp_buffer)
	{
		status_t status;
		std::vector<connect_pool*> pools;

		if (!get_connect_pool(service_name, pools))
			return status_t(-1,
				string("get_connect_pool2 failed: ") += service_name);

		for (size_t i = 0; i < pools.size(); i++)
		{
			status = invoke_http_req(service_name,
				(http_request_pool*)pools[i],
				req_data,
				APPLICATION_JSON,
				resp_buffer);

			if (status)
				break;
		}
		return status;
	}
	http_rpc_client::status_t  
	http_rpc_client::invoke_http_req(
			const string &http_path, 
			http_request_pool *pool, 
			const char *context_type, 
			const string&req_data,
			string &resp_buffer)
	{

		// 从连接池中获取一个 HTTP 连接
		connect_guard _connect_guard(*pool);
		http_request* conn = (http_request*)_connect_guard.peek();

		if (conn == NULL)
		{
			logger_error("peek connect failed from %s",pool->get_addr());

			return status_t(-1, string("peek connect "
				"failed from :") += pool->get_addr());
		}

		// 需要对获得的连接重置状态，以清除上次请求过程的临时数据
		else
			conn->reset();

		conn->request_header().
			set_url(http_path).
			set_content_type(context_type).
			set_keep_alive(true);

		if (!conn->request(req_data.c_str(), req_data.size()))
		{
			logger_error("http_request failed");
			_connect_guard.set_keep(false);

			return status_t(-1, "http_request failed");
		}
		resp_buffer.clear();
		char  buf[8192];
		int   ret = 0;
		// 接收 HTTP 响应体数据
		long long body_len = conn->body_length();
		while (true)
		{
			ret = conn->read_body(buf, sizeof(buf));
			if (ret == 0)
				break;
			else if (ret < 0)
			{
				_connect_guard.set_keep(false);

				logger_error("http_request read_body error");
				
				return status_t(-1, "http_request read_body error");
			}
			resp_buffer.append(buf, ret);
		}
		if (conn->http_status() != 200)
		{
			status_t retval(conn->http_status(), resp_buffer);
			return retval;
		}

		return status_t();
	}

	bool http_rpc_client::find_connect_pool(const string &service_name, 
		std::vector<connect_pool*> &pools)
	{

		lock_guard guard(service_addrs_locker_);
		
		http_rpc_service_info *info = service_addrs_[service_name];
		if (info == NULL)
		{
			logger_error("not nameservice addr: %s",
				var_confg_nameserver_register_find_service);
			return false;
		}

		for (size_t i = 0; i < info->addrs_.size(); i++)
		{
			size_t index = ++info->index_%info->addrs_.size();
			string addr = info->addrs_[index];
			connect_pool *pool = conn_manager_->get(addr.c_str());
			if (pool && pool->aliving())
				pools.push_back(pool);
		}
		return !pools.empty();
	}

	bool http_rpc_client::get_connect_pool(const string &service_name,
		std::vector<connect_pool*> &pools)
	{
		if (!find_connect_pool(service_name, pools))
		{
			std::vector<string> addrs;
			if (rpc_find_service_addr(service_name, addrs))
			{
				add_service_addr(service_name, addrs);
				return find_connect_pool(service_name, pools);
			}
		}
		return false;
	}

	bool http_rpc_client::rpc_find_service_addr(
		const string &service_name,
		std::vector<string> &addrs)
	{
	
		std::vector<connect_pool* >pools;
		if (!find_connect_pool(
			var_confg_nameserver_register_find_service, 
			pools))
			return false;

		nameserver_proto::find_service_req req;
		nameserver_proto::find_service_resp resp;

		//发起rpc 请求 服务信息
		string buffer;

		for (size_t i = 0; i < pools.size() ; i++)
		{
			status_t ret = invoke_http_req(
				var_confg_nameserver_register_find_service,
				(http_request_pool*)pools[i],
				APPLICATION_JSON,
				gson(req),
				buffer);
			if (ret)
				break;
		}

		std::pair<bool, std::string> ret = gson(buffer, resp);
		if (!ret.first)
		{
			logger_error("gson error: %s", ret.second.c_str());
			return  false;
		}
		if (resp.status != "ok")
		{
			logger_error("find_service resp status "
				"error: %s", resp.status.c_str());
			return false;
		}
		addrs = resp.server_addrs;
		return true;
	}

	void http_rpc_client::add_service_addr(
		const string &service_name, 
		const std::vector<string> &addrs)
	{

		lock_guard guard(service_addrs_locker_);

		http_rpc_service_info * service_addr = NULL;
		
		std::map<string, http_rpc_service_info*>::iterator itr =
			service_addrs_.find(service_name);

		if (itr == service_addrs_.end())
		{
			service_addr = new http_rpc_service_info;
			service_addr->addrs_ = addrs;
			service_addr->index_ = 0;
			service_addr->service_name_ = service_name;
			service_addrs_[service_name] = service_addr;

			return;
		}
		service_addr = itr->second;

		for (size_t i = 0; i < addrs.size(); i++)
		{			
			for (size_t j = 0; j< service_addr->addrs_.size(); j++)
			{
				if (service_addr->addrs_[j] == addrs[j])
				{
					continue;
				}
			}
			service_addr->addrs_.push_back(addrs[i]);
		}
		return;
	}

	void http_rpc_client::add_service_addr(const string &service_name, 
		const string &addr)
	{
		lock_guard guard(service_addrs_locker_);

		http_rpc_service_info * service_addr = NULL;

		std::map<string, http_rpc_service_info*>::iterator itr =
			service_addrs_.find(service_name);
		if (itr == service_addrs_.end())
		{
			service_addr = new http_rpc_service_info;
			service_addr->addrs_.push_back(addr);
			service_addr->index_ = 0;
			service_addr->service_name_ = service_name;
			service_addrs_[service_name] = service_addr;
			return;
		}
		service_addr = itr->second;

		for (size_t i = 0; i< service_addr->addrs_.size(); i++)
		{
			if (service_addr->addrs_[i] == addr)
			{
				return;
			}
		}
		service_addr->addrs_.push_back(addr);
		return;
	}
}