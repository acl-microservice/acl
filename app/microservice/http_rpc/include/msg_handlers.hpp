#pragma once
namespace acl
{
    /**
	 *处理消息的基类，管理消息处理函数句柄
	 *
	 */
	class msg_handlers
	{
	public:
		msg_handlers();

		virtual ~msg_handlers() {}

		/**
		 * 坚持函数是否存在
		 * @param func_name{const char *} 函数名称
		 */
		bool exist(const char *func_name);
		
		/**
		 * 获取函数句柄
		 * @param name{const string &} 函数名称
		 * @return {func_handler*} 
		 * 存在返回func_handler *，否则NULL
		 */
		func_handler *get_handle(const string &name);
	protected:
		
		acl::locker lock_;
		std::map<acl::string, func_handler *> message_handles_;
	};

}