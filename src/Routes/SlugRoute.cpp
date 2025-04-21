#include "SlugRoute.h"

namespace webwork::routes {
    Response SlugRoute::HandleRequest(const Request &request) {
        return requestHandler(request);
    }

    std::shared_ptr<IRoute> SlugRoute::GetNextRoute(std::span<std::string> path) {
        if (route == nullptr) return nullptr;
        return route->GetNextRoute(path.subspan(1));
    }

    void SlugRoute::InvokeSideEffect(Request &request, std::string_view path) {
        request.slugs.emplace(name, path);
        sideEffect(request);
    }
} // webwork::routes