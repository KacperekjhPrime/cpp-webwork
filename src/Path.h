#ifndef PATH_H
#define PATH_H
#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <iostream>

namespace webwork {
    class Path {
    public:
        std::string pathString;
        std::vector<std::string> path;
        std::multimap<std::string, std::string> searchParameters;

        Path();
        Path(std::string_view url);
    };
} // webwork

#endif //PATH_H
