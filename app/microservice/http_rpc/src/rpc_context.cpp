#include "http_rpc.h"

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

	//nameservice::nameservice()
	//{

	//}

	//bool nameservice::add_service(
	//	const nameserver_proto::add_services_req &req,
	//	nameserver_proto::add_services_resp &resp)
	//{
	//	return true;
	//}
	////DEFINE_SERVICE_NAME(SERVER_NAME,nameservice,add_service)
	//void nameservice::init()
	//{
	//	http_rpc_server &server = http_rpc_server::get_instance();
	//	const char *add_service_name = 
	//		DEFINE_SERVICE_NAME(SERVER_NAME, nameservice, add_service);

	//	server.regist_json_msg_handler(add_service_name, this, &nameservice::add_service);
	//}

}