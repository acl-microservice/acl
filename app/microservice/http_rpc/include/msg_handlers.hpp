#pragma once
namespace acl
{
	class msg_handlers
	{
	public:
		msg_handlers();
		virtual ~msg_handlers() {}
		bool check_method_exist(const char *func_name);
		func_handle *get_message_handle(const string &name);
	protected:
		
		acl::locker lock_;
		std::map<acl::string, func_handle *> message_handles_;
	};

}