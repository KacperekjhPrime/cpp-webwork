#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H
#include <string>

struct ServerConfig {
    int port = 8080;
    int ioThreads = 1;
    std::string serverName = "The machine that turns your tears into c++ code";
};

#endif //SERVERCONFIG_H
