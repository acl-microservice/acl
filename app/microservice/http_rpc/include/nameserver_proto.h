#pragma once
#include <vector>
#include <string>
namespace nameserver_proto
{
	struct service_info
	{
		acl::string service_name;
		std::vector<acl::string> server_addrs;
	};

	/*
	json:
	{
		"service_names":[
			"/server_name/module/service1",
			"/server_name/module/service2"
		],
		"server_addr":"127.0.0.1:10038"
	}
	{
		"result":"ok"
	}
	*/
	struct  add_services_req
	{
		std::vector<acl::string> service_names;
		acl::string server_addr;
	};

	struct add_services_resp
	{
		acl::string result;
	};


	/*
	json:
	{
		"service_names":[
			"/server_name/module/service1",
			"/server_name/module/service2"
		],
		"server_addr":"127.0.0.1:10038"
	}
	response
	{
	"result":"ok"
	}
	*/
	struct del_services_req
	{
		std::vector<acl::string> service_names;
		acl::string server_addr;
	};

	struct del_services_resp
	{
		acl::string result;
	};


	/*
	json:
	{
		"service_name":"/server_name/module/service"
	}
	
	{
		"status":"ok",
		"server_addrs":["127.0.0.1:10038","127.0.0.1:10039"]
	}
	*/

	struct find_service_req
	{
		acl::string service_name;
	};

	struct find_service_resp
	{
		acl::string status;
		acl::string service_name;
		std::vector<acl::string> server_addrs;
	};
	/*
	json:
	{
		"service_names":["b","a"]
	}

	{
		"service_infos":{
			"service_name":{
				"service_name":"service_name",
				"server_addrs":["120.0.0.1:9001","127.0.0.1:9002"]
			}
		}
	}
	*/
	struct find_services_req
	{
		std::vector<acl::string> service_names;
	};

	struct find_services_resp
	{
		std::map<acl::string, service_info> service_infos;
	};

	/*
	json:
	{
		"services":[
			{
				"service_name":/server_name/module/service",
				"server_addrs":["127.0.0.1:10038","127.0.0.1:10039"]
			}
		]
	}
	*/

	
	struct list_services_resp
	{
		std::vector<service_info> services;
	};
}