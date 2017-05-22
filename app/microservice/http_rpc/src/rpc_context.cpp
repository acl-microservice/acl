#include "http_rpc.h"

#define SERVER_NAME "nameserver";

namespace acl
{

	rpc_context::~rpc_context()
	{

	}

	HttpServletRequest & rpc_context::getHttpServletRequest()
	{
		acl_pthread_key_t key;
		key = acl_pthread_self();
		return *(HttpServletRequest*)acl_pthread_tls_get(&key);
	}

	nameservice::nameservice()
	{
		init();
	}

	bool nameservice::add_service(
		const nameserver_proto::add_services_req &req,
		nameserver_proto::add_services_resp &resp)
	{
		return true;
	}

	void nameservice::init()
	{
		http_rpc_server::get_instance().
			regist_json_msg_handler(DEFINE_SERVICE_NAME(SERVER_NAME,nameservice,add_service), this, &nameservice::add_service);
	}

}