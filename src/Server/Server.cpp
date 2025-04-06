#include "Server.h"
#include <asio.hpp>
#include <map>
#include <fstream>
#include "../Logging.h"
#include "../Response.h"

using asio::ip::tcp;

namespace webwork {
    bool isServerRunning = true;

    void RunServer(const ServerConfig &config) {
        asio::io_context io_context{config.ioThreads};
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), config.port));

        while (isServerRunning) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            std::string rawRequestContent;
            socket.read_some(asio::buffer(rawRequestContent));
            Request request = ParseRequest(rawRequestContent);

            std::ifstream file{"index.html", std::ios::binary};
            std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(file), {});
            Response response{StatusCode::OK, buffer};
            response.headers["Server"] = "The machine that turns your tears into c++ code";
            response.headers["Content-Type"] = "text/html";

            std::error_code error;
            asio::write(socket, asio::buffer(response.ToString()), error);
        }
    }

    Request ParseRequest(std::string requestString) {
        return Request{RequestType::GET, URL("/hello/world/aaaa/index.html"), std::nullopt, std::map<std::string, std::string>{}};
    }

    void StopServer() {
        isServerRunning = false;
    }

}
