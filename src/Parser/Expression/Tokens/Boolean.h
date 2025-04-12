#ifndef EXPRESSION_BOOLEAN_H
#define EXPRESSION_BOOLEAN_H
#include "../Token.h"
#include "Interfaces/IEvaluable.h"
#include "../../Thingamajig/Properties/Boolean.h"

namespace webwork::expression {
    class Boolean final : public Token, public IEvaluable{
    public:
        const std::shared_ptr<const properties::Boolean> value;

        explicit Boolean(bool value);

        std::shared_ptr<const Property> Evaluate(const std::shared_ptr<const Scope> &scope) const override;
    };
}

#endif //BOOLEAN_H
