#pragma once
namespace acl
{
	class message_handle
	{
	public:
		message_handle()
		{

		}
		string function_name()
		{
			return func_name_;
		}

		virtual bool invoke(const string &req, string &resp) = 0;
	protected:
		string func_name_;
	};
}