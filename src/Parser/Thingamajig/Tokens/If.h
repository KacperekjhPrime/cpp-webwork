#ifndef THINGAMAJIG_IF_H
#define THINGAMAJIG_IF_H
#include "../Token.h"
#include "../../Block.h"
#include "../../Chunk.h"
#include "../../Expression/Tokens/Parenthesis.h"

namespace webwork::tokens {
    class If final : public Token, public Block<Token> {
    public:
        const std::shared_ptr<expression::Parenthesis> expression;

        If(size_t textIndex, const std::shared_ptr<expression::Parenthesis> &expression);

        std::string GetContent(const std::shared_ptr<Scope> &scope) const override;
    };
} // webwork

#endif //IF_H
