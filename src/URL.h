#ifndef URL_H
#define URL_H
#include <string>
#include <vector>
#include <map>
#include <iostream>

namespace webwork {
    class URL {
    public:
        std::string url;
        std::vector<std::string> path;
        std::map<std::string, std::string> searchParameters;

        URL(std::string_view url);
    };
} // webwork

#endif //URL_H
