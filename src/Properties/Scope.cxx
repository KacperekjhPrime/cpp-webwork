#include "Scope.h"

namespace webwork::properties {
    Scope::Scope(const std::shared_ptr<Object> &object, const std::shared_ptr<const Scope> &previous) : object(object), previous(previous) {}

    std::shared_ptr<const Object> Scope::GetObject() const {
        return object;
    }

    std::shared_ptr<Object> &Scope::GetObject() {
        return object;
    }
}