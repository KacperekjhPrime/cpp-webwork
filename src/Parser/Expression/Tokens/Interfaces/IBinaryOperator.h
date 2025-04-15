#ifndef BINARYOPERATOR_H
#define BINARYOPERATOR_H
#include <memory>

#include "../../../../Properties/Property.h"

namespace webwork::expression {
    class IBinaryOperator {
    public:
        virtual ~IBinaryOperator() = default;

        virtual std::shared_ptr<const Property> Calculate(const std::shared_ptr<const Property> &a, const std::shared_ptr<const Property> &b) const = 0;
    };
}

#endif //BINARYOPERATOR_H
