#ifndef NESTABLETOKEN_H
#define NESTABLETOKEN_H
#include <memory>
#include <vector>

#include "Token.h"
#include "Parser/TokenType.h"

namespace webwork {
    class Block {
    protected:
        Block(TokenT closingToken, std::string_view name);

    public:
        std::vector<std::shared_ptr<Token>> children;
        const TokenT closingToken;
        const std::string name;

        virtual ~Block() = default;
    };
}

#endif //NESTABLETOKEN_H