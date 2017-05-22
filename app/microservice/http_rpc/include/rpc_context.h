#pragma once
#include "nameserver_proto.h"
namespace acl
{
	class rpc_context
	{
	public:
		virtual ~rpc_context();
		static HttpServletRequest &getHttpServletRequest();
	};



	class nameservice:public rpc_context
	{
	public:
		nameservice();
		bool add_service(const 
			nameserver_proto::add_services_req &req, 
			nameserver_proto::add_services_resp &resp );
	private:
		void init();
	};
}

