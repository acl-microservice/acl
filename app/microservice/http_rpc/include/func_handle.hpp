#pragma once
namespace acl
{
	class func_handle
	{
	public:
		func_handle();
		
		string func_name();
		virtual bool invoke(const string &req, string &resp) = 0;
	protected:
		string func_name_;
	};
}