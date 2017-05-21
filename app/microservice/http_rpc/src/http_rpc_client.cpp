#include "http_rpc.h"
namespace acl
{

	http_rpc_client::http_rpc_client()
	{

	}

	void http_rpc_client::init()
	{
		int  cocurrent = 100, 
			conn_timeout = 100, 
			rw_timeout = 200;

		// 创建 HTTP 请求连接池集群管理对象
		conn_manager_ = new http_request_manager();


		int  check_inter = 1, check_conn_timeout = 5;
		acl::connect_monitor* monitor = new acl::connect_monitor(*conn_manager_);

		(*monitor).set_check_inter(check_inter).
			set_conn_timeout(check_conn_timeout);

		// 启动后台检测线程
		conn_manager_->start_monitor(monitor);
	}

	acl::http_rpc_client::status
		http_rpc_client::invoke_http_req(
			const string &service_name,
			const char *context_type,
			const string&req_data,
			string &resp_buffer)
	{
		connect_pool *pool = get_connect_pool(service_name);

		if (pool == NULL)
		{
			return status(-1, string("can't service_addr: ")
				+= service_name);
		}

		// 从连接池中获取一个 HTTP 连接
		connect_guard _connect_guard(*pool);
		http_request* conn = (http_request*)_connect_guard.peek();
		if (conn == NULL)
		{
			logger_error("%lu: peek connect failed from %s<<<\r\n",
				(unsigned long)acl_pthread_self(),
				pool->get_addr());

			return status(-1, string().format(
				"%lu: peek connect failed from %s<<<\r\n",
				(unsigned long)acl_pthread_self(),
				pool->get_addr()));
		}

		// 需要对获得的连接重置状态，以清除上次请求过程的临时数据
		else
			conn->reset();

		conn->request_header().
			set_url(service_name).
			set_content_type(context_type).
			set_content_length(req_data.length());

		if (!conn->request(req_data.c_str(), req_data.size()))
		{
			logger_error("http_request failed");
			_connect_guard.set_keep(false);

			return status(-1, "http_request failed");
		}

		char  buf[8192];
		int   ret, length = 0;
		// 接收 HTTP 响应体数据
		long long body_len = conn->body_length();
		while (true)
		{
			ret = conn->read_body(buf, sizeof(buf));
			if (ret == 0)
				break;
			else if (ret < 0)
			{
				logger_error("http_request read_body error");
				_connect_guard.set_keep(false);
				return status(-1, "http_request read_body error");
			}
			resp_buffer.append(buf, ret);
			length += ret;
		}
		if (conn->http_status() != 200)
		{
			status retval(conn->http_status(), resp_buffer);
			resp_buffer.clear();
			return retval;
		}

		return status();
	}

	connect_pool * http_rpc_client::get_connect_pool(const string &service_name)
	{
		acl::lock_guard guard(locker_);

		std::map<string, rpc_service_addr*>::iterator
			itr = service_addrs_.find(service_name);
		if (itr == service_addrs_.end())
			return NULL;

		rpc_service_addr *pool_info = itr->second;
		int index = ++pool_info->index_ %pool_info->addrs_.size();

		string *addr = pool_info->addrs_[index];
		assert(addr);
		return conn_manager_->get(addr->c_str());
	}

}