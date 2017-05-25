#pragma once
namespace acl
{
     /**
	  * �������Ļ��࣬�̳�ʵ��init����
	  */
	class http_rpc_server: public master_threads
	{
	public:
		http_rpc_server();

		/**
		 * ע����Ϣ������
		 * @param service_path {const char*} ������·��,����ƥ����Ϣ
		 * Ҫ���ʽ��/{server}/{module}/{interface}
		 * @param ctx {Context*} �����ָ��
		 * @param func{bool(Context::*)(const ReqType &, RespType &)*} ����ָ��
		 * @return {bool} ������� false ���ʾע��ʧ��
		 */
		template<class Context, class ReqType, class RespType>
		bool on_json(const char *service_path,
			Context *ctx,
			bool(Context::*func)(const ReqType &, RespType &))
		{
			return json_service_handles::get_instance().
				add(service_path, ctx, func);
		}

		/**
		 *ע�����
		 */
		template<class ServiceType>
		http_rpc_server &regist_service()
		{
			services_.push_back(new ServiceType(*this));
			return *this;
		}
	protected:
		/*
		 * ��������ʼ������������ʵ��������ʼ������
		 */
		virtual void init() = 0;
	private:

		http_rpc_server(const http_rpc_server&);
		http_rpc_server &operator=(const http_rpc_server&);

		/**
		 * �������л��û���ݺ���õĻص��������˺���������ʱ������
		 * ��Ȩ��Ϊ��ͨ���޼���
		 */
		virtual void proc_on_init();


		/**
		 * ����ĳ���̰߳󶨵����ӹر�ʱ�Ļص�����
		 * @param stream {socket_stream*}
	 	 */
		virtual void thread_on_close(socket_stream* stream);

		/**
		 * ��ĳ���������ӵ� IO ��д��ʱʱ�Ļص�������
		 * ����ú������� true ���ʾ�����ȴ���һ��
		 * ��д��������ϣ���رո�����
		 * @param stream {socket_stream*}
		 * @return {bool} ������� false ���ʾ����Ҫ��ر����ӣ�����
		 *  �ؽ��������ٴ����� thread_main ����
		 */
		virtual bool thread_on_timeout(socket_stream* stream);

		/**
		 * ���̳߳��е�ĳ���̻߳��һ������ʱ�Ļص�������
		 * ���������һЩ��ʼ������
		 * @param stream {socket_stream*}
		 * @return {bool} ������� false ���ʾ����Ҫ��ر����ӣ�����
		 *  �ؽ��������ٴ����� thread_main ����
		 */
		virtual bool thread_on_accept(socket_stream* stream);

		/**
		 * ���麯������ĳ���ͻ������������ݿɶ���رջ����ʱ���ô˺���
		 * @param stream {socket_stream*}
		 * @return {bool} ���� false ���ʾ���������غ���Ҫ�ر����ӣ�
		 *  �����ʾ��Ҫ���ֳ����ӣ��������������Ӧ��Ӧ�÷��� false
		 */
		virtual bool thread_on_read(socket_stream* stream);


		session *create_session();
	private:

		std::vector<service_base*> services_;

		acl::redis_client_cluster *redis_cluster_cli_;
	};
}