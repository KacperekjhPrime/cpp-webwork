#include "TokenTree.h"

namespace webwork {
    struct DefaultTree {
        TokenTree<TokenType> tree = {
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

    const TokenTree<TokenType> &GetDefaultTokenTree() {
        return defaultTree.tree;
    }
}
