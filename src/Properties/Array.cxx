#include "Array.h"

namespace webwork::properties {
    Array::Array() {}

    std::shared_ptr<const Property> Array::GetProperty(const std::string &key) const {
        if (key == "size") {
            return CreateProperty(value.size());
        }
        return nullptr;
    }
}