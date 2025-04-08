#include "Helper.h"

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
}