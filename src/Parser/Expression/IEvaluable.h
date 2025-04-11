#ifndef IEVALUABLE_H
#define IEVALUABLE_H
#include <memory>

#include "../Thingamajig/Property.h"
#include "../Thingamajig/Scope.h"

namespace webwork::expression {
    class IEvaluable {
    public:
        virtual ~IEvaluable() = default;

        virtual std::shared_ptr<const Property> Evaluate(const std::shared_ptr<const Scope> &scope) const = 0;
    };
}

#endif //IEVALUABLE_H
