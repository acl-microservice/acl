#include "http_rpc.h"

namespace acl
{
	namespace http_rpc_config
	{
		master_int_tbl *var_conf_int_tab;
		master_int64_tbl  *var_conf_int64_tab;
		master_str_tbl  *var_conf_str_tab;
		master_bool_tbl  *var_conf_bool_tab;

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
		char *var_cfg_server_addr;//��Ҫ�Լ�����
		char *var_cfg_server_name;//��Ҫ�Լ�����
		char *var_cfg_nameserver;

		//Ĭ������
		//�û���Ҫcopy �����ʼ�����룬����Լ��Ĵ�����ȥ
		//ʵ���Լ���������Ϣ
		//��д����Ĭ���ǿյģ�����ֱ��ʹ��
		void init_default_config()
		{
			//���һ�б�����NULL,0 ,NULL,0, 0��ʾ����
			var_conf_int_tab = new master_int_tbl[7]{
				{ "var_cfg_redis_conn_timeout", 30, &var_cfg_redis_conn_timeout, 0, 0 },
				{ "var_cfg_redis_rw_timeout", 30, &var_cfg_redis_rw_timeout, 0, 0 },
				{ "var_cfg_rpc_conn_check_inter", 1,&var_cfg_rpc_conn_check_inter, 0, 0 },
				{ "var_cfg_rpc_conn_check_timeout", 5,&var_cfg_rpc_conn_check_timeout, 0, 0},
				{ "var_cfg_register_service_inter", 3,&var_cfg_regist_service_inter ,0, 0},
				{ "var_cfg_update_service_inter", 3,&var_cfg_update_service_inter ,0, 0 },

				{ NULL, 0 , NULL , 0, 0 }
			};

			//���һ�б�����NULL,NULL,NULL ��ʾ����
			var_conf_str_tab = new master_str_tbl[12]{
				{ "var_cfg_allow_clients","all",&var_cfg_allow_clients},
				{ "var_cfg_redis_addr", "", &var_cfg_redis_addr },
				{ "var_cfg_memcache_addr", "", &var_cfg_memcache_addr },
				{ "var_cfg_find_service", "/nameservice/service_mgr/find",&var_cfg_find_service },
				{ "var_cfg_find_services", "/nameservice/service_mgr/finds",&var_cfg_find_services },
				{ "var_cfg_add_service", "/nameservice/service_mgr/add",&var_cfg_add_service },
				{ "var_cfg_del_service", "/nameservice/service_mgr/del",&var_cfg_del_service},
				{ "var_cfg_server_addr", "",&var_cfg_server_addr},
				{ "var_cfg_nameserver_name", "nameserver",&var_cfg_nameserver},
				{ "var_cfg_server_name", "", &var_cfg_server_name},
				{ "var_cfg_nameserver", "nameserver", &var_cfg_nameserver},
				{ NULL, NULL, NULL }
			};
			var_conf_int64_tab = new master_int64_tbl[1]{
				{ 0, 0 , 0 , 0, 0 }
			};

			var_conf_bool_tab = new master_bool_tbl[1]{
				{ 0, 0 , 0 }
			};
		}
	}
}
