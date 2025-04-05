//
// Created by Kacper on 4/5/25.
//

#ifndef ROUTE_H
#define ROUTE_H
#include <memory>

#include "Response.h"

namespace webwork {

class Route {
public:
    virtual Response GetContent() = 0;
    virtual std::shared_ptr<Route> GetRoute(std::string_view name) = 0;

    virtual ~Route() = default;
};

} // webwork

#endif //ROUTE_H
