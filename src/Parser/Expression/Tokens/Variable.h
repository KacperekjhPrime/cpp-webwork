#ifndef EXPRESSION_VARIABLE_H
#define EXPRESSION_VARIABLE_H

#include "../IEvaluable.h"
#include "../Token.h"
#include "../../Chunk.h"

namespace webwork::expression {
    class Variable final : public Token, public IEvaluable {
    public:
        const std::string variable;

        Variable(std::string_view text, const Chunk &chunk);

        std::shared_ptr<const Property> Evaluate(const std::shared_ptr<const Scope> &scope) const override;
    };
}

#endif //EXPRESSION_VARIABLE_H
