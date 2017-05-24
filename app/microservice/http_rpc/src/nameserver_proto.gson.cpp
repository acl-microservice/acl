#include "http_rpc.h"
#include "nameserver_proto.h"
#include "nameserver_proto.gson.h"
#include "acl_cpp/serialize/gson_helper.ipp"
namespace acl
{
    acl::json_node& gson(acl::json &$json, const nameserver_proto::add_services_req &$obj)
    {
        acl::json_node &$node = $json.create_node();

        if (check_nullptr($obj.service_names))
            $node.add_null("service_names");
        else
            $node.add_child("service_names", acl::gson($json, $obj.service_names));

        if (check_nullptr($obj.server_addr))
            $node.add_null("server_addr");
        else
            $node.add_text("server_addr", acl::get_value($obj.server_addr));


        return $node;
    }
    
    acl::json_node& gson(acl::json &$json, const nameserver_proto::add_services_req *$obj)
    {
        return gson ($json, *$obj);
    }


    acl::string gson(const nameserver_proto::add_services_req &$obj)
    {
        acl::json $json;
        acl::json_node &$node = acl::gson ($json, $obj);
        return $node.to_string ();
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::add_services_req &$obj)
    {
        acl::json_node *service_names = $node["service_names"];
        acl::json_node *server_addr = $node["server_addr"];
        std::pair<bool, std::string> $result;

        if(!service_names ||!service_names->get_obj()||!($result = gson(*service_names->get_obj(), &$obj.service_names), $result.first))
            return std::make_pair(false, "required [nameserver_proto::add_services_req.service_names] failed:{"+$result.second+"}");
     
        if(!server_addr ||!($result = gson(*server_addr, &$obj.server_addr), $result.first))
            return std::make_pair(false, "required [nameserver_proto::add_services_req.server_addr] failed:{"+$result.second+"}");
     
        return std::make_pair(true,"");
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::add_services_req *$obj)
    {
        return gson($node, *$obj);
    }


    std::pair<bool,std::string> gson(const acl::string &$str, nameserver_proto::add_services_req &$obj)
    {
        acl::json _json;
        _json.update($str.c_str());
        if (!_json.finish())
        {
            return std::make_pair(false, "json not finish error");
        }
        return gson(_json.get_root(), $obj);
    }


    acl::json_node& gson(acl::json &$json, const nameserver_proto::add_services_resp &$obj)
    {
        acl::json_node &$node = $json.create_node();

        if (check_nullptr($obj.result))
            $node.add_null("result");
        else
            $node.add_text("result", acl::get_value($obj.result));


        return $node;
    }
    
    acl::json_node& gson(acl::json &$json, const nameserver_proto::add_services_resp *$obj)
    {
        return gson ($json, *$obj);
    }


    acl::string gson(const nameserver_proto::add_services_resp &$obj)
    {
        acl::json $json;
        acl::json_node &$node = acl::gson ($json, $obj);
        return $node.to_string ();
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::add_services_resp &$obj)
    {
        acl::json_node *result = $node["result"];
        std::pair<bool, std::string> $result;

        if(!result ||!($result = gson(*result, &$obj.result), $result.first))
            return std::make_pair(false, "required [nameserver_proto::add_services_resp.result] failed:{"+$result.second+"}");
     
        return std::make_pair(true,"");
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::add_services_resp *$obj)
    {
        return gson($node, *$obj);
    }


    std::pair<bool,std::string> gson(const acl::string &$str, nameserver_proto::add_services_resp &$obj)
    {
        acl::json _json;
        _json.update($str.c_str());
        if (!_json.finish())
        {
            return std::make_pair(false, "json not finish error");
        }
        return gson(_json.get_root(), $obj);
    }


    acl::json_node& gson(acl::json &$json, const nameserver_proto::del_services_req &$obj)
    {
        acl::json_node &$node = $json.create_node();

        if (check_nullptr($obj.service_names))
            $node.add_null("service_names");
        else
            $node.add_child("service_names", acl::gson($json, $obj.service_names));

        if (check_nullptr($obj.server_addr))
            $node.add_null("server_addr");
        else
            $node.add_text("server_addr", acl::get_value($obj.server_addr));


        return $node;
    }
    
    acl::json_node& gson(acl::json &$json, const nameserver_proto::del_services_req *$obj)
    {
        return gson ($json, *$obj);
    }


