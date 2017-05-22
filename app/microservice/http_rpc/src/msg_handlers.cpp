#include "http_rpc.h"

namespace acl
{
	acl::msg_handlers::msg_handlers()
	{

	}

	bool acl::msg_handlers::check_method_exist(const char *func_name)
	{
		acl::lock_guard guard(lock_);
		return message_handles_.find(func_name)
			== message_handles_.end();
	}

	func_handle * msg_handlers::get_message_handle(const string &name)
	{
		acl::lock_guard guard(lock_);
		std::map<acl::string, func_handle *>::iterator
			itr = message_handles_.find(name);
		if (itr == message_handles_.end())
			return NULL;
		return itr->second;
	}

}
