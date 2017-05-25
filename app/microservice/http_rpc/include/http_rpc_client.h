#pragma once

namespace acl
{
	class http_rpc_client:public thread
	{
	public:
		static http_rpc_client &get_instance()
		{
			static http_rpc_client instance;
			return instance;
		}
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
		* 添加服务地址	
		*/
		void add_service_addr(const string &addr,
			const string &service_path);

		void add_service_addr(const string &addr, 
			const std::vector<string> &service_path);

		/*
		*rpc远程调用
		* @param service_name {const string&} 服务名称
		* @param req_type {const ReqType &} 请求参数对象
		* @param req_type {const ReqType &} 响应对象
		* @return {status } 如果返回 status == true 则表示调用成功。
		*/
		template<class ReqType, class RespType>
		status_t json_call(
			const string &service_name, 
			const ReqType &req_type, 
			RespType &resp)
		{
			string buffer;

			status_t status = invoke_http_req(service_name, 
				"application/json",
				gson(req_type), 
				buffer);
			if (!status)
				return status;

			std::pair<bool, std::string> ret = gson(buffer, resp);
			if (!ret.first)
			{
				logger_error("gson error: %s", ret.second.c_str());
				return status_t(-1, ret.second.c_str());
			}
			return status_t();
		}

	private:
		http_rpc_client();
		http_rpc_client(const http_rpc_client&);
		http_rpc_client &operator =(const http_rpc_client&);

		void init();

		status_t invoke_http_req(
			const string &service_path,
			http_request_pool *pool,
			const char *context_type,
			const string&req_data,
			string &resp_buffer);

		status_t invoke_http_req(
			const string &service_path,
			const char *context_type, 
			const string&req_data, 
			string &resp_buffer);

		bool find_connect_pool(
			const string &service_name, 
			std::vector<connect_pool*> &pools);

		bool get_connect_pool(
			const string &service_name,
			std::vector<connect_pool*> &pools);

		bool rpc_find_service_addr(
			const string &service_name, 
			std::vector<string> &addrs);
		
		void update_services_addr();

		virtual void *run();

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
		//连接池管理
		http_request_manager *conn_manager_;


	};
}