    acl::string gson(const nameserver_proto::del_services_req &$obj)
    {
        acl::json $json;
        acl::json_node &$node = acl::gson ($json, $obj);
        return $node.to_string ();
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::del_services_req &$obj)
    {
        acl::json_node *service_names = $node["service_names"];
        acl::json_node *server_addr = $node["server_addr"];
        std::pair<bool, std::string> $result;

        if(!service_names ||!service_names->get_obj()||!($result = gson(*service_names->get_obj(), &$obj.service_names), $result.first))
            return std::make_pair(false, "required [nameserver_proto::del_services_req.service_names] failed:{"+$result.second+"}");
     
        if(!server_addr ||!($result = gson(*server_addr, &$obj.server_addr), $result.first))
            return std::make_pair(false, "required [nameserver_proto::del_services_req.server_addr] failed:{"+$result.second+"}");
     
        return std::make_pair(true,"");
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::del_services_req *$obj)
    {
        return gson($node, *$obj);
    }


    std::pair<bool,std::string> gson(const acl::string &$str, nameserver_proto::del_services_req &$obj)
    {
        acl::json _json;
        _json.update($str.c_str());
        if (!_json.finish())
        {
            return std::make_pair(false, "json not finish error");
        }
        return gson(_json.get_root(), $obj);
    }


    acl::json_node& gson(acl::json &$json, const nameserver_proto::del_services_resp &$obj)
    {
        acl::json_node &$node = $json.create_node();

        if (check_nullptr($obj.result))
            $node.add_null("result");
        else
            $node.add_text("result", acl::get_value($obj.result));


        return $node;
    }
    
    acl::json_node& gson(acl::json &$json, const nameserver_proto::del_services_resp *$obj)
    {
        return gson ($json, *$obj);
    }


    acl::string gson(const nameserver_proto::del_services_resp &$obj)
    {
        acl::json $json;
        acl::json_node &$node = acl::gson ($json, $obj);
        return $node.to_string ();
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::del_services_resp &$obj)
    {
        acl::json_node *result = $node["result"];
        std::pair<bool, std::string> $result;

        if(!result ||!($result = gson(*result, &$obj.result), $result.first))
            return std::make_pair(false, "required [nameserver_proto::del_services_resp.result] failed:{"+$result.second+"}");
     
        return std::make_pair(true,"");
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::del_services_resp *$obj)
    {
        return gson($node, *$obj);
    }


    std::pair<bool,std::string> gson(const acl::string &$str, nameserver_proto::del_services_resp &$obj)
    {
        acl::json _json;
        _json.update($str.c_str());
        if (!_json.finish())
        {
            return std::make_pair(false, "json not finish error");
        }
        return gson(_json.get_root(), $obj);
    }


    acl::json_node& gson(acl::json &$json, const nameserver_proto::find_service_req &$obj)
    {
        acl::json_node &$node = $json.create_node();

        if (check_nullptr($obj.service_name))
            $node.add_null("service_name");
        else
            $node.add_text("service_name", acl::get_value($obj.service_name));


        return $node;
    }
    
    acl::json_node& gson(acl::json &$json, const nameserver_proto::find_service_req *$obj)
    {
        return gson ($json, *$obj);
    }


    acl::string gson(const nameserver_proto::find_service_req &$obj)
    {
        acl::json $json;
        acl::json_node &$node = acl::gson ($json, $obj);
        return $node.to_string ();
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::find_service_req &$obj)
    {
        acl::json_node *service_name = $node["service_name"];
        std::pair<bool, std::string> $result;

        if(!service_name ||!($result = gson(*service_name, &$obj.service_name), $result.first))
            return std::make_pair(false, "required [nameserver_proto::find_service_req.service_name] failed:{"+$result.second+"}");
     
        return std::make_pair(true,"");
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::find_service_req *$obj)
    {
        return gson($node, *$obj);
    }


    std::pair<bool,std::string> gson(const acl::string &$str, nameserver_proto::find_service_req &$obj)
    {
        acl::json _json;
        _json.update($str.c_str());
        if (!_json.finish())
        {
            return std::make_pair(false, "json not finish error");
        }
        return gson(_json.get_root(), $obj);
    }


    acl::json_node& gson(acl::json &$json, const nameserver_proto::find_service_resp &$obj)
    {
        acl::json_node &$node = $json.create_node();

        if (check_nullptr($obj.status))
            $node.add_null("status");
        else
            $node.add_text("status", acl::get_value($obj.status));

        if (check_nullptr($obj.service_name))
            $node.add_null("service_name");
        else
            $node.add_text("service_name", acl::get_value($obj.service_name));

        if (check_nullptr($obj.server_addrs))
            $node.add_null("server_addrs");
        else
            $node.add_child("server_addrs", acl::gson($json, $obj.server_addrs));


        return $node;
    }
    
    acl::json_node& gson(acl::json &$json, const nameserver_proto::find_service_resp *$obj)
    {
        return gson ($json, *$obj);
    }


