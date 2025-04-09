#include "TokenTree.h"

#include "TokenType.h"

namespace webwork {
    struct DefaultTree {
        std::shared_ptr<TokenTree> tree = std::make_shared<TokenTree>();

        DefaultTree() {
            const auto recursiveIfEnding = std::make_shared<TokenTree>();
            recursiveIfEnding->children[' '] = recursiveIfEnding;
            recursiveIfEnding->type = TokenType::If;

            const auto recursiveForEnding = std::make_shared<TokenTree>();
            recursiveForEnding->children[' '] = recursiveForEnding;
            recursiveForEnding->type = TokenType::For;

            const auto recursiveInEnding = std::make_shared<TokenTree>();
            recursiveInEnding->children[' '] = recursiveInEnding;
            recursiveInEnding->type = TokenType::In;

            const auto in = std::make_shared<TokenTree>();
            in->children[' '] = in;
            AddTextBranch(in, "in", {recursiveInEnding});

            const auto recursiveCommaEnding = std::make_shared<TokenTree>();
            recursiveCommaEnding->children[' '] = recursiveCommaEnding;
            recursiveCommaEnding->type = TokenType::Comma;

            tree->children = {
                {'{', TokenType::VariableOpening},
                {'}', TokenType::VariableClosing},
                {'\\', TokenType::Escape},
                {' ', in}
            };

            AddTextBranch(tree, "{if", {recursiveIfEnding});
            AddTextBranch(tree, "{for", {recursiveForEnding});
            AddTextBranch(tree, "{endif}", {TokenType::EndIf});
            AddTextBranch(tree, "{endfor}", {TokenType::EndFor});
            AddTextBranch(tree, ",", {recursiveCommaEnding});
        }
    };

    const DefaultTree defaultTree{};

    void AddTextBranch(const std::shared_ptr<TokenTree> &tree, std::string_view text, const TokenTree::Child &ending) {
        if (text.empty()) return;

        auto branch = tree;

        for (size_t i = 0; i < text.size() - 1; i++) {
            const auto existingBranch = branch->children.find(text[i]);
            if (existingBranch != branch->children.end()) {
                const auto &value = existingBranch->second;
                if (std::holds_alternative<TokenT>(value)) {
                    // Replace the ending branch with a new one and set type;
                    const auto type = std::get<TokenT>(value);
                    const auto newBranch = std::make_shared<TokenTree>();
                    newBranch->type = type;
                    existingBranch->second = branch = newBranch;
                } else {
                    branch = std::get<std::shared_ptr<TokenTree>>(value);
                }
            } else {
                const auto newBranch = std::make_shared<TokenTree>();
                branch->children[text[i]] = newBranch;
                branch = newBranch;
            }
        }

        branch->children[text.back()] = ending;
    }

    const std::shared_ptr<TokenTree> &GetDefaultTokenTree() {
        return defaultTree.tree;
    }
}
