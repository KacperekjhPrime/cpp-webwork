#ifndef VARIABLE_H
#define VARIABLE_H

#include "../Token.h"
#include "../../Chunk.h"

namespace webwork::tokens {
    class Variable final : public Token {
    public:
        std::string variableName;

        Variable(std::string_view text, const Chunk &chunk);

        std::string GetContent(const std::shared_ptr<Scope> &scope) const override;
    };
}

#endif //VARIABLE_H
