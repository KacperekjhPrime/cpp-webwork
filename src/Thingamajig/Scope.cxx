#include "Scope.h"

namespace webwork {
    Scope::Scope(const std::shared_ptr<properties::Object> &object, const std::shared_ptr<Scope> &previous) : object(object), previous(previous) {}

    std::shared_ptr<Property> Scope::GetProperty(const std::string &name) const {
        const auto property = object->GetProperty(name);
        if (property) {
            return property;
        }
        if (previous) {
            return previous->GetProperty(name);
        }
        return nullptr;
    }
}