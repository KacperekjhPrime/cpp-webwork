#ifndef IPOSTFIXUNARYOPERATOR_H
#define IPOSTFIXUNARYOPERATOR_H
#include <memory>

#include "../../../../Properties/Property.h"
#include "../../../../Properties/Scope.h"

namespace webwork {
    class IPostfixUnaryOperator {
    public:
        virtual ~IPostfixUnaryOperator() = default;

        virtual std::shared_ptr<const Property> CalculatePostfix(const std::shared_ptr<const Property> &prop, const std::shared_ptr<const properties::Scope> &scope) const = 0;
    };
}

#endif //IPOSTFIXUNARYOPERATOR_H
