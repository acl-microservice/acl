#pragma once
#include "nameserver_proto.h"
namespace acl
{
	/*
		所以的service都要继承这个类，实现init方法。
		init 可以用来初始化一些资源，这个是函数是线程安全的。
		这个架构是基于acl::master_threads 模型，提供服务接口会可能被多线程同时访问。
		也就说 用户自己的数据 需要自己作多线程安全处理。
	*/
	class rpc_context
	{
	public:
		virtual ~rpc_context();
		static HttpServletRequest &getHttpServletRequest();
		virtual void init() = 0;
	};



	/*class nameservice:
		public rpc_context
	{
	public:
		nameservice();
		bool add_service(const 
			nameserver_proto::add_services_req &req, 
			nameserver_proto::add_services_resp &resp );
	private:
		void init();
	};*/
}

