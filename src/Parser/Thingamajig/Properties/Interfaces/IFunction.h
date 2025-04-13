#ifndef IFUNCTION_H
#define IFUNCTION_H
#include <memory>

#include "../../Property.h"

namespace webwork::properties {
    class IFunction {
    public:
        virtual std::shared_ptr<const Property> Execute(std::span<std::shared_ptr<const Property>> properties) const = 0;

        virtual ~IFunction() = default;
    };
}

#endif //IFUNCTION_H