//
// Created by Kacper on 08/04/25.
//

#include "Boolean.h"

namespace webwork::properties {
    Boolean::Boolean(bool value) : value(value) {}

    std::string Boolean::ToString() const {
        return value ? "true" : "false";
    }

    bool Boolean::GetBoolValue() const {
        return value;
    }

    double Boolean::GetNumberValue() const {
        return value ? 1.0 : 0.0;
    }
}