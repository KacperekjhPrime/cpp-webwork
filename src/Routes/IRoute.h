#ifndef IROUTE_H
#define IROUTE_H
#include <string>
#include <filesystem>
#include <span>
#include <functional>
#include <string_view>
#include "../Request.h"
#include "../Response.h"

namespace webwork::routes {
    using RequestHandlerT = std::function<Response(const Request &)>;
    using SideEffectT = std::function<void(const Request &)>;

    class IRoute {
    public:
        const bool isFinalRoute;

        IRoute(bool isFinalRoute = false) : isFinalRoute(isFinalRoute) {}

        virtual Response HandleRequest(const Request &request) = 0;
        virtual std::shared_ptr<IRoute> GetNextRoute(std::span<std::string> path) = 0;
        virtual void InvokeSideEffect(Request &request, std::string_view path) {}

        virtual ~IRoute() = default;
    };
} // webwork::routes
#endif //IROUTE_H
