
#include "http_server.hpp"
#include "html.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace scuweb;

class HttpServerDemo: public HttpServer{
protected:
    // override httpHandler in base class
    void httpHandler(websocketpp::connection_hdl hdl) override {
        server::connection_ptr con = m_server.get_con_from_hdl(hdl);
        std::string resource = con->get_resource();
        
        if(resource.compare(0, resource.size(), "/") == 0){
            httpHandlerCallbackHtml(con,indexHtml);
        }else if(resource.compare(0, resource.size(), "/net.html") == 0){
            httpHandlerCallbackHtml(con,netHtml);
        }else if(resource.compare(0, resource.size(), "/connect.html") == 0){
            httpHandlerCallbackHtml(con,connectHtml);
        }else if(resource.compare(0, resource.size(), "/channel1.html") == 0){
            httpHandlerCallbackHtml(con,channel1Html);
        }else if(resource.compare(0, resource.size(), "/channel2.html") == 0){
            httpHandlerCallbackHtml(con,channel2Html);
        }else if(resource.compare(0, resource.size(), "/channel3.html") == 0){
            httpHandlerCallbackHtml(con,channel3Html);
        }else if(resource.compare(0, resource.size(), "/channel4.html") == 0){
            httpHandlerCallbackHtml(con,channel4Html);
        }else if(resource.compare(0, resource.size(), "/channel5.html") == 0){
            httpHandlerCallbackHtml(con,channel5Html);
        }else if(resource.compare(0, resource.size(), "/net") == 0){
            httpHandlerCallbackApiConfig(con,"net.config");
        }else if(resource.compare(0, resource.size(), "/connect") == 0){
            httpHandlerCallbackApiConfig(con,"connect.config");
        }else if(resource.compare(0, resource.size(), "/channel1") == 0){
            httpHandlerCallbackApiConfig(con,"channel1.config");
        }else if(resource.compare(0, resource.size(), "/channel2") == 0){
            httpHandlerCallbackApiConfig(con,"channel2.config");
        }else if(resource.compare(0, resource.size(), "/channel3") == 0){
            httpHandlerCallbackApiConfig(con,"channel3.config");
        }else if(resource.compare(0, resource.size(), "/channel4") == 0){
            httpHandlerCallbackApiConfig(con,"channel4.config");
        }else if(resource.compare(0, resource.size(), "/channel5") == 0){
            httpHandlerCallbackApiConfig(con,"channel5.config");
        }else if(resource.compare(0, resource.size(), "/login") == 0){
            httpHandlerCallbackApiLogin(con);
        }else{
            httpHandlerCallback404(con);
        }
    }
    
    void httpHandlerCallbackHtml(server::connection_ptr con, const char * html){
        con->set_body(html);
        con->set_status(websocketpp::http::status_code::ok);
    }

    std::string m_config;
    std::mutex m_start_ws_mtx;
public:
    std::string getConfig(){
        std::lock_guard<std::mutex> mtx(m_start_ws_mtx);
        return m_config;
    }
    void setConfig(std::string config){
        std::lock_guard<std::mutex> mtx(m_start_ws_mtx);
        m_config = config;
    }

protected:
    // callback method for api: '/login', return example json data
    void httpHandlerCallbackApiLogin(server::connection_ptr con) {
        //std::cout << "接受到登录请求" << std::endl;
	    std::string body = con->get_request_body();
        //std::cout << body << std::endl;
	    auto r = nlohmann::json::parse(body);
        nlohmann::json j;
	    if(r["username"] == "admin" && r["password"] == "admin"){
		    std::cout<<"user message correct"<<std::endl;
		    j["code"] = 0;
		    j["msg"] = "ok";
	    }else{
		    std::cout<<"user message incorrect"<<std::endl;
		    j["code"] = 0;
		    j["msg"] = "no";
	    }   
        std::string s = j.dump(4);
        con->set_body(s.c_str());
        con->set_status(websocketpp::http::status_code::ok);
    }

    void httpHandlerCallbackApiConfig(server::connection_ptr con, std::string configName) {
        setConfig(configName);
        std::string body = con->get_request_body();
        nlohmann::json r = nlohmann::json::parse(body);
        std::ofstream ofile;
        std::string rootDir = "./config/";
        std::string config = getConfig();
        ofile.open(rootDir + config,std::ios::out);
        if(!ofile)
        {
            std::cerr<<"Open File Fail."<<std::endl;
            return;
        }
        for (nlohmann::json::iterator it = r.begin(); it != r.end(); ++it) {
            std::cout << it.key() << ":" << it.value() << "\n" << std::endl;
            ofile << it.key() << "=" << it.value() << "\n";
        }
        ofile.close();
        std::cout << getConfig() << "has done!" << std::endl;
        nlohmann::json j;
        j["code"] = 1;
        j["msg"] = "ok";
        std::string s = j.dump(4);
        con->set_body(s.c_str());
        con->set_status(websocketpp::http::status_code::ok);
    }
};

int main() {
    std::shared_ptr<HttpServerDemo> server_ptr = std::make_shared<HttpServerDemo>();
    server_ptr->start();
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}

