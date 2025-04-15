#ifndef RESPONSE_H
#define RESPONSE_H
#include <map>
#include <string>
#include <vector>
#include <chrono>
#include "StatusCodes.h"

namespace webwork {
    const std::string HTTPVersion = "HTTP/1.0";
    const std::string Endline = "\r\n";

    enum class SameSite {
        Default = 0,
        Strict = 1,
        Lax = 2,
        None = 3
    };

    struct Cookie {
        std::string value;
        std::string domain;
        std::optional<std::chrono::sys_seconds> expires;
        bool httpOnly = false;
        std::optional<ssize_t> maxAge;
        bool partitioned = false;
        std::string path;
        bool secure = false;
        SameSite sameSite = SameSite::Default;

        std::string ToString() const;
    };

    struct Response {
        StatusCode code;
        std::vector<unsigned char> body;
        std::map<std::string, std::string> headers;
        std::map<std::string, Cookie> cookies;

        std::string ToString() const;
    };
} // webwork

#endif //RESPONSE_H
