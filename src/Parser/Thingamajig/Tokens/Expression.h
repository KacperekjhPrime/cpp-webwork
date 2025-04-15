#ifndef THINGAMAJIG_EXPRESSION_H
#define THINGAMAJIG_EXPRESSION_H
#include "../Token.h"
#include "../../Expression/Tokens/Parenthesis.h"

namespace webwork::thingamajig {
    class Expression final : public Token {
    public:
        const std::shared_ptr<const expression::Parenthesis> expression;

        Expression(size_t textIndex, const std::shared_ptr<const expression::Parenthesis> &expression);

        std::string GetContent(const std::shared_ptr<properties::Scope> &scope) const override;
    };
}

#endif //THINGAMAJIG_EXPRESSION_H
