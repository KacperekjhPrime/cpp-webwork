#include "Object.h"

#include "../../Logging.h"

namespace webwork::properties {
    std::shared_ptr<Property> &Object::GetProperty(const std::string &key) {
        return properties[key];
    }

    std::shared_ptr<Property> Object::GetProperty(const std::string &key) const {
        const auto it = properties.find(key);
        if (it == properties.end()) {
            return nullptr;
        }
        return it->second;
    }

    std::string Object::ToString() const {
        Log(LogLevel::Warning, "Trying to convert an object into string.");
        return "[Object]";
    }

}
