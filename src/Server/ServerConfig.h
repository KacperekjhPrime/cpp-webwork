#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H
#include <string>

struct ServerConfig {
    std::string port = "8080";
    int ioThreads = 1;
};

#endif //SERVERCONFIG_H
