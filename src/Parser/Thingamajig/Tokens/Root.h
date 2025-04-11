#ifndef ROOT_H
#define ROOT_H
#include "../Token.h"
#include "../../Block.h"

namespace webwork::tokens {
    class Root final : public Token, public Block<Token> {
    public:
        Root();

        std::string GetContent(const std::shared_ptr<Scope> &scope) const override;
    };
}

#endif //ROOT_H
