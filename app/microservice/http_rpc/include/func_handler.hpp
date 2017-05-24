#pragma once
namespace acl
{
	/*
	* ��Ϣ�������Ļ��ࡣ���༯�ɣ���ʵ��invoke ������
	* json_msg_handler �̳��ˣ���ʵ����invoke�������Ϳ��Դ���json��Ϣ
	*/
	class func_handler
	{
	public:
		func_handler();
		
		string func_name();

		/*
		* ������Ϣ�Ľӿ�
		* @param {const string@} req ���緢�͹���������
		* @param {string@} resp  ��Ҫ���ͻ�ȥ����Ӧ��
		# @return {bool} false ����Ͽ����ӣ�true��������
		*/
		virtual bool invoke(const string &req, string &resp) = 0;

	protected:
		string func_name_;
	};
}