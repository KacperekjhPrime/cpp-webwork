#ifndef RESPONSE_H
#define RESPONSE_H
#include <map>
#include <string>

namespace webwork {

struct Response {
    int code;
    std::string body;
    std::map<std::string, std::string> headers;
};

} // webwork

#endif //RESPONSE_H
