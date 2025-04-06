#include "URL.h"

#include "Logging.h"

namespace webwork {
    URL::URL(std::string_view url) {
        this -> url = url;

        size_t previousFound = 1;
        size_t position = 1;
        for (; position < url.size(); position++) {
            if (url[position] == '/') {
                if (url[position - 1] == '/') {
                    previousFound++;
                    continue;
                }
                path.push_back(std::string(url.substr(previousFound, position - previousFound)));
                previousFound = position + 1;
            }
        }

        if (previousFound != url.size() - 1) {
            path.push_back(std::string(url.substr(previousFound, url.size() - 1)));
        }
    }
} // webwork