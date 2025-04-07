#ifndef SERVER_H
#define SERVER_H
#include "ServerConfig.h"
#include "../Request.h"

namespace webwork {
    void RunServer(const ServerConfig &config);
    Request ParseRequest(std::string_view requestString);
    void StopServer();
}

#endif //SERVER_H
