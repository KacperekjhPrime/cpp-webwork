#ifndef THINGAMAJIG_FOR_H
#define THINGAMAJIG_FOR_H
#include "BlockBase.h"
#include "../Token.h"

namespace webwork {
    struct Chunk;
}

namespace webwork::tokens {
    class For final : public Token, public BlockBase {
    public:
        const std::string variable;
        const std::string collection;
        const std::optional<std::string> index;

        For(std::string_view text, const Chunk &chunk);

        std::string GetContent(const std::shared_ptr<Scope> &scope) const override;
    };
} // webwork

#endif //FOR_H
