
#define ASIO_STANDALONE

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <functional>
#include <list>

#include "nlohmann/json.hpp"

#include <mutex>



namespace scuweb
{

using server = websocketpp::server<websocketpp::config::asio>;


/// @brief HttpServer class
class HttpServer {

protected:
    server m_server;
    uint16_t m_listen_port;
    bool m_debug_info;

public:
    /// @brief constructor
    HttpServer(uint16_t listen_port=8080, bool debug_info=true): m_listen_port(listen_port), m_debug_info(debug_info) {
        if (m_debug_info) {
		    std::cout << "HttpServer construct" << std::endl;
        }
    }

    /// @brief desconstructor
    virtual ~HttpServer() noexcept{
        if (m_debug_info) {
		    std::cout << "HttpServer destruct" << std::endl;
        }
    }

protected:
    // websocket connections established by browser
    std::vector<websocketpp::connection_hdl> m_websocket_connections;
    std::mutex m_websocket_connections_mtx;

    /// @brief Default callback method for when the client intends to establish a websocket 
	/// @param hdl - the connection
    virtual void websocketOpenHandler(websocketpp::connection_hdl hdl) {
        std::lock_guard<std::mutex> lock(m_websocket_connections_mtx);
        m_websocket_connections.push_back(hdl);
        if(m_debug_info){
            std::cout<<"websocketOpenHandler called, m_websocket_connections.size:"<< m_websocket_connections.size()<<std::endl;
        }
    }

    /// @brief Default callback method for when the client intends to close a websocket 
	/// @param hdl - the connection
    virtual void websocketCloseHandler(websocketpp::connection_hdl hdl) {
        std::lock_guard<std::mutex> lock(m_websocket_connections_mtx);
        m_websocket_connections.erase(
            std::remove_if(
                std::begin(m_websocket_connections), std::end(m_websocket_connections), [&](const websocketpp::connection_hdl& a) {
                    if (a.lock() == hdl.lock())return true;
                    return false;
                }
            )
        );
        if(m_debug_info){
            std::cout<<"websocketCloseHandler, m_websocket_connections.size:"<< m_websocket_connections.size()<<std::endl;
        }
    }

    /// @brief Default callback method for when the client send a websocket message, just echo back what it get
	/// @param hdl - the connection
    /// @param msg - the websocket message
    virtual void websocketEchoHandler(websocketpp::connection_hdl hdl, server::message_ptr msg) {
        m_server.send(hdl, msg->get_payload(), msg->get_opcode());
        if(m_debug_info){
            std::cout<<"websocketEchoHandler, echo back message:"<< msg->get_payload()<<std::endl;
        }
    }


    // message in websocket send queue will sent to browser
    std::list<std::pair<std::shared_ptr<std::vector<unsigned char>>, websocketpp::frame::opcode::value>> m_websocket_send_queue;
    const uint kMaxQueueSize = 12;
    std::mutex m_websocket_send_queue_mtx;
    std::condition_variable m_websocket_send_queue_cv;

public:

    /// @brief enqueue message to the websocket send queue 
    /// @param payload - raw websocket message, wrapped with std::shared_ptr
    /// @param payload_type - websocket message type, usually websocketpp::frame::opcode::value::binary or websocketpp::frame::opcode::value::text
    virtual void enqueue(std::shared_ptr<std::vector<unsigned char>> payload, websocketpp::frame::opcode::value payload_type){
        if(payload==nullptr){
            if(m_debug_info)std::cout<<"enqueue called, payload is nullptr"<<std::endl;
            return;
        }
        {
            std::lock_guard<std::mutex> lock(m_websocket_send_queue_mtx);
            if(m_websocket_send_queue.size()>kMaxQueueSize){
                m_websocket_send_queue.pop_front();
                if(m_debug_info)std::cout<<"m_websocket_send_queue.size()>kMaxQueueSize:"<<kMaxQueueSize<<std::endl;
            }
            m_websocket_send_queue.push_back(std::make_pair(payload, payload_type));
            m_websocket_send_queue_cv.notify_one();
        }
    }

    /// @brief method for sending message in the websocket send queue to the browser
    virtual void dequeueThread(void){
        while (true){
            std::unique_lock<std::mutex> lock(m_websocket_send_queue_mtx);
            m_websocket_send_queue_cv.wait(lock, [this] {return !m_websocket_send_queue.empty() && !m_websocket_connections.empty();});
            std::pair<std::shared_ptr<std::vector<unsigned char>>, websocketpp::frame::opcode::value> obj_pair = m_websocket_send_queue.front();
            m_websocket_send_queue.pop_front();
            lock.unlock();
            std::lock_guard<std::mutex> lock2(m_websocket_connections_mtx);
            for (auto websocket_connection : m_websocket_connections)
            {
                m_server.send(websocket_connection, obj_pair.first->data(), obj_pair.first->size(), obj_pair.second);
            }
        }
    }



protected:

    /// @brief Default http handler for all http request, you can override this method in derived class
	/// @param hdl - the connection
    virtual void httpHandler(websocketpp::connection_hdl hdl) {
        server::connection_ptr con = m_server.get_con_from_hdl(hdl);
        std::string resource = con->get_resource();
        
        if(resource == "/"){
            httpHandlerCallbackDefault(con);
        }else{
            httpHandlerCallback404(con);
        }
    }

    /// @brief Default http callback method, you can override this method in derived class
	/// @param hdl - the connection pointer
    virtual void httpHandlerCallbackDefault(server::connection_ptr con) {
        con->set_body("<html><h1>This is the default http response</h1></html>");
        con->set_status(websocketpp::http::status_code::ok);
    }

    /// @brief Default http 404 callback method, you can override this method in derived class
	/// @param hdl - the connection pointer
    virtual void httpHandlerCallback404(server::connection_ptr con) {
        nlohmann::json j;
        j["err_code"] = 1;
        j["err_msg"] = "404 request resource not found";
        j["data"] = nullptr;
        
        std::string s = j.dump(4);
        con->set_body(s.c_str());
        con->set_status(websocketpp::http::status_code::not_found);
    }


protected:
    /// @brief Thread for running http server
    virtual void runThread() {
        // Set logging settings
        m_server.set_error_channels(websocketpp::log::elevel::all);
        m_server.set_access_channels(websocketpp::log::alevel::none);

        // Initialize Asio
        m_server.init_asio();
        m_server.set_reuse_addr(true);

        m_server.set_open_handler(std::bind(
            &HttpServer::websocketOpenHandler, this,
            std::placeholders::_1
        ));
        // Set the default message handler to the echo handler
        m_server.set_message_handler(std::bind(
            &HttpServer::websocketEchoHandler, this,
            std::placeholders::_1, std::placeholders::_2
        ));
        m_server.set_close_handler(std::bind(
            &HttpServer::websocketCloseHandler, this,
            std::placeholders::_1
        ));


        m_server.set_http_handler(
            std::bind(&HttpServer::httpHandler, this,  std::placeholders::_1)
        );
        // Listen on port 8080
        m_server.listen(m_listen_port);

        // Queues a connection accept operation
        m_server.start_accept();

        // Start the Asio io_service run loop
        m_server.run();
    }

public:
    /// @brief start http server
    virtual void start(){
        static std::thread run_thread(&HttpServer::runThread, this);
        run_thread.detach();
        
        static std::thread dequeue_thread(&HttpServer::dequeueThread, this);
        dequeue_thread.detach();

        if(m_debug_info)std::cout<<"HttpServer start done"<<std::endl;
    }
};

}
