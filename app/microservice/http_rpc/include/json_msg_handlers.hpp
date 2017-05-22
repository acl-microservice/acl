#pragma once
namespace acl
{
	class json_msg_handlers : public msg_handlers
	{
	public:
		static json_msg_handlers &get_instance()
		{
			static json_msg_handlers instance;
			return instance;
		}

		template<class Context, class ReqType, class RespType>
		bool add(const char *func_name, Context *ctx,
			bool(Context::*func)(const ReqType &, RespType &))
		{
			acl::lock_guard guard(lock_);
			if (check_method_exist(func_name))
			{
				logger_error("function exist: %s", func_name);
				return false;
			}
			message_handles_.insert( std::make_pair(func_name,
				new json_msg_handle<Context, ReqType, RespType>(
					func_name, ctx, func)));

			return true;
		}
	private:
		json_msg_handlers()
		{
		}
		//
		json_msg_handlers(const json_msg_handlers &);
		json_msg_handlers &operator =(const json_msg_handlers &);

	};
}