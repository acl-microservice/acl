#pragma once
namespace acl
{
	class http_rpc_server: public master_threads
	{
	public:
		static http_rpc_server& get_instance();

		/**
		* 注册消息处理函数
		* @param func_name {const char*} 函数名,用来匹配消息
		* @param ctx {Context*} 对象的指针
		* @param func{bool(Context::*)(const ReqType &, RespType &)*} 函数指针
		* @return {bool} 如果返回 false 则表示注册失败
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
		* 当进程切换用户身份后调用的回调函数，此函数被调用时，进程
		* 的权限为普通受限级别
		*/
		virtual void proc_on_init();


		/**
		* 当与某个线程绑定的连接关闭时的回调函数
		* @param stream {socket_stream*}
		*/
		virtual void thread_on_close(socket_stream* stream);

		/**
		* 当某个网络连接的 IO 读写超时时的回调函数，
		* 如果该函数返回 true 则表示继续等待下一次
		* 读写，否则则希望关闭该连接
		* @param stream {socket_stream*}
		* @return {bool} 如果返回 false 则表示子类要求关闭连接，而不
		*  必将该连接再传递至 thread_main 过程
		*/
		virtual bool thread_on_timeout(socket_stream* stream);

		/**
		* 当线程池中的某个线程获得一个连接时的回调函数，
		* 子类可以做一些初始化工作
		* @param stream {socket_stream*}
		* @return {bool} 如果返回 false 则表示子类要求关闭连接，而不
		*  必将该连接再传递至 thread_main 过程
		*/
		virtual bool thread_on_accept(socket_stream* stream);

		/**
		* 纯虚函数：当某个客户端连接有数据可读或关闭或出错时调用此函数
		* @param stream {socket_stream*}
		* @return {bool} 返回 false 则表示当函数返回后需要关闭连接，
		*  否则表示需要保持长连接，如果该流出错，则应用应该返回 false
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
		//rpc 读写超时时间 秒
		int var_cfg_rw_timeout;

		master_int_tbl *var_conf_int_tab;
		master_int64_tbl  *var_conf_int64_tab;
		master_str_tbl  *var_conf_str_tab;
		master_bool_tbl  *var_conf_bool_tab;
	};
}