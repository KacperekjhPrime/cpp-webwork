//
// Created by Kacper on 08/04/25.
//

#include "String.h"

namespace webwork::properties {
    String::String(std::string_view data) : value(data) {}

    std::string String::GetStringValue() const {
        return value;
    }
}