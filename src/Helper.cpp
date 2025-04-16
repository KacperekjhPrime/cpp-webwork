#include "Helper.h"

#include <cassert>
#include <cstring>
#include <string>
#include <map>

namespace webwork {
    std::vector<std::string> SplitString(std::string_view input, char delimiter) {
        std::vector<std::string> output;

        size_t i = 0;
        size_t previousFound = 0;
        while (i < input.length()) {
            if (input[i] == delimiter) {
                output.push_back(std::string(input.substr(previousFound, i - previousFound)));
                previousFound = i + 1;
            }

            i++;
        }

        output.push_back(std::string(input).substr(previousFound, input.size()));

        return output;
    }

    std::vector<std::string> SplitString(std::string_view input, std::string delimiter) {
        std::vector<std::string> output;

        size_t i = 0;
        size_t previousFound = 0;
        while (i < input.length() - delimiter.size() + 1) {
            if (input.substr(i, delimiter.size()) == delimiter) {
                output.push_back(std::string(input.substr(previousFound, i - previousFound)));
                previousFound = i + delimiter.size();
            }

            i++;
        }

        output.push_back(std::string(input).substr(previousFound, input.size()));

        return output;
    }

    std::multimap<std::string, std::string> ParseParameters(std::string_view parametersString) {
        std::multimap<std::string, std::string> output;

        auto parameterStrings = SplitString(parametersString, '&');

        for (auto parameterString : parameterStrings) {
            std::pair<std::string, std::string> parameter;

            size_t splitIndex = parameterString.find('=');
            if (splitIndex == std::string::npos) continue;
            parameter.first = parameterString.substr(0, splitIndex);
            parameter.second = parameterString.substr(splitIndex + 1);

            output.insert(parameter);
        }

        return output;
    }

    std::string VectorToPath(std::vector<std::string> input) {
        std::string output;

        for (const auto &string : input) {
            if (&string != &input.back()) {
                output += string + "/";
            }
            else {
                if (string == "") {
                    output += "index.html";
                }
                else {
                    output += string;
                }
            }
        }

        return output;
    }

    std::string_view TrimSpacesFront(std::string_view input) {
        size_t i = 0;
        for (; i < input.size(); i++) {
            if (input[i] != ' ') break;
        }
        return input.substr(i, input.size() - i);
    }

    std::string_view TrimSpacesBack(std::string_view input) {
        ssize_t i = input.size() - 1;
        for (; i >= 0; i--) {
            if (input[i] != ' ') break;
        }
        return input.substr(0, i + 1);
    }

    std::string_view TrimSpaces(std::string_view input) {
        return TrimSpacesFront(TrimSpacesBack(input));
    }

    bool IsValidHexCharacter(char input) {
        return (input >= 48 && input <= 57) || (input >= 65 && input <= 70) || (input >= 97 && input <= 102);
    }

    char HexCharacterToValue(char input) {
        if (input >= 97 && input <= 102) return input - 87;
        return input - 48;
    }

    char HexToChar(std::string_view input) {
        assert(input.size() == 2);
        if (!IsValidHexCharacter(input[0]) || !IsValidHexCharacter(input[1])) return - 1;
        return 16 * HexCharacterToValue(tolower(input[0])) + tolower(HexCharacterToValue(tolower(input[1])));
    }

    std::string PercentDecode(std::string_view input) {
        if (input.size() < 3) return std::string(input);
        std::string output;
        output.reserve(input.size());
        for (size_t i = 0; i < input.size() - 2; i++) {
            if (input[i] == '%') {
                char character = HexToChar(input.substr(i + 1, 2));
                output += character;
                i += 2;
            }
            else output += input[i];
        }

        return output;
    }

    void PlusToSpace(std::string& input) {
        for (size_t i = 0; i < input.size(); i++) {
            if (input[i] == '+') input[i] = ' ';
        }
    }

    std::string Join(std::span<std::string> input, std::string_view delimiter) {
        std::string output;

        for (const auto &string : input) {
            if (&string == &input.back()) break;
            output += delimiter;
            output += string;
        }

        return output;
    }
}