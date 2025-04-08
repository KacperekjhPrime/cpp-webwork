#ifndef TOKENMERGERULES_H
#define TOKENMERGERULES_H

#include <functional>
#include <map>

#include "BasicToken.h"
#include "TokenType.h"
#include "../Block.h"
#include "../Token.h"

namespace webwork {
    using TokenCreator = std::function<std::shared_ptr<Token>(const std::vector<BasicToken<TokenType>> &tokens, size_t textIndex, size_t lastIndex)>;

    struct MergeRules {
        std::map<TokenType, std::variant<MergeRules, TokenCreator>> children;
    };

    constexpr void AddMergeBranch(MergeRules &rules, std::span<const TokenType> tokens, const TokenCreator &createToken) {
        if (tokens.empty()) return;

        auto *branch = &rules;
        for (size_t i = 0; i < tokens.size() - 1; i++) {
            auto it = branch->children.find(tokens[i]);
            if (it == branch->children.end()) {
                branch->children.insert({tokens[i], MergeRules{}});
                branch = &std::get<MergeRules>(branch->children[tokens[i]]);
            } else {
                branch = &std::get<MergeRules>(it->second);
            }
        }

        branch->children[tokens.back()] = createToken;
    }

    const MergeRules &GetDefaultMergeRules();
}

#endif //TOKENMERGERULES_H
