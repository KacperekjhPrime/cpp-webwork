#ifndef SERVER_H
#define SERVER_H
#include "ServerConfig.h"
#include "../Request.h"
#include "../Response.h"

namespace webwork {
    void RunServer(const ServerConfig &config);
    Response CreateResponse(const Request &request);
    Request ParseRequest(std::string_view requestString);
    std::map<std::string, std::string> ParseCookies(std::string_view cookieString);
    void StopServer();
}

#endif //SERVER_H
