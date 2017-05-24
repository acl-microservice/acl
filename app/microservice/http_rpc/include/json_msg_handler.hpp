#pragma once
namespace acl
{
	template<class Context, class ReqType, class RespType>
	class json_msg_handler: public func_handler
	{
	public:
		typedef bool (Context::*func_t)(const ReqType &, RespType&);

		json_msg_handler(const string &func_name, Context *ctx, func_t fun)
			:context_(ctx),
			function_(fun)
		{
			func_name_ = func_name;
		}

		virtual bool invoke(const string &data, string &buffer)
		{
			ReqType req;
			RespType resp;

			//data --> req obj
			std::pair<bool, std::string> status = gson(data, req);
			if (!status.first)
			{
				logger_error("gson error: %s", status.second.c_str());
				return false;
			}

			//invoke 
			bool ret = (context_->*function_)(req, resp);

			//resp obj --> string
			buffer = gson(resp);
			return ret;
		}

	private:
		Context *context_;
		func_t function_;
	};
}