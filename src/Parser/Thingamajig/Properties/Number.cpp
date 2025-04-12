#include "Number.h"

namespace webwork::properties {
    Number::Number(double data) : value(data) {}

    std::string Number::ToString() const {
        return std::format("{}", value);
    }

    bool Number::GetBoolValue() const {
        return static_cast<bool>(value);
    }
}