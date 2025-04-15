#ifndef REQUEST_H
#define REQUEST_H
#include <map>
#include <optional>
#include <string>
#include "URL.h"

namespace webwork {
    enum class RequestType {
        GET,
        HEAD,
        POST,
        PUT,
        DELETE,
        CONNECT,
        OPTIONS,
        TRACE,
        PATCH
    };

    const std::map<std::string, RequestType> RequestMethods{
        {"GET", RequestType::GET},
        {"HEAD", RequestType::HEAD},
        {"POST", RequestType::POST},
        {"PUT", RequestType::PUT},
        {"DELETE", RequestType::DELETE},
        {"CONNECT", RequestType::CONNECT},
        {"OPTIONS", RequestType::OPTIONS},
        {"TRACE", RequestType::TRACE},
        {"PATCH", RequestType::PATCH}
    };

    struct Request {
        RequestType method;
        URL url;
        std::optional<std::string> body;
        std::map<std::string, std::string> headers;
    };
} // webwork

#endif //REQUEST_H
