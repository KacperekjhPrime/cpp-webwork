#ifndef IUNARYOPERATOR_H
#define IUNARYOPERATOR_H
#include <memory>

#include "../../../../Properties/Property.h"

namespace webwork {
    class IUnaryOperator {
    public:
        virtual ~IUnaryOperator() = default;

        virtual std::shared_ptr<const Property> Calculate(const std::shared_ptr<const Property> &prop) const = 0;
    };
}

#endif //IUNARYOPERATOR_H
