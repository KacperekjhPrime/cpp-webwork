#ifndef TOKENTREE_H
#define TOKENTREE_H

#include <map>
#include <memory>

#include "BasicToken.h"
#include "TokenType.h"

namespace webwork {
    template <class T>
    class TokenTree {
    public:
        std::map<char, std::variant<TokenTree, T>> children;
        std::optional<T> type;
    };

    template <class T>
    constexpr void AddTextBranch(TokenTree<T> &tree, std::string_view text, T type) {
        if (text.empty()) return;

        auto *branch = &tree;
        for (size_t i = 0; i < text.size() - 1; i++) {
            const auto &nextBranch = branch->children.find(text[i]);
            if (nextBranch == branch->children.end()) {
                branch->children[text[i]] = TokenTree<T>{};
                branch = &std::get<TokenTree<T>>(branch->children[text[i]]);
            } else {
                if (std::holds_alternative<TokenType>(nextBranch->second)) {
                    const auto oldType = std::get<TokenType>(nextBranch->second);
                    nextBranch->second = TokenTree<T>{{}, oldType};
                }
                std::get<TokenTree<T>>(nextBranch->second).children.insert(std::make_pair(text[i], TokenTree<T>{}));
                branch = &std::get<TokenTree<T>>(branch->children[text[i]]);
            }
        }
        branch->children[text.back()] = type;
    }

    const TokenTree<TokenType> &GetDefaultTokenTree();
}

#endif //TOKENTREE_H
