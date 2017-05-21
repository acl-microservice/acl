#pragma once
namespace acl
{
	class http_rpc_client :
		public singleton2<http_rpc_client>
	{
	public:
		struct status 
		{
			status(int ret, const string &error)
				:ret_(ret),
				error_str_(error)
			{}
			status()
				:ret_(0),
				error_str_("")
			{}

			operator bool(){ return !ret_; }
			bool operator !() { return !!ret_; }

			int ret_;
			string error_str_;
		};

		/*
		* 添加服务发现 地址	
		*/
		void add_nameservice_addr(const string &addr)
		{
			nameservice_addrs_.push_back(addr);
		}


		/*
		*rpc远程调用
		* @param service_name {const string&} 服务名称
		* @param req_type {const ReqType &} 请求参数对象
		* @param req_type {const ReqType &} 响应对象
		* @return {status } 如果返回 status == true 则表示调用成功。
		*/
		template<class ReqType, class RespType>
		status json_call(const string &service_name, const ReqType &req_type, RespType &resp)
		{
			string buffer;
			status ret = invoke_http_req(gson(req_type),"", buffer);
			if (!ret)
				return ret;
			json _json;
			_json.update(buffer.c_str());
			if (!_json.finish())
			{
				logger_error("resp json error: %s",buffer.c_str());
				return status( -1;	string("resp json error") += buffer.c_str() );
			}
			std::pair<bool, std::string> gson_ret = gson(_json.get_root(), resp);
			if (!gson_ret.first)
			{
				logger_error("gson error: %s", gson_ret.second.c_str());
				return status(-1, gson_ret.second.c_str());
			}
			return status();
		}
	private:
		http_rpc_client();

		void init();

		status invoke_http_req(const string &service_name, 
			const char *context_type, 
			const string&req_data,  string &resp_buffer);

		connect_pool *get_connect_pool(const string &service_name);


	private:
		locker locker_;
		struct rpc_service_addr
		{
			rpc_service_addr()
				:faileds_(0),
				successes_(0)
			{
			}

			string service_name_;
			std::vector<string *> addrs_;
			unsigned long long faileds_;
			unsigned long long successes_;
			int index_;
		};
		//service_name:addr
		std::map<string, rpc_service_addr*> service_addrs_;

		//连接池管理
		connect_manager *conn_manager_;

		string nameserver_addr_;

		std::vector<string> nameservice_addrs_;
	};
}