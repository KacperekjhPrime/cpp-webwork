#ifndef RESPONSE_H
#define RESPONSE_H
#include <map>
#include <string>
#include <utility>
#include <vector>
#include "StatusCodes.h"
#include <cstring>

namespace webwork {
    const std::string HTTPVersion = "HTTP/1.0";
    const std::string Endline = "\r\n";

    struct Response {
        StatusCode code;
        std::vector<unsigned char> body;
        std::map<std::string, std::string> headers;

        std::string ToString() const {
            std::string result{};

            result += HTTPVersion + " " + std::to_string(std::to_underlying(code)) + " " + statusCodes.at(code) + Endline;
            result += "Content-Length: " + std::to_string(body.size()) + Endline;

            for (const auto &[key, value] : headers) {
                result += key + ": " + value + Endline;
            }

            result += Endline;

            const size_t contentSize = result.size();
            result.resize(result.size() + body.size());
            std::memcpy(result.data() + contentSize, body.data(), body.size());

            return result;
        }
    };
} // webwork

#endif //RESPONSE_H
