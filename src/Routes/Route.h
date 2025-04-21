#ifndef ROUTE_H
#define ROUTE_H
#include <string>
#include <filesystem>
#include <functional>
#include <span>
#include <string_view>
#include "../Request.h"
#include "../Response.h"
#include "IRoute.h"

namespace webwork::routes {
    class Route : public IRoute {
    public:
        std::map<std::string, std::shared_ptr<IRoute>> routes;
        std::function<Response(const Request &)> requestHandler;
        std::function<void(const Request &)> sideEffect;

        Route(const std::map<std::string, std::shared_ptr<IRoute>> &routes, const RequestHandlerT &requestHandler, const SideEffectT &sideEffect) : routes(routes), requestHandler(requestHandler), sideEffect(sideEffect) {}

        Response HandleRequest(const Request &request) override;
        std::shared_ptr<IRoute> GetNextRoute(std::span<std::string> path) override;
        void InvokeSideEffect(Request &request, std::string_view path) override;
    };
} // webwork::routes

#endif //ROUTE_H
