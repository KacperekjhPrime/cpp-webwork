#include "Object.h"

#include "../Logging.h"

namespace webwork::properties {
    std::shared_ptr<const Property> Object::Get(const std::string &key) const {
        const auto it = properties.find(key);
        if (it == properties.end()) {
            return nullptr;
        }
        return it->second;
    }

    void Object::Set(const std::string &key, const std::shared_ptr<const Property> &value) {
        properties[key] = value;
    }
}
