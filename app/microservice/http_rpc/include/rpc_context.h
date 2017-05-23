#pragma once
#include "nameserver_proto.h"
namespace acl
{
	/*
		���Ե�service��Ҫ�̳�����࣬ʵ��init������
		init ����������ʼ��һЩ��Դ������Ǻ������̰߳�ȫ�ġ�
		����ܹ��ǻ���acl::master_threads ģ�ͣ��ṩ����ӿڻ���ܱ����߳�ͬʱ���ʡ�
		Ҳ��˵ �û��Լ������� ��Ҫ�Լ������̰߳�ȫ����
	*/
	class rpc_context
	{
	public:
		virtual ~rpc_context();
		static HttpServletRequest &getHttpServletRequest();
		virtual void init() = 0;
	};



	/*class nameservice:
		public rpc_context
	{
	public:
		nameservice();
		bool add_service(const 
			nameserver_proto::add_services_req &req, 
			nameserver_proto::add_services_resp &resp );
	private:
		void init();
	};*/
}

