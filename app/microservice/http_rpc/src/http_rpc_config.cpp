#include "http_rpc.h"

namespace acl
{
	namespace http_rpc_config
	{
		//���ö���
		int var_cfg_redis_conn_timeout;
		int var_cfg_redis_rw_timeout;
		int var_cfg_rpc_conn_check_inter;
		int var_cfg_rpc_conn_check_timeout;
		int var_cfg_regist_service_inter;
		int var_cfg_update_service_inter;
		int var_cfg_rw_timeout;

		char *var_cfg_redis_addr;
		char *var_cfg_memcache_addr;
		char *var_cfg_allow_clients;
		char *var_cfg_find_service;
		char *var_cfg_find_services;
		char *var_cfg_add_service;
		char *var_cfg_del_service;
		char *var_cfg_list_services;
		char *var_cfg_server_addr;//��Ҫ�Լ�����
		char *var_cfg_server_name;//��Ҫ�Լ�����
		char *var_cfg_nameserver;
		char *var_cfg_nameserver_addr;//��Ҫ�Լ�����
	}
}
