#ifndef ROUTE_H
#define ROUTE_H
#include <functional>
#include "Request.h"
#include <vector>

namespace webwork {
    struct Route {
        std::function<void(const Request &)> RequestHandler;
        std::function<Route(std::vector<std::string>)> GetRoutes;
    };
} // webwork

#endif //ROUTE_H
