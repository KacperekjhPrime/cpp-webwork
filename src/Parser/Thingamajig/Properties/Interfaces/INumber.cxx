#include "INumber.h"

namespace webwork::properties {
    double INumber::GetValue(const INumber &prop) {
        return prop.GetNumberValue();
    }
}