#ifndef ROUTE_H
#define ROUTE_H
#include <functional>
#include <memory>
#include "Request.h"
#include <vector>

namespace webwork {
    struct Route {
        std::function<void(const Request &)> RequestHandler;
        std::function<std::shared_ptr<Route>(std::vector<std::string>)> GetRoutes;
    };
} // webwork

#endif //ROUTE_H
