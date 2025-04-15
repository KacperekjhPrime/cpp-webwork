#include <cstring>
#include <utility>
#include "Response.h"

namespace webwork {
    std::string Cookie::ToString() const {
        std::vector<std::string> attributes;

        if (domain != "") attributes.push_back("Domain=" + domain);
        if (expires.has_value()) {
            const std::chrono::zoned_time expiresGMT{"Etc/GMT", expires.value()};
            const int seconds = std::stoi(std::format("{0:%S}", expires.value()));
            attributes.push_back(std::format("Expires={0:%a}, {0:%d} {0:%m} {0:%Y} {0:%H}:{0:%M}:{1} GMT", expiresGMT, seconds));
        }
        if (httpOnly) attributes.push_back("HttpOnly");
        if (maxAge.has_value()) attributes.push_back("Max-Age=" + maxAge.value());
        if (partitioned) attributes.push_back("Partitioned");
        if (path != "") attributes.push_back("Path=" + path);
        if (secure) attributes.push_back("Secure");
        if (sameSite != SameSite::Default) {
            switch (sameSite) {
                case SameSite::Strict:
                    attributes.push_back("Strict");
                    break;
                case SameSite::Lax:
                    attributes.push_back("Lax");
                    break;
                case SameSite::None:
                    attributes.push_back("None");
                    break;
            }
        }
    }

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