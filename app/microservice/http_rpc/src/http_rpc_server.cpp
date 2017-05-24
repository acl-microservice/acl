#include "http_rpc.h"



namespace acl
{
	

	http_rpc_server::http_rpc_server()
	{		
		acl_assert(http_rpc_config::var_conf_int_tab);
		acl_assert(http_rpc_config::var_conf_int64_tab);
		acl_assert(http_rpc_config::var_conf_str_tab);
		acl_assert(http_rpc_config::var_conf_bool_tab);
	
		set_cfg_int(http_rpc_config::var_conf_int_tab);
		set_cfg_int64(http_rpc_config::var_conf_int64_tab);
		set_cfg_str(http_rpc_config::var_conf_str_tab);
		set_cfg_bool(http_rpc_config::var_conf_bool_tab);
	}

	void http_rpc_server::proc_on_init()
	{
		if (http_rpc_config::var_cfg_redis_addr)
		{
			redis_cluster_cli_ = new acl::redis_client_cluster();
			redis_cluster_cli_->set(
				http_rpc_config::var_cfg_redis_addr,
				acl_var_threads_pool_limit);
		}

		//设置白名单
		if (http_rpc_config::var_cfg_allow_clients && 
			*http_rpc_config::var_cfg_allow_clients)
		{
			access_list::get_instance()
				.set_allow_clients(http_rpc_config::var_cfg_allow_clients);
		}
		//init instances;
		http_rpc_client::get_instance();

		//nameserver not need service_register
		acl_assert(http_rpc_config::var_cfg_server_name);
		string servername = string(http_rpc_config::var_cfg_server_name);

		if (servername.empty())
			acl_assert("server_name empty.set_server_name() first");

		if(string("nameserver") != servername)
			service_register::get_instance().start();

		//init rpc_context
		for (std::vector<rpc_context*>::iterator iter = rpc_ctxs_.begin();
			iter != rpc_ctxs_.end(); ++iter)
		{
			(*iter)->init();
		}
	}

	void http_rpc_server::thread_on_close(socket_stream* stream)
	{
		http_rpc_servlet *servlet = (http_rpc_servlet *)stream->get_ctx();
		session *sess = &servlet->getSession();
		delete servlet;
		delete sess;
	}

	bool http_rpc_server::thread_on_timeout(socket_stream* stream)
	{
		//keep read next time;
		return true;
	}

	bool http_rpc_server::thread_on_accept(socket_stream* stream)
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

		//rpc 读写超时时间
		stream->set_rw_timeout(http_rpc_config::var_cfg_rw_timeout);

		http_rpc_servlet *servlet = new http_rpc_servlet;
		
		stream->set_ctx(servlet);

		return true;
	}

	bool http_rpc_server::thread_on_read(socket_stream* stream)
	{
		http_rpc_servlet *servlet = (http_rpc_servlet *)stream->get_ctx();
		if (servlet == NULL)
			logger_fatal("servlet null!");

		session *sess = create_session();
		servlet->doRun(*sess, stream);

		return true;
	}


	session * http_rpc_server::create_session()
	{
		if (redis_cluster_cli_)
		{
			return new redis_session(*redis_cluster_cli_, 
				acl_var_threads_pool_limit);
		}
		return new memcache_session(http_rpc_config::var_cfg_memcache_addr);
	}

}


