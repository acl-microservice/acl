#include "nameserver.h"


/**
 * 初始化http_rpc 配置信息
 */
static void init_config()
{
	//最后一行必须是NULL,0 ,NULL,0, 0表示结束
	using namespace acl::http_rpc_config;
	var_conf_int_tab = new acl::master_int_tbl[7]{
		{ "var_cfg_redis_conn_timeout", 30, &var_cfg_redis_conn_timeout, 0, 0 },
		{ "var_cfg_redis_rw_timeout", 30, &var_cfg_redis_rw_timeout, 0, 0 },
		{ "var_cfg_rpc_conn_check_inter", 1,&var_cfg_rpc_conn_check_inter, 0, 0 },
		{ "var_cfg_rpc_conn_check_timeout", 5,&var_cfg_rpc_conn_check_timeout, 0, 0 },
		{ "var_cfg_register_service_inter", 3,&var_cfg_regist_service_inter ,0, 0 },
		{ "var_cfg_update_service_inter", 3,&var_cfg_update_service_inter ,0, 0 },

		{ NULL, 0 , NULL , 0, 0 }
	};

	//最后一行必须是NULL,NULL,NULL 表示结束
	var_conf_str_tab = new acl::master_str_tbl[12]{
		{ "var_cfg_allow_clients","all",&var_cfg_allow_clients },
		{ "var_cfg_redis_addr", "", &var_cfg_redis_addr },
		{ "var_cfg_memcache_addr", "", &var_cfg_memcache_addr },
		{ "var_cfg_find_service", "/nameservice/service_mgr/find",&var_cfg_find_service },
		{ "var_cfg_find_services", "/nameservice/service_mgr/finds",&var_cfg_find_services },
		{ "var_cfg_add_service", "/nameservice/service_mgr/add",&var_cfg_add_service },
		{ "var_cfg_del_service", "/nameservice/service_mgr/del",&var_cfg_del_service },
		{ "var_cfg_server_addr", "",&var_cfg_server_addr },
		{ "var_cfg_nameserver_name", "nameserver",&var_cfg_nameserver },
		{ "var_cfg_server_name", "", &var_cfg_server_name },
		{ "var_cfg_nameserver", "nameserver", &var_cfg_nameserver },
		{ NULL, NULL, NULL }
	};
	var_conf_int64_tab = new acl::master_int64_tbl[1]{
		{ 0, 0 , 0 , 0, 0 }
	};

	var_conf_bool_tab = new acl::master_bool_tbl[1]{
		{ 0, 0 , 0 }
	};
}
int main(int argc, char *argv[])
{
	//初始化 默认配置
	//如果需要的添加的配置，需要自己实现一个配置信息
	//初始化函数
	
	//初始化 acl
	acl::acl_cpp_init();

	acl::log::stdout_open(true);

	nameserver server;

	if (argc >= 2 && strcmp(argv[1], "alone") == 0)
	{
		const char* addr = "10080";
		printf("listen on: %s\r\n", addr);
		if (argc >= 3)
		{
			// 单独运行方式
			server.run_alone(addr, argv[2], 0, 100);
		}
		else
		{
			// 单独运行方式
			server.run_alone(addr, NULL, 0, 100);
		}

		printf("Enter any key to exit now\r\n");
		getchar();
	}
	// acl_master 控制模式运行
	server.run_daemon(argc, argv);  

	return 0;
}