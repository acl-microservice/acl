#include "nameserver.h"

int main(int argc, char *argv[])
{
	//初始化 默认配置
	//如果需要的添加的配置，需要自己实现一个配置信息
	//初始化函数
	acl::http_rpc_config::init_default_config();

	acl::http_rpc_server::get_instance().regist_service<nameserver::service_mgr>();

	return acl::http_rpc_server::get_instance().run(argc, argv);
}