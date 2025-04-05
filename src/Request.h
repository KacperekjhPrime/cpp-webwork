#ifndef REQUEST_H
#define REQUEST_H
#include <map>
#include <optional>
#include <string>

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
        PATCH,
    };

    struct Request {
        RequestType method;
        std::string url;
        std::optional<std::string> body;
        std::map<std::string, std::string> headers;
    };
} // webwork

#endif //REQUEST_H
