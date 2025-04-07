#include <cstring>
#include <utility>
#include <string>
#include "Response.h"

namespace webwork {
    std::string Response::ToString() const {
        std::string result{};

        result += HTTPVersion + " " + std::to_string(std::to_underlying(code)) + " " + statusCodes.at(code) + Endline;
        result += "Content-Length: " + std::to_string(body.size()) + Endline;

        for (const auto &[key, value] : headers) {
            result += key;
            result += ": ";
            result += value;
            result += Endline;
        }

        result += Endline;

        const size_t contentSize = result.size();
        result.resize(result.size() + body.size());
        std::memcpy(result.data() + contentSize, body.data(), body.size());

        return result;
    }
}