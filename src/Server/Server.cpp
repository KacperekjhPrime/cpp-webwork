#include "Server.h"
#include <zmq.hpp>
#include <format>
#include <map>

namespace webwork {
    bool isServerRunning = true;

    void RunServer(const ServerConfig &config) {
        zmq::context_t context{config.ioThreads};

        zmq::socket_t socket{context, zmq::socket_type::rep};

        socket.bind(std::format("tcp://*:{}", config.port));

        while (isServerRunning) {
            zmq::message_t request;

            socket.recv(request, zmq::recv_flags::none);
            ParseRequest(request.to_string());
        }
    }

    Request ParseRequest(std::string requestString) {
        return Request{RequestType::GET, "/", std::nullopt, std::map<std::string, std::string>{}};
    }

    void StopServer() {
        isServerRunning = false;
    }

}
