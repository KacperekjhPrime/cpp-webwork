#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include <memory>

#include "Helper.h"
#include "Property.h"
#include "Interfaces/IDotAccessible.h"

namespace webwork::properties {
    namespace detail {
        template <class T>
        constexpr bool IsAssignableToConstProperty = requires(std::shared_ptr<const Property> property, const T &t) {
            property = t;
        };
    }

    template <class T>
    concept Iterable = requires (const T collection)
    {
        std::begin(collection) != std::end(collection);
        *std::begin(collection);
        ++std::declval<decltype(std::begin(collection))&>();
    };

    class Array final : public Property, public IDotAccessible {
    public:
        std::vector<std::shared_ptr<Property>> value;

        Array();

        std::shared_ptr<const Property> GetProperty(const std::string &key) const override;

        template <Iterable T>
        explicit Array(const T &collection) {
            value.reserve(collection.size());
            for (const auto &element : collection) {
                value.push_back(CreateProperty(element));
            }
        }

        template <class T>
        void PushElement(const T &element) {
            if constexpr (detail::IsAssignableToConstProperty<T>) {
                value.push_back(element);
            } else {
                value.push_back(CreateProperty(element));
            }
        }

        template <class ...Ts>
        explicit Array(const Ts ...parameters) {
            value.reserve(sizeof...(parameters));
            (PushElement(parameters), ...);
        }
    };
}

#endif //ARRAY_H
