#include "nameserver.h"

int main(int argc, char *argv[])
{
	//��ʼ�� Ĭ������
	//�����Ҫ����ӵ����ã���Ҫ�Լ�ʵ��һ��������Ϣ
	//��ʼ������
	acl::http_rpc_config::init_default_config();

	acl::http_rpc_server::get_instance().regist_service<nameserver::service_mgr>();

	return acl::http_rpc_server::get_instance().run(argc, argv);
}