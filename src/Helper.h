#ifndef HELPER_H
#define HELPER_H
#include <algorithm>
#include <string>
#include <cxxabi.h>
#include <filesystem>
#include <string_view>
#include <vector>
#include <map>

namespace webwork {
    template <size_t Size>
    struct ConstString {
        char data[Size];

        constexpr ConstString(const char (&str)[Size]) {
            std::copy_n(str, Size, data);
        }

        constexpr operator std::string_view() const {
            return std::string_view(data, Size);
        }

        constexpr operator std::string() const {
            return std::string(data, Size);
        }
    };

    template <class T>
    std::string GetTypeName() {
        int status = 0;
        const auto mangled = typeid(T).name();
        const auto demangled = abi::__cxa_demangle(mangled, nullptr, nullptr, &status);

        std::string name = {status == 0 ? demangled : mangled};
        std::free(demangled);

        return name;
    }

    template <class ...Ts>
    struct Types;

    std::vector<std::string> SplitString(const std::string_view input, const char delimiter);
    std::vector<std::string> SplitString(const std::string_view input, const std::string delimiter);
    std::multimap<std::string, std::string> ParseParameters(std::string_view parametersString);
    std::string VectorToPath(std::vector<std::string> input);
    std::string_view TrimSpacesFront(std::string_view input);
    std::string_view TrimSpacesBack(std::string_view input);
    std::string_view TrimSpaces(std::string_view input);
    std::string ReadTextFile(const std::filesystem::path &path);
}

#endif //HELPER_H
