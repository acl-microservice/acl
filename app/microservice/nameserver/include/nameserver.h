#pragma once
#include "http_rpc.h"
namespace nameserver
{
	class service_mgr : acl::rpc_context
	{
	private:
		//service: addrs
		struct service_ttl;
		struct service_info
		{
			acl::string addr_;
			std::list<service_ttl*>::iterator ttl_it_;
		};

		struct service_ttl
		{
			acl::string service_name_;
			acl::string addr_;
			unsigned long long when_;
		};
	public:
		service_mgr()
		{

		}
		~service_mgr()
		{

		}
		bool add(const nameserver_proto::add_services_req &req,
			nameserver_proto::add_services_resp &resp)
		{
			acl::lock_guard guard(locker_);

			for (size_t i = 0; i < req.service_names.size(); i++)
			{
				service_info *info = NULL;
				service_ttl *ttl = NULL;

				info = services_[req.service_names[i]][req.server_addr];
				if (!info)
				{
					info = new service_info;
					ttl  = new service_ttl;

					ttl->addr_ = req.server_addr;
					ttl->service_name_ = req.service_names[i];
					ttl->when_ = time(NULL) + timeout_;
					info->ttl_it_ = service_ttl_.insert(service_ttl_.end(), ttl);
					info->addr_ = req.server_addr;
					services_[req.service_names[i]][req.server_addr] = info;
					continue;
				}
				ttl = *(info->ttl_it_);
				ttl->when_ = time(NULL) + timeout_;
				service_ttl_.erase(info->ttl_it_);
				info->ttl_it_ = service_ttl_.insert(service_ttl_.end(), ttl);

			}
			resp.result = "ok";
			return true;
		}

		bool find_service(const nameserver_proto::find_service_req &req,
			nameserver_proto::find_service_resp &resp)
		{
			acl::lock_guard guard(locker_);
			
			std::map<acl::string, std::map<acl::string, 
				service_info*>>::iterator 
				serv_it = services_.find(req.service_name);

			if (serv_it == services_.end())
			{
				resp.status = "not exist";
				return true;
			}
			std::map<acl::string, service_info*> 
				&addr_infos = serv_it->second;
			
			std::map<acl::string, service_info*>::iterator
				it = addr_infos.begin();

			for (; it != addr_infos.end(); ++it)
			{
				resp.server_addrs.push_back(it->second->addr_);
			}
			resp.service_name = req.service_name;
			resp.status = "ok";
			return true;
		}

		bool find_services(const nameserver_proto::find_services_req &req,
			nameserver_proto::find_services_resp &resp)
		{
			acl::lock_guard guard(locker_);

			for (size_t i = 0; i < req.service_names.size(); i++)
			{
				acl::string name = req.service_names[i];

				std::map<acl::string, std::map<acl::string, service_info*>>
					::iterator serv_it = services_.find(name);

				if (serv_it == services_.end())
				{
					continue;
				}

				nameserver_proto::service_info &serv_info = resp.service_infos[name];
				serv_info.service_name = name;

				std::map<acl::string, service_info*> &addr_infos = serv_it->second;
				
				std::map<acl::string, service_info*>::iterator it 
					= addr_infos.begin();

				for (; it != addr_infos.end(); ++it)
				{
					serv_info.server_addrs.push_back(it->second->addr_);
				}
			}
			return true;
		}

		bool del_service(const nameserver_proto::del_services_req &req,
			nameserver_proto::del_services_resp &resp)
		{
			acl::lock_guard guard(locker_);
			for (size_t i = 0; i < req.service_names.size();i++)
			{
				std::map<acl::string, std::map<acl::string, service_info*>>
					::iterator serv_it = services_.find(req.service_names[i]);

				if (serv_it == services_.end())
					continue;

				std::map<acl::string, service_info*> addrs = serv_it->second;
				
				std::map<acl::string, service_info*>::iterator addr_it = 
					addrs.find(req.server_addr);

				if (addr_it == addrs.end())
					continue;
				service_ttl_.erase(addr_it->second->ttl_it_);
				delete addr_it->second;
				addrs.erase(addr_it);
			}
			resp.result = "ok";
			return true;
		}

		void init()
		{
			acl::http_rpc_server &server =
				acl::http_rpc_server::get_instance();

			acl_assert(server.regist_json_msg_handler(
				"/nameservice/service_mgr/add",
				this,service_mgr::add));

			acl_assert(server.regist_json_msg_handler(
				"/nameservice/service_mgr/find",
				this,
				service_mgr::find_service));

			acl_assert(server.regist_json_msg_handler(
				"/nameservice/service_mgr/finds",
				this,
				service_mgr::find_services));

			acl_assert(server.regist_json_msg_handler(
				"/nameservice/register/del_service",
				this,
				service_mgr::del_service));
		}

		void check_timeout()
		{
			acl::lock_guard guard(locker_);

			while (service_ttl_.size())
			{
				service_ttl *ttl = service_ttl_.front();
				if (ttl->when_ < time(NULL))
				{
					std::map<acl::string,
						std::map<acl::string, service_info*>>
						::iterator serv_it = 
						services_.find(ttl->service_name_);

					std::map<acl::string, service_info*> 
						&service_infos = serv_it->second;

					std::map<acl::string, service_info*>::iterator 
						it = service_infos.find(ttl->addr_);

					acl_assert(it != service_infos.end());

					service_info* info = it->second;
					service_infos.erase(it);
					if (service_infos.empty())
					{
						services_.erase(serv_it);
					}
					service_ttl_.pop_front();

					delete info;
					delete ttl;
					continue;
				}
				return;
			}
		}
	private:

		acl::locker locker_;

		int timeout_;

		std::list<service_ttl*> service_ttl_;

		//service_name: addrs
		std::map<acl::string, std::map<acl::string, service_info*>> services_;
	};
}