#include "DirectoryRoute.h"

namespace webwork::routes {
    Response DirectoryRoute::HandleRequest(const Request &request) {
        throw std::logic_error("Not implemented >:3");
    }

    std::shared_ptr<IRoute> DirectoryRoute::GetNextRoute(std::span<std::string> path) {
        return nullptr;
    }

    void DirectoryRoute::InvokeSideEffect(Request &request, std::string_view path) {
        sideEffect(request);
    }
} // webwork::routes