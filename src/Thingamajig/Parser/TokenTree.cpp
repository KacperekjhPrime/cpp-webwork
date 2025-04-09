#include "TokenTree.h"

namespace webwork {
    struct DefaultTree {
        std::shared_ptr<TokenTree<TokenType>> tree = std::make_shared<TokenTree<TokenType>>();

        DefaultTree() {
            const auto recursiveIfEnding = std::make_shared<TokenTree<TokenType>>();
            recursiveIfEnding->children[' '] = recursiveIfEnding;
            recursiveIfEnding->type = TokenType::If;

            const auto recursiveForEnding = std::make_shared<TokenTree<TokenType>>();
            recursiveForEnding->children[' '] = recursiveForEnding;
            recursiveForEnding->type = TokenType::For;

            const auto recursiveInEnding = std::make_shared<TokenTree<TokenType>>();
            recursiveInEnding->children[' '] = recursiveInEnding;
            recursiveInEnding->type = TokenType::In;

            const auto in = std::make_shared<TokenTree<TokenType>>();
            in->children[' '] = in;
            AddTextBranch(in, "in", {recursiveInEnding});

            const auto recursiveCommaEnding = std::make_shared<TokenTree<TokenType>>();
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

    const std::shared_ptr<TokenTree<TokenType>> &GetDefaultTokenTree() {
        return defaultTree.tree;
    }
}
