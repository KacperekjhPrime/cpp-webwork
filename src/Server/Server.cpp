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

            Response response;
            try {
                acceptor.accept(socket);

                //TODO: Resize buffer to request size
                std::string rawRequestContent(2048, '\0');
                size_t bytesRead = socket.read_some(asio::buffer(rawRequestContent));

                rawRequestContent.resize(bytesRead);
                Request request = ParseRequest(rawRequestContent);
                response = CreateResponse(request);
            }
            catch (HTTPException &e) {
                response.code = e.statusCode;
                Log(LogLevel::Error, "Error");
            }
            catch (std::exception &e) {
                response.code = StatusCode::InternalServerError;
                Log(LogLevel::Error, e.what());
            }
            response.headers["Server"] = config.serverName;

            std::error_code error;
            asio::write(socket, asio::buffer(response.ToString()), error);
        }
    }

    Response CreateResponse(const Request &request) {
        Response response{StatusCode::OK};

        std::filesystem::path filePath = VectorToPath(request.url.path);
        std::ifstream file{filePath, std::ios::binary};
        if (!file.is_open()) throw HTTPException(StatusCode::NotFound);

        std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(file), {});
        file.close();

        response.body = buffer;

        std::string mimeType;
        if (filePath.extension() == ".css") mimeType = "text/css";
        else if (filePath.extension() == ".js") mimeType = "application/javascript";
        else mimeType = GetFileMime(filePath);

        response.headers["Content-Type"] = mimeType;

        return response;
    }

    Request ParseRequest(std::string_view requestString) {
        Request request{};

        size_t requestHeaderLength = requestString.find("\r\n\r\n");
        if (requestHeaderLength == std::string_view::npos) throw HTTPException(StatusCode::BadRequest);

        size_t requestStartLineLength = requestString.find("\r\n");
        if (requestStartLineLength == std::string_view::npos) throw HTTPException(StatusCode::BadRequest);

        auto splitRequestStartLine = SplitString(requestString.substr(0, requestStartLineLength), ' ');

        if (splitRequestStartLine.size() != 3) throw HTTPException(StatusCode::BadRequest);
        std::string requestMethod = splitRequestStartLine[0];

        auto requestMethodIterator = RequestMethods.find(requestMethod);
        if (requestMethodIterator == RequestMethods.end()) throw HTTPException(StatusCode::BadRequest);
        request.method = RequestMethods.at(requestMethod);

        request.url = URL(splitRequestStartLine[1]);

        auto splitHeaders = SplitString(requestString.substr(requestStartLineLength + 2, requestHeaderLength - requestStartLineLength - 2), "\r\n");
        for (const auto &header : splitHeaders) {
            auto splitHeader = SplitString(header, ": ");
            if (splitHeader.size() != 2) throw HTTPException(StatusCode::BadRequest);
            request.headers[splitHeader[0]] = splitHeader[1];
        }

        auto cookieHeaderIndex = request.headers.find("Cookie");
        if (cookieHeaderIndex != request.headers.end()) {
            request.cookies = ParseCookies(cookieHeaderIndex->second);
        }

        return request;
    }

    std::map<std::string, std::string> ParseCookies(std::string_view cookieString) {
        std::map<std::string, std::string> output;

        auto splitCookies = SplitString(cookieString, ";");
        for (const auto &cookie : splitCookies) {
            auto splitCookie = SplitString(cookie, "=");
            if (splitCookie.size() != 2) continue;
            output[splitCookie[0]] = splitCookie[1];
        }

        return output;
    }

    void StopServer() {
        isServerRunning = false;
    }
}
