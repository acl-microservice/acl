#include "http_rpc.h"

namespace acl
{
	
	rpc_service::rpc_service()
	{
		acl::acl_cpp_init();
		init_master_default_tbl();

		set_cfg_int(var_conf_int_tab);
		set_cfg_int64(var_conf_int64_tab);
		set_cfg_str(var_conf_str_tab);
		set_cfg_bool(var_conf_bool_tab);
	}

	int rpc_service::init_master_default_tbl()
	{
		var_conf_int_tab = new master_int_tbl[3]{ 
			{"redis_conn_timeout", 30, &var_cfg_redis_conn_timeout, 0, 0},
			{"redis_rw_timeout", 30, &var_cfg_redis_rw_timeout, 0, 0 },
			{ 0, 0 , 0 , 0, 0 }
		};
		var_conf_str_tab = new master_str_tbl[4]{
			{ "redis_addr", "", &var_cfg_redis_addr},
			{ "memcache_addr", "", &var_cfg_memcache_addr},
			{ "memcache_addr", "", &var_cfg_memcache_addr },
			{ 0, 0 , 0 }
		};
		var_conf_int64_tab = new master_int64_tbl[1]{ 
			{ 0, 0 , 0 , 0, 0 } 
		};

		var_conf_bool_tab = new master_bool_tbl[1]{
			{ 0, 0 , 0 }
		};
	}

	int rpc_service::run(int argc, char *argv[])
	{
		if (argc >= 2 && strcmp(argv[1], "alone") == 0)
		{
			// 日志输出至标准输出
			acl::log::stdout_open(true);  
			const char* addr = "10080";
			printf("listen on: %s\r\n", addr);
			if (argc >= 3)
				run_alone(addr, argv[2], 0, 100);  // 单独运行方式
			else
				run_alone(addr, NULL, 0, 100);  // 单独运行方式

			printf("Enter any key to exit now\r\n");
			getchar();
		}
		else
			run_daemon(argc, argv);  // acl_master 控制模式运行
	}

	

	void rpc_service::proc_on_init()
	{
		if (var_cfg_redis_addr)
		{
			redis_cluster_cli_ = new acl::redis_client_cluster();
			redis_cluster_cli_->set(
				var_cfg_redis_addr, 
				acl_var_threads_pool_limit);
		}

		//设置白名单
		if (var_cfg_allow_clients && *var_cfg_allow_clients)
		{
			access_list::get_instance()
				.set_allow_clients(var_cfg_allow_clients);
		}
	}

	void rpc_service::thread_on_close(socket_stream* stream)
	{
		http_rpc_servlet *servlet = (http_rpc_servlet *)stream->get_ctx();
		session *sess = &servlet->getSession();
		delete servlet;
		delete sess;
	}

	bool rpc_service::thread_on_timeout(socket_stream* stream)
	{
		//keep read next time;
		return true;
	}

	bool rpc_service::thread_on_accept(socket_stream* stream)
	{
		const char* peer = stream->get_peer(false);

		if (peer == NULL || *peer == 0)
		{
			logger_warn("invalid client, local: %s, peer: %s"
				,peer ? peer : "null");
			return false;
		}
		// 检查rpc_client IP 访问权限
		if (access_list::get_instance().check_client(peer) == false)
		{
			logger_warn("Denied from server ip: %s", peer);
			return false;
		}

		stream->set_rw_timeout(var_cfg_rw_timeout);

		http_rpc_servlet *servlet = new http_rpc_servlet;
		
		stream->set_ctx(servlet);

		return true;
	}

	bool rpc_service::thread_on_read(socket_stream* stream)
	{
		http_rpc_servlet *servlet = (http_rpc_servlet *)stream->get_ctx();
		if (servlet == NULL)
			logger_fatal("servlet null!");
		session *sess = get_session();
		servlet->doRun(*sess, stream);
	}


	session * rpc_service::get_session()
	{
		if (redis_cluster_cli_)
		{
			return new redis_session(*redis_cluster_cli_, 
				acl_var_threads_pool_limit);
		}
		return new memcache_session(var_cfg_memcache_addr);
	}

}


