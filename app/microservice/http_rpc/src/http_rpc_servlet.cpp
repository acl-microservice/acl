#include "http_rpc.h"

namespace acl
{
	http_rpc_servlet::http_rpc_servlet()
		:req_(NULL),
		resp_(NULL)
	{
	}

	HttpServletRequest * http_rpc_servlet::get_httpServletRequest()
	{
		return req_;
	}

	HttpServletResponse * http_rpc_servlet::get_httpServletResponse()
	{
		return resp_;
	}

	message_handle * http_rpc_servlet::get_message_handle(const string &message_type, const string &func_name)
	{
		if (message_type == "application/json")
		{
			return json_message_handle_register::
				get_instance().get_message_handle(func_name);
		}
		return NULL;
	}

	bool http_rpc_servlet::doGet(HttpServletRequest& req, HttpServletResponse& resp)
	{
		return doPost(req, resp);
	}

	bool http_rpc_servlet::doPost(HttpServletRequest& req, HttpServletResponse& resp)
	{
		message_handle *handle = get_message_handle(
						req.getContentType(), req.getPathInfo());
		if (!handle)
		{
			logger_error("can't find message handle for path: %s", 
				req.getPathInfo());
			return false;
		}

		string body;
		string buffer;

		if(read_http_body(req, body) == false)
			return false;
		resp_ = &resp;
		req_ = &req;
		bool ret = handle->invoke(body, buffer);
		req_ = NULL;
		resp_ = NULL;
		if (!resp.write(buffer))
			return false;
		return ret;
	}

	bool http_rpc_servlet::doUnknown(HttpServletRequest&, HttpServletResponse&)
	{
		logger_error("http Unknown error");
		return false;
	}

	bool http_rpc_servlet::doError(HttpServletRequest&, HttpServletResponse&)
	{
		logger_error("http error");
		return false;
	}

	bool http_rpc_servlet::read_http_body(HttpServletRequest &req, string &body)
	{
		long long int length = req.getContentLength();
		if (length <= 0)
		{
			logger_error("length: %lld invalid", length);
			return false;
		}
		acl::istream& in = req.getInputStream();
		char  buf[8192];
		int   ret;
		size_t n;

		while (length > 0)
		{
			n = (size_t)length > sizeof(buf) - 1
				? sizeof(buf) - 1 : (size_t)length;
			ret = in.read(buf, n, false);
			if (ret == -1)
			{
				logger_error("read json body error");
				return false;
			}
			body.append(buf, ret);
			length -= ret;
		}
		return true;
	}

}
