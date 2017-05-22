#pragma once
#include <set>
namespace acl
{
	class service_register: public acl::thread
	{
	public:
		static service_register& get_instance();

		bool regist(const string &addr_, const string& service_name);

		bool del(const string &addr_, const string& service_name);

		void stop();
	private:
		service_register();
		service_register(const service_register&);
		service_register &operator= (const service_register&);

		void rpc_regist_service(const string &addr_, 
			const std::vector<string>& service_names);

		virtual void* run();

		bool is_stop_;

		locker locker_;
		//addr:service
		std::map<string, std::set<string>> services;
	};
}