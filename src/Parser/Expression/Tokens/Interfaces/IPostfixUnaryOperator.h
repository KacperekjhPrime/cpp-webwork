#ifndef IPOSTFIXUNARYOPERATOR_H
#define IPOSTFIXUNARYOPERATOR_H
#include <memory>

#include "../../../../Properties/Property.h"

namespace webwork {
    class IPostfixUnaryOperator {
    public:
        virtual ~IPostfixUnaryOperator() = default;

        virtual std::shared_ptr<const Property> CalculatePostfix(const std::shared_ptr<const Property> &prop) const = 0;
    };
}

#endif //IPOSTFIXUNARYOPERATOR_H
