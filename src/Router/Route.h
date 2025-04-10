#ifndef BASICROUTE_H
#define BASICROUTE_H
#include <string>
#include <filesystem>
#include <functional>
#include "../Request.h"
#include "../Response.h"

namespace webwork::routes {
    struct Route {
        std::map<std::string, Route> subroutes;
        std::function<Response(const Request &)> RequestHandler;
    };
} // webwork::routes

#endif //BASICROUTE_H