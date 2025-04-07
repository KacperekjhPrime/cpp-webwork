#include "Helper.h"
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

        if (previousFound != input.size() - 1) {
            output.push_back(std::string(input).substr(previousFound, input.size() - 1));
        }

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
}