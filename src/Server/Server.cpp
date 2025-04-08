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
#include "../HTTPException.h"

using asio::ip::tcp;

namespace webwork {
    bool isServerRunning = true;

    void RunServer(const ServerConfig &config) {
        asio::io_context io_context{config.ioThreads};
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), config.port));

        while (isServerRunning) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            //TODO: Resize buffer to request size
            std::string rawRequestContent(2048, '\0');
            size_t bytesRead = socket.read_some(asio::buffer(rawRequestContent));
            rawRequestContent.resize(bytesRead);

            Request request = ParseRequest(rawRequestContent);

            std::filesystem::path filePath = VectorToPath(request.url.path);
            std::ifstream file{filePath, std::ios::binary};
            if (!file.is_open()) throw HTTPException(StatusCode::NotFound);

            std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(file), {});
            file.close();

            auto mimeType = GetFileMime(filePath);

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

        auto splitRequestStartLine = SplitString(requestString.substr(0, requestStartLineLength), ' ');

        if (splitRequestStartLine.size() != 3) throw std::invalid_argument("Invalid request");
        std::string requestMethod = splitRequestStartLine[0];

        auto requestMethodIterator = RequestMethods.find(requestMethod);
        if (requestMethodIterator == RequestMethods.end()) throw std::invalid_argument("Invalid request");
        request.method = RequestMethods.at(requestMethod);

        request.url = URL(splitRequestStartLine[1]);

        auto splitHeaders = SplitString(requestString.substr(requestStartLineLength + 2, requestHeaderLength - requestStartLineLength - 2), "\r\n");
        for (auto header : splitHeaders) {
            auto splitHeader = SplitString(header, ": ");
            if (splitHeader.size() != 2) throw new std::invalid_argument("Invalid request");
            request.headers[splitHeader[0]] = splitHeader[1];
        }

        return request;
    }

    void StopServer() {
        isServerRunning = false;
    }
}
