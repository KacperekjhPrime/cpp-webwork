#ifndef HELPER_H
#define HELPER_H
#include <cxxabi.h>

namespace webwork {
    template <size_t Size>
    struct ConstString {
        char data[Size];

        constexpr ConstString(const char (&str)[Size]) {
            std::copy_n(str, Size, data);
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
}

#endif //HELPER_H
