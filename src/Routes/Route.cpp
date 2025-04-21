#include "Route.h"

namespace webwork::routes {
    Response Route::HandleRequest(const Request &request) {
        return requestHandler(request);
    }

    std::shared_ptr<IRoute> Route::GetNextRoute(std::span<std::string> path) {
        auto nextElement = routes.find(path.front());
        if (nextElement == routes.end()) return nullptr;
        return nextElement->second;
    }

    void Route::InvokeSideEffect(Request &request, std::string_view path) {
        sideEffect(request);
    }
} // webwork::routes