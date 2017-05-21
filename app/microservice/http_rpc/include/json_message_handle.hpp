#pragma once
namespace acl
{
	//gson template

	template<class Type>
	inline acl::string gson(const Type &$obj);
	template<class Type>
	inline acl::json_node& gson(acl::json &$json, const Type&$obj);
	template<class Type>
	inline acl::json_node& gson(acl::json &$json, const Type*$obj);
	template<class Type>
	inline std::pair<bool, std::string> gson(acl::json_node &$node, Type&$obj);
	template<class Type>
	inline std::pair<bool, std::string> gson(acl::json_node &$node, Type*$obj);


	//
	template<class RpcContext, class ReqType, class RespType>
	class json_message_handle: public message_handle
	{
	public:
		typedef bool (RpcContext::*function_t)(const ReqType &, RespType&);

		json_message_handle(const string &func_name, RpcContext *context, function_t fun)
			:context_(context),
			function_(fun)
		{
			func_name_ = func_name;
		}

		virtual bool invoke(const string &data, string &buffer)
		{
			json _json;
			_json.update(data.c_str());
			if (!_json.finish())
			{
				logger_error("json not finish error");
				return false;
			}

			ReqType req;
			RespType resp;
			std::pair<bool, std::string> status = gson(_json.get_root(), data);
			if (!status.first)
			{
				logger_error("gson error: %s",ret.second.c_str());
				return false;
			}
			bool ret = context_->function_(req, resp);
			buffer = gson(resp);
			return ret;
		}

	private:
		RpcContext *context_;
		function_t function_;
	};
}