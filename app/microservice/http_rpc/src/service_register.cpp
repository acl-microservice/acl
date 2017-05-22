#include "http_rpc.h"
#include "nameserver_proto.h"

namespace acl
{
	int var_cfg_register_service_inter;
	char *var_confg_nameserver_register_add_service;
	char *var_confg_nameserver_register_del_service;

	service_register& service_register::get_instance()
	{
		static service_register inst;
		return inst;
	}

	service_register::service_register()
		:is_stop_(false)
	{

	}


	void* service_register::run()
	{
		do
		{
			timeval start, end;
			gettimeofday(&start, NULL);
			locker_.lock();
			for (std::map<string, std::set<string>>::iterator itr =
				services.begin(); itr != services.end(); ++itr)
			{
				std::vector<string> services;
				for (std::set<string>::iterator set_itr =
					itr->second.begin();
					set_itr != itr->second.end(); set_itr++)
				{
					services.push_back(*set_itr);
				}
				if (services.size())
					rpc_regist_service(itr->first, services);
			}
			locker_.unlock();
			gettimeofday(&end, NULL);

			long mills = (end.tv_sec - start.tv_sec) * 1000;
			mills += (end.tv_usec - start.tv_usec) / 1000;

			acl_doze(mills);

		} while (!is_stop_);

		return NULL;
	}

	
	void service_register::rpc_regist_service(const string &addr_, 
		const std::vector<string>& service_names)
	{
		nameserver_proto::add_services_req req;
		nameserver_proto::add_services_resp resp;

		req.server_addr = addr_;
		req.service_names = service_names;

		http_rpc_client::status_t status =
			http_rpc_client::get_instance().
			json_call(var_confg_nameserver_register_add_service,
				req, resp);

		if (!status)
		{
			logger_error("json_call failed:%s",
				status.error_str_.c_str());
		}
	}

	bool service_register::del(const string &addr_,
		const string& service_name)
	{
		nameserver_proto::del_services_req req;
		nameserver_proto::del_services_resp resp;

		req.server_addr = addr_;
		req.service_names.push_back(service_name);

		http_rpc_client::status_t status =
			http_rpc_client::get_instance().
			json_call(var_confg_nameserver_register_del_service,
				req, resp);
		if (!status)
		{
			logger_error("json_call failed:%s", status.error_str_.c_str());
		}
		//del service from register timer'
		lock_guard guard(locker_);
		services[addr_].erase(service_name);
		return !!status;
	}

	bool service_register::regist(const string &addr_,
		const string& service_name)
	{
		nameserver_proto::add_services_req req;
		nameserver_proto::add_services_resp resp;

		req.server_addr = addr_;
		req.service_names.push_back(service_name);

		http_rpc_client::status_t status =
			http_rpc_client::get_instance().
			json_call(var_confg_nameserver_register_add_service,
				req, resp);
		if (status)
		{
			logger_error("json_call failed:%s", status.error_str_.c_str());
		}
		//add service to regist timer
		lock_guard guard(locker_);
		services[addr_].insert(service_name);
		return !!status;
	}

	void service_register::stop()
	{
		is_stop_ = true;
	}

	

}