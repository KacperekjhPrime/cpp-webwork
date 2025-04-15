#include "Scope.h"

namespace webwork::properties {
    Scope::Scope(const std::shared_ptr<const properties::Object> &object, const std::shared_ptr<const Scope> &previous) : object(object), previous(previous) {}

    std::shared_ptr<const Property> Scope::GetProperty(const std::string &name) const {
        if (object) {
            const auto property = object->GetProperty(name);
            if (property) {
                return property;
            }
        }

        if (previous) {
            return previous->GetProperty(name);
        }

        Log(LogLevel::Warning, "Property {} is undefined.", name);
        return nullptr;
    }
}