#ifndef SLUGROUTE_H
#define SLUGROUTE_H
#include <string>
#include <filesystem>
#include <functional>
#include <span>
#include <string_view>
#include "../Request.h"
#include "../Response.h"
#include "IRoute.h"

namespace webwork::routes {
    class SlugRoute : public IRoute {
    public:
        std::string name;
        std::shared_ptr<IRoute> route;
        std::function<Response(const Request &)> requestHandler;
        std::function<void(const Request &)> sideEffect;

        SlugRoute(std::string_view name, const std::shared_ptr<IRoute> &route, const RequestHandlerT &requestHandler, const SideEffectT &sideEffect) : name(name), route(route), requestHandler(requestHandler), sideEffect(sideEffect) {}

        Response HandleRequest(const Request &request) override;
        std::shared_ptr<IRoute> GetNextRoute(std::span<std::string> path) override;
        void InvokeSideEffect(Request &request, std::string_view path) override;
    };
} // webwork::routes

#endif //SLUGROUTE_H
