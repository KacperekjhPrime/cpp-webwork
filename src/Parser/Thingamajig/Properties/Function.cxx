#include "Function.h"

namespace webwork::properties {
    Function::Function(const FunctionT &function) : function(function) {}

    std::shared_ptr<const Property> Function::Execute(std::span<std::shared_ptr<const Property>> properties) const {
        return function(properties);
    }
}