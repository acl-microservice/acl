#pragma once

#ifndef APPLICATION_JSON
#define APPLICATION_JSON "application/json"
#endif//APPLICATION_JSON

#ifndef DEFINE_SERVICE_NAME
#define DEFINE_SERVICE_NAME(SERVER,MODULE,SERVICE) \
"/"#SERVER"/"#MODULE"/"#SERVICE
#endif //DEFINE_SERVICE_NAME

#include <vector>
#include <exception>
#include "acl_cpp/lib_acl.hpp"
#include "lib_acl.h"
#include "func_handle.hpp"
#include "msg_handlers.hpp"
#include "json_msg_handle.hpp"
#include "json_msg_handlers.hpp"
#include "http_rpc_servlet.h"
#include "http_rpc_client.h"
#include "access_list.h"
#include "service_register.h"
#include "rpc_context.h"
#include "http_rpc_server.h"
