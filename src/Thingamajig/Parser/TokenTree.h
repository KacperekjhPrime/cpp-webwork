#ifndef TOKENTREE_H
#define TOKENTREE_H

#include <map>
#include <memory>

#include "BasicToken.h"
#include "TokenType.h"
#include "TokenTypeConstants.h"

namespace webwork {
    template <TokenT T>
    class TokenTree {
    public:
        std::map<char, std::variant<std::shared_ptr<TokenTree>, T>> children;
        std::optional<T> type;

        TokenTree() = default;
    };

    template <TokenT T>
    void AddTextBranch(const std::shared_ptr<TokenTree<T>> &tree, std::string_view text, const std::variant<std::shared_ptr<TokenTree<T>>, T> &ending) {
        using TreePtr = std::shared_ptr<TokenTree<T>>;

        if (text.empty()) return;

        auto branch = tree;

        for (size_t i = 0; i < text.size() - 1; i++) {
            const auto existingBranch = branch->children.find(text[i]);
            if (existingBranch != branch->children.end()) {
                const auto &value = existingBranch->second;
                if (std::holds_alternative<T>(value)) {
                    // Replace the ending branch with a new one and set type;
                    const auto type = std::get<T>(value);
                    const auto newBranch = std::make_shared<TokenTree<T>>();
                    newBranch->type = type;
                    existingBranch->second = branch = newBranch;
                } else {
                    branch = std::get<TreePtr>(value);
                }
            } else {
                const auto newBranch = std::make_shared<TokenTree<T>>();
                branch->children[text[i]] = newBranch;
                branch = newBranch;
            }
        }

        branch->children[text.back()] = ending;
    }

    const std::shared_ptr<TokenTree<TokenType>> &GetDefaultTokenTree();
}

#endif //TOKENTREE_H
