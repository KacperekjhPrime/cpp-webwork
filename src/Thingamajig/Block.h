#ifndef NESTABLETOKEN_H
#define NESTABLETOKEN_H
#include <memory>
#include <vector>

#include "Parser/BasicToken.h"
#include "Token.h"

namespace webwork {
    class Block {
    protected:
        Block(TokenType closingToken, std::string_view name);

    public:
        std::vector<std::shared_ptr<Token>> children;
        const TokenType closingToken;
        const std::string name;

        virtual ~Block() = default;
    };
}

#endif //NESTABLETOKEN_H