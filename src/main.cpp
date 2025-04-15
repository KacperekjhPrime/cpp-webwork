#include <iostream>
#include "Logging.h"
#include "Loading/Loader.h"
#include "Server/Server.h"

int main() {
    webwork::LoadModules();

    const ServerConfig config{};
    webwork::RunServer(config);
    return 0;
}
