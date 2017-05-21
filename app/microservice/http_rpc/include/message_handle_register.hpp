#pragma once
namespace acl
{
	class message_handle_register
	{
	public:
		message_handle_register()
		{

		}
		bool check_method_exist(const char *func_name)
		{
			acl::lock_guard guard(lock_);
			return message_handles_.find(func_name)
				== message_handles_.end();
		}
		message_handle *get_message_handle(const string &name)
		{
			acl::lock_guard guard(lock_);
			std::map<acl::string, message_handle *>::iterator 
				itr = message_handles_.find(name);
			if (itr == message_handles_.end())
				return NULL;
			return itr->second;
		}
	protected:
		
		acl::locker lock_;
		std::map<acl::string, message_handle *> message_handles_;
	};

}