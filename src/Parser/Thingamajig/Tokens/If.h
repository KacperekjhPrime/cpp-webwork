#ifndef THINGAMAJIG_IF_H
#define THINGAMAJIG_IF_H
#include "../Token.h"
#include "../../Block.h"
#include "../../Chunk.h"

namespace webwork::tokens {
    class If final : public Token, public Block<Token> {
    public:
        const std::string condition;

        If(std::string_view text, const Chunk &chunk);

        std::string GetContent(const std::shared_ptr<Scope> &scope) const override;
    };
} // webwork

#endif //IF_H
