#ifndef TOKENTREE_H
#define TOKENTREE_H

#include <map>
#include <memory>

#include "BasicToken.h"

namespace webwork {
    class TokenTree {
    public:
        std::map<char, std::variant<TokenTree, TokenType>> children;
        std::optional<TokenType> type;
    };

    void AddTextBranch(TokenTree &tree, std::string_view text, TokenType type);
    const TokenTree &GetDefaultTokenTree();
}

#endif //TOKENTREE_H
