//
// Created by Kacper on 08/04/25.
//

#include "Boolean.h"

namespace webwork::properties {
    Boolean::Boolean(bool value) : value(value) {}

    bool Boolean::GetBoolValue() const {
        return value;
    }

    double Boolean::GetNumberValue() const {
        return value ? 1.0 : 0.0;
    }

    std::string Boolean::GetStringValue() const {
        return value ? "true" : "false";
    }
}