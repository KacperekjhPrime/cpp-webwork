#ifndef HELPER_H
#define HELPER_H
#include <string_view>
#include <vector>
#include <map>

namespace webwork {
    std::vector<std::string> SplitString(const std::string_view input, const char delimiter);
    std::vector<std::string> SplitString(const std::string_view input, const std::string delimiter);
    std::multimap<std::string, std::string> ParseParameters(std::string_view parametersString);
    std::string VectorToPath(std::vector<std::string> input);
}

#endif //HELPER_H
