#pragma once
#include "http_rpc.h"
class service_mgr : public acl::rpc_context
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
		long long when_;
	};
public:
	service_mgr(acl::http_rpc_server &server);

	~service_mgr();

	bool add(const nameserver_proto::add_services_req &req,
		nameserver_proto::add_services_resp &resp);

	bool find_service(const nameserver_proto::find_service_req &req,
		nameserver_proto::find_service_resp &resp);

	bool find_services(const nameserver_proto::find_services_req &req,
		nameserver_proto::find_services_resp &resp);

	bool del_service(const nameserver_proto::del_services_req &req,
		nameserver_proto::del_services_resp &resp);

	void init();

	void check_timeout();
private:

	acl::locker locker_;

	int timeout_;

	std::list<service_ttl*> service_ttl_;

	//service_name: addrs
	std::map<acl::string, std::map<acl::string, service_info*>> services_;
};