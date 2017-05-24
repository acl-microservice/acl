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
}