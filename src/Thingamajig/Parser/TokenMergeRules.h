#ifndef TOKENMERGERULES_H
#define TOKENMERGERULES_H

#include <functional>
#include <map>

#include "BasicToken.h"
#include "../Block.h"
#include "../Token.h"

namespace webwork {
    using TokenCreator = std::function<std::shared_ptr<Token>(const std::vector<BasicToken> &tokens, size_t textIndex, size_t lastIndex)>;

    struct MergeRules {
        std::map<TokenType, std::variant<MergeRules, TokenCreator>> children;
    };

    void AddMergeBranch(MergeRules &rules, std::span<const TokenType> tokens, const TokenCreator &createToken);
    const MergeRules &GetDefaultMergeRules();
}

#endif //TOKENMERGERULES_H
