#pragma once

namespace acl
{
	class http_rpc_client :
		public singleton2<http_rpc_client>
	{
	public:
		struct status_t 
		{
			status_t(int ret, const string &error)
				:ret_(ret),
				error_str_(error)
			{}
			status_t()
				:ret_(0),
				error_str_("")
			{}

			operator bool(){ return !ret_; }
			bool operator !() { return !!ret_; }

			int ret_;
			string error_str_;
		};

		/*
		* ��ӷ����ַ	
		*/
		void add_service_addr(const string &service_name, const string &addr);

		void add_service_addr(const string &service_name, const std::vector<string> &addr);

		/*
		*rpcԶ�̵���
		* @param service_name {const string&} ��������
		* @param req_type {const ReqType &} �����������
		* @param req_type {const ReqType &} ��Ӧ����
		* @return {status } ������� status == true ���ʾ���óɹ���
		*/
		template<class ReqType, class RespType>
		status_t json_call(const string &service_name, const ReqType &req_type, RespType &resp)
		{
			string buffer;

			status_t status = invoke_http_req2(service_name, APPLICATION_JSON, gson(req_type), buffer);
			if (!status)
				return status;
			json _json;
			_json.update(buffer.c_str());
			if (!_json.finish())
			{
				logger_error("resp json error: %s",buffer.c_str());
				return status_t( -1;	string("resp json error: ") += buffer.c_str() );
			}

			std::pair<bool, std::string> ret = gson(_json.get_root(), resp);
			if (!ret.first)
			{
				logger_error("gson error: %s", ret.second.c_str());
				return status_t(-1, ret.second.c_str());
			}
			return status_t();
		}

	private:
		http_rpc_client();

		void init();


		status_t invoke_http_req(const string &http_path,
			http_request_pool *pool,
			const char *context_type,
			const string&req_data,
			string &resp_buffer);

		status_t invoke_http_req2(const string &service_name,
			const char *context_type, 
			const string&req_data, 
			string &resp_buffer);

		bool get_connect_pool(const string &service_name, std::vector<connect_pool*> &pools);

		bool get_connect_pool2(const string &service_name, std::vector<connect_pool*> &pools);

		bool rpc_find_service_addr(const string &service_name, std::vector<string> &addrs);

	private:
		locker service_addrs_locker_;
		struct http_rpc_service_info
		{
			//{/server/module/service}
			string service_name_;
			std::vector<string> addrs_;
			unsigned int index_;
		};
		//service_name:addr
		std::map<string, http_rpc_service_info*> service_addrs_;
		//���ӳع���
		http_request_manager *conn_manager_;


	};
}