    acl::string gson(const nameserver_proto::find_service_resp &$obj)
    {
        acl::json $json;
        acl::json_node &$node = acl::gson ($json, $obj);
        return $node.to_string ();
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::find_service_resp &$obj)
    {
        acl::json_node *status = $node["status"];
        acl::json_node *service_name = $node["service_name"];
        acl::json_node *server_addrs = $node["server_addrs"];
        std::pair<bool, std::string> $result;

        if(!status ||!($result = gson(*status, &$obj.status), $result.first))
            return std::make_pair(false, "required [nameserver_proto::find_service_resp.status] failed:{"+$result.second+"}");
     
        if(service_name)
            gson(*service_name, &$obj.service_name);
     
        if(server_addrs&& server_addrs->get_obj())
             gson(*server_addrs->get_obj(), &$obj.server_addrs);
     
        return std::make_pair(true,"");
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::find_service_resp *$obj)
    {
        return gson($node, *$obj);
    }


    std::pair<bool,std::string> gson(const acl::string &$str, nameserver_proto::find_service_resp &$obj)
    {
        acl::json _json;
        _json.update($str.c_str());
        if (!_json.finish())
        {
            return std::make_pair(false, "json not finish error");
        }
        return gson(_json.get_root(), $obj);
    }


    acl::json_node& gson(acl::json &$json, const nameserver_proto::find_services_req &$obj)
    {
        acl::json_node &$node = $json.create_node();

        if (check_nullptr($obj.service_names))
            $node.add_null("service_names");
        else
            $node.add_child("service_names", acl::gson($json, $obj.service_names));


        return $node;
    }
    
    acl::json_node& gson(acl::json &$json, const nameserver_proto::find_services_req *$obj)
    {
        return gson ($json, *$obj);
    }


    acl::string gson(const nameserver_proto::find_services_req &$obj)
    {
        acl::json $json;
        acl::json_node &$node = acl::gson ($json, $obj);
        return $node.to_string ();
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::find_services_req &$obj)
    {
        acl::json_node *service_names = $node["service_names"];
        std::pair<bool, std::string> $result;

        if(!service_names ||!service_names->get_obj()||!($result = gson(*service_names->get_obj(), &$obj.service_names), $result.first))
            return std::make_pair(false, "required [nameserver_proto::find_services_req.service_names] failed:{"+$result.second+"}");
     
        return std::make_pair(true,"");
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::find_services_req *$obj)
    {
        return gson($node, *$obj);
    }


    std::pair<bool,std::string> gson(const acl::string &$str, nameserver_proto::find_services_req &$obj)
    {
        acl::json _json;
        _json.update($str.c_str());
        if (!_json.finish())
        {
            return std::make_pair(false, "json not finish error");
        }
        return gson(_json.get_root(), $obj);
    }


    acl::json_node& gson(acl::json &$json, const nameserver_proto::find_services_resp &$obj)
    {
        acl::json_node &$node = $json.create_node();

        if (check_nullptr($obj.status))
            $node.add_null("status");
        else
            $node.add_text("status", acl::get_value($obj.status));

        if (check_nullptr($obj.service_infos))
            $node.add_null("service_infos");
        else
            $node.add_child("service_infos", acl::gson($json, $obj.service_infos));


        return $node;
    }
    
    acl::json_node& gson(acl::json &$json, const nameserver_proto::find_services_resp *$obj)
    {
        return gson ($json, *$obj);
    }


    acl::string gson(const nameserver_proto::find_services_resp &$obj)
    {
        acl::json $json;
        acl::json_node &$node = acl::gson ($json, $obj);
        return $node.to_string ();
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::find_services_resp &$obj)
    {
        acl::json_node *status = $node["status"];
        acl::json_node *service_infos = $node["service_infos"];
        std::pair<bool, std::string> $result;

        if(!status ||!($result = gson(*status, &$obj.status), $result.first))
            return std::make_pair(false, "required [nameserver_proto::find_services_resp.status] failed:{"+$result.second+"}");
     
        if(!service_infos ||!service_infos->get_obj()||!($result = gson(*service_infos->get_obj(), &$obj.service_infos), $result.first))
            return std::make_pair(false, "required [nameserver_proto::find_services_resp.service_infos] failed:{"+$result.second+"}");
     
        return std::make_pair(true,"");
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::find_services_resp *$obj)
    {
        return gson($node, *$obj);
    }


    std::pair<bool,std::string> gson(const acl::string &$str, nameserver_proto::find_services_resp &$obj)
    {
        acl::json _json;
        _json.update($str.c_str());
        if (!_json.finish())
        {
            return std::make_pair(false, "json not finish error");
        }
        return gson(_json.get_root(), $obj);
    }


    acl::json_node& gson(acl::json &$json, const nameserver_proto::list_services_req &$obj)
    {
        acl::json_node &$node = $json.create_node();

        if (check_nullptr($obj.path))
            $node.add_null("path");
        else
            $node.add_text("path", acl::get_value($obj.path));


        return $node;
    }
    
