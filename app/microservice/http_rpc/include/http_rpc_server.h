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
		 * @param func_name {const char*} ������,����ƥ����Ϣ
		 * @param ctx {Context*} �����ָ��
		 * @param func{bool(Context::*)(const ReqType &, RespType &)*} ����ָ��
		 * @return {bool} ������� false ���ʾע��ʧ��
		 */
		template<class Context, class ReqType, class RespType>
		bool on_json(const char *func_name,
			Context *ctx,
			bool(Context::*func)(const ReqType &, RespType &))
		{
			string servername;

			acl_assert(http_rpc_config::var_cfg_server_name);

			servername.append(http_rpc_config::var_cfg_server_name);

			if (servername.empty())
				logger_fatal("server_name empty");

			if (servername != http_rpc_config::var_cfg_server_name)
			{
				//�ѷ���ע�ᵽ nameserver ��ȥ��
				service_register::get_instance().regist(
					http_rpc_config::var_cfg_server_addr, func_name);
			}
			return json_msg_handlers::get_instance().
				add(func_name, ctx, func);
		}

		/**
		 *ע�����
		 */
		template<class ServiceType>
		http_rpc_server &regist_service()
		{
			rpc_ctxs_.push_back(new ServiceType(*this));
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

		std::vector<rpc_context*> rpc_ctxs_;

		acl::redis_client_cluster *redis_cluster_cli_;
	};
}