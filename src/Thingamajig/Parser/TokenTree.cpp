#include "TokenTree.h"

namespace webwork {
    struct DefaultTree {
        TokenTree tree = {
            .children = {
                {'{', {TokenType::VariableOpening}},
                {'}', {TokenType::VariableClosing}},
                {'\\', {TokenType::Escape}}
            }
        };

        DefaultTree() {
            AddTextBranch(tree, "{if ", TokenType::If);
            AddTextBranch(tree, "{for ", TokenType::For);
            AddTextBranch(tree, " in ", TokenType::In);
            AddTextBranch(tree, "{endif}", TokenType::EndIf);
            AddTextBranch(tree, "{endfor}", TokenType::EndFor);
            AddTextBranch(tree, ", ", TokenType::Comma);
        }
    };

    const DefaultTree defaultTree{};

    void AddTextBranch(TokenTree &tree, std::string_view text, TokenType type) {
        if (text.empty()) return;

        auto *branch = &tree;
        for (size_t i = 0; i < text.size() - 1; i++) {
            const auto &nextBranch = branch->children.find(text[i]);
            if (nextBranch == branch->children.end()) {
                branch->children[text[i]] = TokenTree{};
                branch = &std::get<TokenTree>(branch->children[text[i]]);
            } else {
                if (std::holds_alternative<TokenType>(nextBranch->second)) {
                    const auto oldType = std::get<TokenType>(nextBranch->second);
                    nextBranch->second = TokenTree{{}, oldType};
                }
                std::get<TokenTree>(nextBranch->second).children.insert(std::make_pair(text[i], TokenTree{}));
                branch = &std::get<TokenTree>(branch->children[text[i]]);
            }
        }
        branch->children[text.back()] = type;
    }

    const TokenTree &GetDefaultTokenTree() {
        return defaultTree.tree;
    }
}
