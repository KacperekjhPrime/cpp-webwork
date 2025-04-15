#ifndef PROPERTIES_HELPER_H
#define PROPERTIES_HELPER_H
#include <type_traits>

#include "Boolean.h"
#include "Number.h"
#include "String.h"

namespace webwork::properties {
    template <class T>
    concept Numeric = std::is_floating_point_v<T> || std::is_integral_v<T>;

    template <class T>
    concept Stringable = std::same_as<T, std::string> || std::same_as<T, std::string_view> || std::same_as<T, char *>;

    template <class T>
    struct PropertyType;

    template <>
    struct PropertyType<bool> {
        using Type = Boolean;
        using Interface = IBoolean;
    };

    template <Numeric T>
    struct PropertyType<T> {
        using Type = Number;
        using Interface = INumber;
    };

    template <Stringable T>
    struct PropertyType<T> {
        using Type = String;
        using Interface = IString;
    };

    template <class T>
    using PropertyTypeT = typename PropertyType<T>::Type;

    template <class T>
    using PropertyInterfaceT = typename PropertyType<T>::Interface;

    template <class T>
    auto CreateProperty(const T &value) {
        return std::make_shared<PropertyTypeT<T>>(value);
    }
}

#endif //HELPER_H
