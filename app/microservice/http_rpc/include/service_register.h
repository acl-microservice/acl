#pragma once
#include <set>
namespace acl
{
	/**
	 * service_register ��nameservice��rpc_client;
	 * regist ע�����nameserver ��ȥ���������ķ����ѯ
	 * del ɾ���Ѿ�ע��ķ���
	 * stop ����ֹͣ����
	 * nameserver ��һ����ʱ�Ļ��ƣ�����̶�ʱ���ڣ�
	 * ����û�м���ע�ᣬ����ɾ����
	 */
	class service_register: public acl::thread
	{
	public:
		static service_register& get_instance();
		
		/*
		 * ע�����nameserver��ȥ
		 * @param addr_ {const string &}����������ַ
		 * @param service_name {const string &}��������,
		 * ��������Ϊ/{server}/{module}/{interface}
		 * @return bool, true ע��ɹ���false ʧ��
		 */
		bool regist(const string &addr_, const string& service_name);

		/*
		 * ȡ��ע�����
		 * @param addr_ {const string &}����������ַ
		 * @param service_name {const string &}��������,
		 * ��������Ϊ/{server}/{module}/{interface}
		 * @return bool, true ע��ɹ���false ʧ��
		 */
		bool del(const string &addr_, const string& service_name);

		/*
		 * ֹͣע���������
		 */
		void stop();
	private:
		service_register();
		service_register(const service_register&);
		service_register &operator= (const service_register&);

		void rpc_regist_service(const string &addr_, 
			const std::vector<string>& service_names);

		virtual void* run();

		bool is_stop_;

		locker locker_;
		//addr:service
		std::map<string, std::set<string>> services;
	};
}