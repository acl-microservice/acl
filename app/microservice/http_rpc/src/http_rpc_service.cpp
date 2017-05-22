#include "http_rpc.h"



namespace acl
{
	char *var_confg_nameserver_register_find_service;
	int var_confg_rpc_conn_check_inter;
	int var_confg_rpc_conn_check_timeout;

	http_rpc_service::http_rpc_service()
	{
		acl::acl_cpp_init();
		init_master_default_tbl();

		set_cfg_int(var_conf_int_tab);
		set_cfg_int64(var_conf_int64_tab);
		set_cfg_str(var_conf_str_tab);
		set_cfg_bool(var_conf_bool_tab);
	}

	void http_rpc_service::init_master_default_tbl()
	{
		var_conf_int_tab = new master_int_tbl[5]{ 
			{"redis_conn_timeout", 30, &var_cfg_redis_conn_timeout, 0, 0},
			{ "redis_rw_timeout", 30, &var_cfg_redis_rw_timeout, 0, 0 },
			{ "var_confg_rpc_conn_check_inter", 1, &var_confg_rpc_conn_check_inter, 0, 0 },
			{ "var_confg_rpc_conn_check_timeout", 5, &var_confg_rpc_conn_check_timeout, 0, 0 },

			{ 0, 0 , 0 , 0, 0 }
		};
		var_conf_str_tab = new master_str_tbl[5]{
			{ "redis_addr", "", &var_cfg_redis_addr},
			{ "memcache_addr", "", &var_cfg_memcache_addr},
			{ "memcache_addr", "", &var_cfg_memcache_addr },
			
			//发现服务 查询服务接口
			{ "var_confg_nameserver_register_find_service",
				"/nameservice/register/find_service", 
			&var_confg_nameserver_register_find_service },

			{ 0, 0 , 0 }
		};
		var_conf_int64_tab = new master_int64_tbl[1]{ 
			{ 0, 0 , 0 , 0, 0 } 
		};

		var_conf_bool_tab = new master_bool_tbl[1]{
			{ 0, 0 , 0 }
		};
	}

	int http_rpc_service::run(int argc, char *argv[])
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

		return 0;
	}

	

	void http_rpc_service::proc_on_init()
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

	void http_rpc_service::thread_on_close(socket_stream* stream)
	{
		http_rpc_servlet *servlet = (http_rpc_servlet *)stream->get_ctx();
		session *sess = &servlet->getSession();
		delete servlet;
		delete sess;
	}

	bool http_rpc_service::thread_on_timeout(socket_stream* stream)
	{
		//keep read next time;
		return true;
	}

	bool http_rpc_service::thread_on_accept(socket_stream* stream)
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

	bool http_rpc_service::thread_on_read(socket_stream* stream)
	{
		http_rpc_servlet *servlet = (http_rpc_servlet *)stream->get_ctx();
		if (servlet == NULL)
			logger_fatal("servlet null!");

		session *sess = get_session();
		servlet->doRun(*sess, stream);

		return true;
	}


	session * http_rpc_service::get_session()
	{
		if (redis_cluster_cli_)
		{
			return new redis_session(*redis_cluster_cli_, 
				acl_var_threads_pool_limit);
		}
		return new memcache_session(var_cfg_memcache_addr);
	}

}


