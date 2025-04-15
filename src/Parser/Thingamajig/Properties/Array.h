#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include <memory>

#include "Helper.h"
#include "../Property.h"

namespace webwork::properties {
    template <class T>
    concept Iterable = requires (const T collection)
    {
        std::begin(collection) != std::end(collection);
        *std::begin(collection);
        ++std::declval<decltype(std::begin(collection))&>();
    };

    class Array final : public Property {
    public:
        std::vector<std::shared_ptr<Property>> value;

        Array();

        template <Iterable T>
        explicit Array(const T &collection) {
            value.reserve(collection.size());
            for (const auto &element : collection) {
                value.push_back(CreateProperty(element));
            }
        }

        template <class ...Ts>
        explicit Array(const Ts ...parameters) {
            value.reserve(sizeof...(parameters));
            (value.push_back(CreateProperty(parameters)), ...);
        }
    };
}

#endif //ARRAY_H
