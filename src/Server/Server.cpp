#include "Server.h"
#include <asio.hpp>
#include <map>
#include <fstream>
#include <string_view>
#include <filesystem>
#include "../Logging.h"
#include "../Response.h"
#include "../Mime.h"
#include "../Helper.h"

using asio::ip::tcp;

namespace webwork {
    bool isServerRunning = true;

    void RunServer(const ServerConfig &config) {
        asio::io_context io_context{config.ioThreads};
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), config.port));

        while (isServerRunning) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            std::string rawRequestContent(2048, '\0');
            size_t bytesRead = socket.read_some(asio::buffer(rawRequestContent));
            rawRequestContent.resize(bytesRead);
            Request request = ParseRequest(rawRequestContent);

            std::filesystem::path filePath = "index.html";
            auto mimeType = GetFileMime(filePath);
            std::ifstream file{"index.html", std::ios::binary};
            std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(file), {});
            Response response{StatusCode::OK, buffer};
            response.headers["Server"] = "The machine that turns your tears into c++ code";
            response.headers["Content-Type"] = mimeType;

            std::error_code error;
            asio::write(socket, asio::buffer(response.ToString()), error);
        }
    }

    Request ParseRequest(std::string_view requestString) {
        Request request{};

        size_t requestHeaderLength = requestString.find("\r\n\r\n");
        if (requestHeaderLength == std::string_view::npos) throw std::invalid_argument("Invalid request");

        size_t requestStartLineLength = requestString.find("\r\n");
        if (requestStartLineLength == std::string_view::npos) throw std::invalid_argument("Invalid request");

        auto splitRequestStartLine = SplitString(requestString.substr(0, requestStartLineLength - 1), ' ');

        if (splitRequestStartLine.size() != 3) throw std::invalid_argument("Invalid request");
        std::string requestMethod = splitRequestStartLine[0];

        auto requestMethodIterator = RequestMethods.find(requestMethod);
        if (requestMethodIterator == RequestMethods.end()) {
            request.method = RequestMethods.at(requestMethod);
        }

        request.url = URL(splitRequestStartLine[1]);

        auto splitHeaders = SplitString(requestString.substr(requestStartLineLength + 2, requestHeaderLength - 1), "\r\n");
        for (auto header : splitHeaders) {
            auto splitHeader = SplitString(header, ": ");
            request.headers[splitHeader[0]] = splitHeader[1];
        }

        return request;
    }

    void StopServer() {
        isServerRunning = false;
    }
}
