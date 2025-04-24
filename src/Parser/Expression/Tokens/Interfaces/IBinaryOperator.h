#ifndef IBINARYOPERATOR_H
#define IBINARYOPERATOR_H
#include <memory>

#include "../../../../Properties/Property.h"
#include "../../../../Properties/Scope.h"

namespace webwork::expression {
    class IBinaryOperator {
    public:
        virtual ~IBinaryOperator() = default;

        virtual std::shared_ptr<const Property> Calculate(const std::shared_ptr<const Property> &a, const std::shared_ptr<const Property> &b, const std::shared_ptr<const properties::Scope> &scope) const = 0;
    };
}

#endif //BINARYOPERATOR_H
