#ifndef RESPONSE_H
#define RESPONSE_H
#include <map>
#include <string>
#include <vector>
#include "StatusCodes.h"

namespace webwork {
    const std::string HTTPVersion = "HTTP/1.0";
    const std::string Endline = "\r\n";

    struct Response {
        StatusCode code;
        std::vector<unsigned char> body;
        std::map<std::string, std::string> headers;

        std::string ToString() const;
    };
} // webwork

#endif //RESPONSE_H
