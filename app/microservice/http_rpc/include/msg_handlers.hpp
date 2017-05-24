#pragma once
namespace acl
{
    /**
	 *������Ϣ�Ļ��࣬������Ϣ���������
	 *
	 */
	class msg_handlers
	{
	public:
		msg_handlers();

		virtual ~msg_handlers() {}

		/**
		 * ��ֺ����Ƿ����
		 * @param func_name{const char *} ��������
		 */
		bool exist(const char *func_name);
		
		/**
		 * ��ȡ�������
		 * @param name{const string &} ��������
		 * @return {func_handler*} 
		 * ���ڷ���func_handler *������NULL
		 */
		func_handler *get_handle(const string &name);
	protected:
		
		acl::locker lock_;
		std::map<acl::string, func_handler *> message_handles_;
	};

}