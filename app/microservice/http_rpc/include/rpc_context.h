#pragma once
namespace acl
{
	/**
	 *	���Ե�service��Ҫ�̳�����࣬ʵ��init������
	 *	init ����������ʼ��һЩ��Դ������Ǻ������̰߳�ȫ�ġ�
	 *	����ܹ��ǻ���acl::master_threads ģ�ͣ��ṩ����ӿڻ���ܱ����߳�ͬʱ���ʡ�
	 *	Ҳ��˵ �û��Լ������� ��Ҫ�Լ������̰߳�ȫ����
	 */
	class http_rpc_server;
	class rpc_context
	{
	public:
		rpc_context(http_rpc_server &server)
			:server_(server)
		{}

		virtual ~rpc_context();

		/**
		 * service ��ʼ�����������������http_rpc_server �ص�
		 */
		virtual void init() = 0;

	protected:

		/**
		 *  ��ȡ HttpServletReques ����
		 *  ע�⣺�������ֻ�з��񱻵��ù����в�����Ч��
		 *  ����ǰ�� HttpServletRequest �ǲ����ڵ�
		 */
		static HttpServletRequest &getHttpServletRequest();

		http_rpc_server &server_;
	};
}

