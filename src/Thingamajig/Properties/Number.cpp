#include "Number.h"

namespace webwork::properties {
    Number::Number(double data) : data(data) {}

    std::string Number::ToString() const {
        return std::to_string(data);
    }

    bool Number::GetBoolValue() const {
        return static_cast<bool>(data);
    }
}