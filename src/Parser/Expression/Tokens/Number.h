#ifndef EXPRESSION_NUMBER_H
#define EXPRESSION_NUMBER_H
#include "Interfaces/IEvaluable.h"
#include "../Token.h"
#include "../../Chunk.h"
#include "../../../Properties/Number.h"

namespace webwork::expression {
    class Number final : public Token, public IEvaluable {
    public:
        const std::shared_ptr<properties::Number> value;

        Number(std::string_view text, const Chunk &chunk);

        std::shared_ptr<const Property> Evaluate(const std::shared_ptr<const properties::Scope> &scope) const override;
    };
}

#endif //EXPRESSION_NUMBER_H
