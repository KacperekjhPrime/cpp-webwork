#include "URL.h"
#include "Helper.h"
#include "Logging.h"

namespace webwork {
    URL::URL(std::string_view url) {
        this -> url = url;

        size_t parametersIndex = url.find('?');
        if (parametersIndex != std::string_view::npos) {
            searchParameters = ParseParameters(url.substr(parametersIndex + 1, url.size() - 1));
        }
        path = SplitString(url.substr(1, (parametersIndex != std::string::npos ? url.size() - (url.size() - parametersIndex) - 1 : url.size() - 1)), '/');

        Log(LogLevel::Info, "Splitting URL: {}", url);
        for (auto a : path) {
            Log(LogLevel::Info, a);
        }
        Log(LogLevel::Info, "Parameters: ");
        for (auto a : searchParameters) {
            Log(LogLevel::Info, "{}={}", a.first, a.second);
        }
    }
} // webwork