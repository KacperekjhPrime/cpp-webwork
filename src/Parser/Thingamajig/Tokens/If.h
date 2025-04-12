#ifndef THINGAMAJIG_IF_H
#define THINGAMAJIG_IF_H
#include "BlockBase.h"
#include "../Token.h"
#include "../../Expression/Tokens/Parenthesis.h"

namespace webwork::thingamajig {
    class If final : public Token, public BlockBase {
    public:
        const std::shared_ptr<expression::Parenthesis> expression;

        If(size_t textIndex, const std::shared_ptr<expression::Parenthesis> &expression);

        std::string GetContent(const std::shared_ptr<Scope> &scope) const override;
    };
} // webwork

#endif //IF_H
