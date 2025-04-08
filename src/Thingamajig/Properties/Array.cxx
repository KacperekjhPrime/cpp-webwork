#include "Array.h"

namespace webwork::properties {
    std::string Array::ToString() const {
        std::string result = "[";
        for (const auto &element : array) {
            result += element->ToString();
        }
        result += ']';
        return result;
    }
}