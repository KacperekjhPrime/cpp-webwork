#include "Number.h"

namespace webwork::properties {
    Number::Number(double data) : value(data) {}

    std::string Number::ToString() const {
        return std::format("{}", value);
    }

    bool Number::GetBoolValue() const {
        return value != 0;
    }

    double Number::GetNumberValue() const {
        return value;
    }
}