#pragma once
namespace acl
{
	//gson template

	template<class Type>
	inline acl::string gson(const Type &);
	template<class Type>
	inline acl::json_node& gson(acl::json &, const Type&);
	template<class Type>
	inline acl::json_node& gson(acl::json &, const Type*);
	template<class Type>
	inline std::pair<bool, std::string>gson(acl::json_node &, Type&);
	template<class Type>
	inline std::pair<bool, std::string> gson(acl::json_node &, Type*);
	template<class Type>
	inline std::pair<bool, std::string> gson(const acl::string&, Type &);

	//
	template<class Context, class ReqType, class RespType>
	class json_msg_handle: public func_handle
	{
	public:
		typedef bool (Context::*func_t)(const ReqType &, RespType&);

		json_msg_handle(const string &func_name, Context *ctx, func_t fun)
			:context_(ctx),
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
			
			std::pair<bool, std::string> status = 
				gson(_json.get_root(), data);

			if (!status.first)
			{
				logger_error("gson error: %s", status.second.c_str());
				return false;
			}
			bool ret = (context_->*function_)(req, resp);
			buffer = gson(resp);
			return ret;
		}

	private:
		Context *context_;
		func_t function_;
	};
}