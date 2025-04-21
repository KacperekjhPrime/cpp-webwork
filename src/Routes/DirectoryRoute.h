#ifndef DIRECTORYROUTE_H
#define DIRECTORYROUTE_H
#include <string>
#include <filesystem>
#include <functional>
#include <span>
#include <string_view>
#include "../Request.h"
#include "../Response.h"
#include "IRoute.h"

namespace webwork::routes {
    class DirectoryRoute : public IRoute {
    public:
        std::function<void(const Request &)> sideEffect;

        DirectoryRoute(const SideEffectT &sideEffect) : IRoute(true), sideEffect(sideEffect) {}

        Response HandleRequest(const Request &request) override;
        std::shared_ptr<IRoute> GetNextRoute(std::span<std::string> path) override;
        void InvokeSideEffect(Request &request, std::string_view path) override;
    };
} // webwork::routes

#endif //DIRECTORYROUTE_H
