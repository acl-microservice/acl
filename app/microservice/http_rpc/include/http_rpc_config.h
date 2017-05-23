#pragma once
namespace acl
{
	namespace http_rpc_config
	{
		void init_default_config();

		//http_rpc ���ñ�
		extern master_int_tbl *var_conf_int_tab;
		extern master_int64_tbl  *var_conf_int64_tab;
		extern master_str_tbl  *var_conf_str_tab;
		extern master_bool_tbl  *var_conf_bool_tab;

		//nameserver������
		//Ĭ�ϣ�nameserver
		extern char *var_cfg_nameserver;

		//server ��ַ
		//�����ַ��Ҫ�ŵ� nameservice ����ȥ����������service �ɼ���
		//��ʽ ip:port 
		extern char *var_cfg_server_addr;

		//redis ��Ⱥ��ַ
		extern char *var_cfg_redis_addr;

		//redis ���ӳ�ʱʱ�� ��
		extern int var_cfg_redis_conn_timeout;

		//redis ��д��ʱʱ�� ��
		extern int var_cfg_redis_rw_timeout;

		//memcache �����ַ
		extern char *var_cfg_memcache_addr;

		//������ all Ϊ����client �����Է���
		extern char *var_cfg_allow_clients;

		//rpc socket ��д��ʱʱ�� ��
		extern int var_cfg_rw_timeout;

		//namserver ���� ��ѯ����Ľӿ�����
		//Ĭ���� /nameserver/service_mgr/find ����Ҫ�޸�
		extern char * var_cfg_find_service;

		//namserver ���� ��ѯ����Ľӿ�����
		//Ĭ���� /nameserver/service_mgr/finds ����Ҫ�޸�
		extern char * var_cfg_find_services;


		//namserver ���� ��ӷ���Ľӿ�����
		//Ĭ���� /nameserver/service_mgr/add ����Ҫ�޸�
		extern char *var_cfg_add_service;

		//namserver ���� ɾ������Ľӿ�����
		//Ĭ���� /nameserver/service_mgr/del ����Ҫ�޸�
		extern char *var_cfg_del_service;

		//http_rpc ���ӳ� ������ӽ����ļ��
		//������ 1 ��
		extern int var_cfg_rpc_conn_check_inter;

		//http_rpc ���ӳ� ������ӽ����ĳ�ʱʱ��
		//������ 5��
		extern int var_cfg_rpc_conn_check_timeout;

		//ע����� �����ļ��
		//������ 3����
		extern int var_cfg_regist_service_inter;

		//����service address ʱ����
		//������ 3����
		extern int var_cfg_update_service_inter;
	}
		
}