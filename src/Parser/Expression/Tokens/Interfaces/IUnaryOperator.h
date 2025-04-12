#ifndef IBINARYOPERATOR_H
#define IBINARYOPERATOR_H
#include <memory>

#include "../../../Thingamajig/Property.h"

namespace webwork {
    class IUnaryOperator {
    public:
        virtual ~IUnaryOperator() = default;

        virtual std::shared_ptr<const Property> Calculate(const std::shared_ptr<const Property> &prop) const = 0;
    };
}

#endif //IBINARYOPERATOR_H
