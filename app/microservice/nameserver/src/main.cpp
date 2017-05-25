#include "http_rpc.h"
#include "nameserver.h"

//var_cfg_server_name，
//var_cfg_server_addr,
//var_cfg_nameserver_addr
//必须配置
//实现自己的配置信息
//有写内容默认是空的，不能直接使用
//最后一行必须是NULL,0 ,NULL,0, 0表示结束
using namespace acl::http_rpc_config;
acl::master_int_tbl acl::http_rpc_config::var_conf_int_tab  [] = {
	{ "var_cfg_redis_conn_timeout",     30, &var_cfg_redis_conn_timeout,     0, 0 },
	{ "var_cfg_redis_rw_timeout",       30, &var_cfg_redis_rw_timeout,       0, 0 },
	{ "var_cfg_rpc_conn_check_inter",   1,  &var_cfg_rpc_conn_check_inter,   0, 0 },
	{ "var_cfg_rpc_conn_check_timeout", 5,  &var_cfg_rpc_conn_check_timeout, 0, 0 },
	{ "var_cfg_register_service_inter", 3,  &var_cfg_regist_service_inter ,  0, 0 },
	{ "var_cfg_update_service_inter",   3,  &var_cfg_update_service_inter ,  0, 0 },
	{ NULL,                             0 , NULL ,                           0, 0 }
};


//最后一行必须是NULL,NULL,NULL 表示结束
acl::master_str_tbl acl::http_rpc_config::var_conf_str_tab [] = {

	{ "var_cfg_find_service",    "/nameserver/service_mgr/find",   &var_cfg_find_service    },
	{ "var_cfg_find_services",   "/nameserver/service_mgr/finds",  &var_cfg_find_services   },
	{ "var_cfg_add_service",     "/nameserver/service_mgr/add",    &var_cfg_add_service     },
	{ "var_cfg_del_service",     "/nameserver/service_mgr/del",    &var_cfg_del_service     },
	{ "var_cfg_del_service",     "/nameserver/service_mgr/list",   &var_cfg_list_services   },
	{ "var_cfg_nameserver",      "nameserver",					   &var_cfg_nameserver      },
	{ "var_cfg_nameserver_addr", "127.0.0.1:10080",                &var_cfg_nameserver_addr },
	{ "var_cfg_allow_clients",   "all",                            &var_cfg_allow_clients   },
	{ "var_cfg_redis_addr",	     "",                               &var_cfg_redis_addr      },
	{ "var_cfg_memcache_addr",   "127.0.0.1:11211",                &var_cfg_memcache_addr   },
	{ "var_cfg_server_addr",     "",                               &var_cfg_server_addr     },
	{ "var_cfg_server_name",     "nameserver",                     &var_cfg_server_name     },
	{ NULL,                      NULL,                             NULL }
};

//最后一行必须是0,0,0,0,0表示结束
acl::master_int64_tbl acl::http_rpc_config::var_conf_int64_tab [] = {

	{ NULL, 0 , NULL , 0, 0 }
};

//最后一行必须是0,0,0表示结束
acl::master_bool_tbl acl::http_rpc_config::var_conf_bool_tab [] = {

	{ NULL, 0 , NULL }
};
int main(int argc, char *argv[])
{
	
	//初始化 acl
	acl::acl_cpp_init();
	
	acl::log::stdout_open(true);

	nameserver server;

	if (argc >= 2 && strcmp(argv[1], "alone") == 0)
	{
		const char* addr = "0.0.0.0:10080";
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
	}else
		server.run_daemon(argc, argv);
		// acl_master 控制模式运行
	

	return 0;
}