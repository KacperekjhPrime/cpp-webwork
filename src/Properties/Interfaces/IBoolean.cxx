#include "IBoolean.h"

namespace webwork::properties {
    bool IBoolean::GetValue(const IBoolean &prop) {
        return prop.GetBoolValue();
    }

}