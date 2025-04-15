#include "Number.h"

namespace webwork::properties {
    Number::Number(double data) : value(data) {}

    bool Number::GetBoolValue() const {
        return value != 0;
    }

    double Number::GetNumberValue() const {
        return value;
    }

    std::string Number::GetStringValue() const {
        return std::format("{}", value);
    }
}