#ifndef URL_H
#define URL_H
#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <iostream>

namespace webwork {
    class URL {
    public:
        std::string url;
        std::vector<std::string> path;
        std::multimap<std::string, std::string> searchParameters;

        URL();
        URL(std::string_view url);
    };
} // webwork

#endif //URL_H