    acl::json_node& gson(acl::json &$json, const nameserver_proto::list_services_req *$obj)
    {
        return gson ($json, *$obj);
    }


    acl::string gson(const nameserver_proto::list_services_req &$obj)
    {
        acl::json $json;
        acl::json_node &$node = acl::gson ($json, $obj);
        return $node.to_string ();
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::list_services_req &$obj)
    {
        acl::json_node *path = $node["path"];
        std::pair<bool, std::string> $result;

        if(!path ||!($result = gson(*path, &$obj.path), $result.first))
            return std::make_pair(false, "required [nameserver_proto::list_services_req.path] failed:{"+$result.second+"}");
     
        return std::make_pair(true,"");
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::list_services_req *$obj)
    {
        return gson($node, *$obj);
    }


    std::pair<bool,std::string> gson(const acl::string &$str, nameserver_proto::list_services_req &$obj)
    {
        acl::json _json;
        _json.update($str.c_str());
        if (!_json.finish())
        {
            return std::make_pair(false, "json not finish error");
        }
        return gson(_json.get_root(), $obj);
    }


    acl::json_node& gson(acl::json &$json, const nameserver_proto::list_services_resp &$obj)
    {
        acl::json_node &$node = $json.create_node();

        if (check_nullptr($obj.status))
            $node.add_null("status");
        else
            $node.add_text("status", acl::get_value($obj.status));

        if (check_nullptr($obj.services))
            $node.add_null("services");
        else
            $node.add_child("services", acl::gson($json, $obj.services));


        return $node;
    }
    
    acl::json_node& gson(acl::json &$json, const nameserver_proto::list_services_resp *$obj)
    {
        return gson ($json, *$obj);
    }


    acl::string gson(const nameserver_proto::list_services_resp &$obj)
    {
        acl::json $json;
        acl::json_node &$node = acl::gson ($json, $obj);
        return $node.to_string ();
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::list_services_resp &$obj)
    {
        acl::json_node *status = $node["status"];
        acl::json_node *services = $node["services"];
        std::pair<bool, std::string> $result;

        if(!status ||!($result = gson(*status, &$obj.status), $result.first))
            return std::make_pair(false, "required [nameserver_proto::list_services_resp.status] failed:{"+$result.second+"}");
     
        if(services&& services->get_obj())
             gson(*services->get_obj(), &$obj.services);
     
        return std::make_pair(true,"");
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::list_services_resp *$obj)
    {
        return gson($node, *$obj);
    }


    std::pair<bool,std::string> gson(const acl::string &$str, nameserver_proto::list_services_resp &$obj)
    {
        acl::json _json;
        _json.update($str.c_str());
        if (!_json.finish())
        {
            return std::make_pair(false, "json not finish error");
        }
        return gson(_json.get_root(), $obj);
    }


    acl::json_node& gson(acl::json &$json, const nameserver_proto::service_info &$obj)
    {
        acl::json_node &$node = $json.create_node();

        if (check_nullptr($obj.service_name))
            $node.add_null("service_name");
        else
            $node.add_text("service_name", acl::get_value($obj.service_name));

        if (check_nullptr($obj.server_addrs))
            $node.add_null("server_addrs");
        else
            $node.add_child("server_addrs", acl::gson($json, $obj.server_addrs));


        return $node;
    }
    
    acl::json_node& gson(acl::json &$json, const nameserver_proto::service_info *$obj)
    {
        return gson ($json, *$obj);
    }


    acl::string gson(const nameserver_proto::service_info &$obj)
    {
        acl::json $json;
        acl::json_node &$node = acl::gson ($json, $obj);
        return $node.to_string ();
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::service_info &$obj)
    {
        acl::json_node *service_name = $node["service_name"];
        acl::json_node *server_addrs = $node["server_addrs"];
        std::pair<bool, std::string> $result;

        if(!service_name ||!($result = gson(*service_name, &$obj.service_name), $result.first))
            return std::make_pair(false, "required [nameserver_proto::service_info.service_name] failed:{"+$result.second+"}");
     
        if(!server_addrs ||!server_addrs->get_obj()||!($result = gson(*server_addrs->get_obj(), &$obj.server_addrs), $result.first))
            return std::make_pair(false, "required [nameserver_proto::service_info.server_addrs] failed:{"+$result.second+"}");
     
        return std::make_pair(true,"");
    }


    std::pair<bool,std::string> gson(acl::json_node &$node, nameserver_proto::service_info *$obj)
    {
        return gson($node, *$obj);
    }


    std::pair<bool,std::string> gson(const acl::string &$str, nameserver_proto::service_info &$obj)
    {
        acl::json _json;
        _json.update($str.c_str());
        if (!_json.finish())
        {
            return std::make_pair(false, "json not finish error");
        }
        return gson(_json.get_root(), $obj);
    }


}///end of acl.
