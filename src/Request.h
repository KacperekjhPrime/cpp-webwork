//
// Created by Kacper on 4/5/25.
//

#ifndef REQUEST_H
#define REQUEST_H
#include <map>
#include <optional>
#include <string>

namespace webwork {

struct Request {
    std::string method;
    std::string url;
    std::optional<std::string> body;
    std::map<std::string, std::string> headers;
};

} // webwork

#endif //REQUEST_H
