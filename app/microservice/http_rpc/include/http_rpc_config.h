#pragma once
namespace acl
{
	namespace http_rpc_config
	{
		void init_default_config();

		//http_rpc 配置表单
		extern master_int_tbl *var_conf_int_tab;
		extern master_int64_tbl  *var_conf_int64_tab;
		extern master_str_tbl  *var_conf_str_tab;
		extern master_bool_tbl  *var_conf_bool_tab;

		//nameserver的名称
		//默认：nameserver
		extern char *var_cfg_nameserver;

		//server 地址
		//这个地址需要放到 nameservice 上面去，被其他的service 可见。
		//格式 ip:port 
		extern char *var_cfg_server_addr;

		//redis 集群地址
		extern char *var_cfg_redis_addr;

		//redis 连接超时时间 秒
		extern int var_cfg_redis_conn_timeout;

		//redis 读写超时时间 秒
		extern int var_cfg_redis_rw_timeout;

		//memcache 服务地址
		extern char *var_cfg_memcache_addr;

		//白名单 all 为任意client 都可以访问
		extern char *var_cfg_allow_clients;

		//rpc socket 读写超时时间 秒
		extern int var_cfg_rw_timeout;

		//namserver 服务 查询服务的接口名字
		//默认是 /nameserver/service_mgr/find 不需要修改
		extern char * var_cfg_find_service;

		//namserver 服务 查询服务的接口名字
		//默认是 /nameserver/service_mgr/finds 不需要修改
		extern char * var_cfg_find_services;


		//namserver 服务 添加服务的接口名字
		//默认是 /nameserver/service_mgr/add 不需要修改
		extern char *var_cfg_add_service;

		//namserver 服务 删除服务的接口名字
		//默认是 /nameserver/service_mgr/del 不需要修改
		extern char *var_cfg_del_service;

		//http_rpc 连接池 坚持连接健康的间隔
		//建议是 1 秒
		extern int var_cfg_rpc_conn_check_inter;

		//http_rpc 连接池 坚持连接健康的超时时间
		//建议是 5秒
		extern int var_cfg_rpc_conn_check_timeout;

		//注册服务 心跳的间隔
		//建议是 3秒钟
		extern int var_cfg_regist_service_inter;

		//更新service address 时间间隔
		//建议是 3秒钟
		extern int var_cfg_update_service_inter;
	}
		
}