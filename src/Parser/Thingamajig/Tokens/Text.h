#ifndef THINGAMAJIG_TEXT_H
#define THINGAMAJIG_TEXT_H
#include "../Token.h"
#include "../../Chunk.h"

namespace webwork::tokens {
    class Text final : public Token {
    public:
        std::string text;

        Text(std::string_view text, const Chunk &chunk);

        std::string GetContent(const std::shared_ptr<Scope> &) const override;
    };
}

#endif //TEXT_H
