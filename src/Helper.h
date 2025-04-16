#ifndef HELPER_H
#define HELPER_H
#include <string_view>
#include <vector>
#include <map>
#include <span>

namespace webwork {
    std::vector<std::string> SplitString(std::string_view input, char delimiter);
    std::vector<std::string> SplitString(std::string_view input, std::string delimiter);
    std::multimap<std::string, std::string> ParseParameters(std::string_view parametersString);
    std::string VectorToPath(std::span<std::string> input);
    std::string_view TrimSpacesFront(std::string_view input);
    std::string_view TrimSpacesBack(std::string_view input);
    std::string_view TrimSpaces(std::string_view input);
    bool IsValidHexCharacter(char input);
    char HexToChar(std::string_view input);
    std::string PercentDecode(std::string_view input);
    void PlusToSpace(std::string& input);
    std::string Join(std::span<std::string> input, std::string_view delimiter);
}

#endif //HELPER_H
