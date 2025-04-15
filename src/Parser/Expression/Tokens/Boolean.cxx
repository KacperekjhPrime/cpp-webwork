#include "Boolean.h"

namespace webwork::expression {
    Boolean::Boolean(bool value) : value(std::make_shared<properties::Boolean>(value)) {}

    std::shared_ptr<const Property> Boolean::Evaluate(const std::shared_ptr<const properties::Scope> &) const {
        return value;
    }
}