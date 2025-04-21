#include "Path.h"
#include "Helper.h"
#include "Logging.h"

namespace webwork {
    Path::Path() {}

    Path::Path(std::string_view url) {
        this -> pathString = url;

        size_t parametersIndex = url.find('?');
        if (parametersIndex != std::string_view::npos) {
            searchParameters = ParseParameters(url.substr(parametersIndex + 1, url.size() - parametersIndex + 1));
        }
        path = SplitString(url.substr(1, (parametersIndex != std::string::npos ? url.size() - (url.size() - parametersIndex) - 1 : url.size() - 1)), '/');
    }
} // webwork