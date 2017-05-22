#pragma once
namespace acl
{
	class http_rpc_server: public master_threads
	{
	public:
		static http_rpc_server& get_instance();

		/**
		* ע����Ϣ������
		* @param func_name {const char*} ������,����ƥ����Ϣ
		* @param ctx {Context*} �����ָ��
		* @param func{bool(Context::*)(const ReqType &, RespType &)*} ����ָ��
		* @return {bool} ������� false ���ʾע��ʧ��
		*/
		template<class Context, class ReqType, class RespType>
		bool regist_json_msg_handler(const char *func_name, Context *ctx,
			bool(Context::*func)(const ReqType &, RespType &))
		{
			return json_msg_handlers::get_instance().add(func_name, ctx, func);
		}

		int run(int argc, char *argv[]);
	private:
		//singleton 
		http_rpc_server();
		http_rpc_server(const http_rpc_server&);
		http_rpc_server &operator=(const http_rpc_server&);

		void init_master_default_tbl();

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


		session *get_session();
	private:

		acl::redis_client_cluster *redis_cluster_cli_;

		//config
		char *var_cfg_redis_addr;
		int var_cfg_redis_conn_timeout;
		int var_cfg_redis_rw_timeout;
		char *var_cfg_memcache_addr;
		char *var_cfg_allow_clients;
		//rpc ��д��ʱʱ�� ��
		int var_cfg_rw_timeout;

		master_int_tbl *var_conf_int_tab;
		master_int64_tbl  *var_conf_int64_tab;
		master_str_tbl  *var_conf_str_tab;
		master_bool_tbl  *var_conf_bool_tab;
	};
}