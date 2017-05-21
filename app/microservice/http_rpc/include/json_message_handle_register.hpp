#pragma once
namespace acl
{
	class json_message_handle_register : public message_handle_register,
		public singleton2<json_message_handle_register>

	{
	public:
		template<class Context, class ReqType, class RespType>
		bool regist(const char *func_name, Context *ctx,
			bool(Context::*func)(const ReqType &, RespType &))
		{
			acl::lock_guard guard(lock_);
			if (check_method_exist(func_name))
			{
				logger_error("function exist: %s", func_name);
				return false;
			}
			message_handles_.insert(new MessageHandleImpl<
				Context, ReqType, RespType>(func_name, ctx, func));

			return true;
		}
	};
}