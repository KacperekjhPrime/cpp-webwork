#ifndef IPREFIXUNARYOPERATOR_H
#define IPREFIXUNARYOPERATOR_H
#include <memory>

#include "../../../../Properties/Property.h"

namespace webwork {
    class IPrefixUnaryOperator {
    public:
        virtual ~IPrefixUnaryOperator() = default;

        virtual std::shared_ptr<const Property> CalculatePrefix(const std::shared_ptr<const Property> &prop) const = 0;
    };
}

#endif //IPREFIXUNARYOPERATOR_H
