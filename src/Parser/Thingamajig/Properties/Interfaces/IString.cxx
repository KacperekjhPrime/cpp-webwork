#include "IString.h"

namespace webwork::properties {
    std::string IString::GetValue(const IString &prop) {
        return prop.GetStringValue();
    }
}