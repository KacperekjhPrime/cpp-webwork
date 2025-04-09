#include "TokenTree.h"

#include "ExpressionToken.h"
#include "TokenType.h"

namespace webwork {
    std::shared_ptr<TokenTree> MakeRecursiveTrailingSpace(TokenT type) {
        const auto tree = std::make_shared<TokenTree>();
        tree->children[' '] = tree;
        tree->type = type;
        return tree;
    }

    struct DefaultTree {
        std::shared_ptr<TokenTree> tree = std::make_shared<TokenTree>();

        DefaultTree() {
            const auto recursiveIfEnding = MakeRecursiveTrailingSpace(TokenType::If);
            const auto recursiveForEnding = MakeRecursiveTrailingSpace(TokenType::For);
            const auto recursiveInEnding = MakeRecursiveTrailingSpace(TokenType::In);

            const auto in = std::make_shared<TokenTree>();
            in->children[' '] = in;
            AddTextBranch(in, "in", {recursiveInEnding});

            const auto recursiveCommaEnding = MakeRecursiveTrailingSpace(TokenType::Comma);

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

    struct ExpressionTree {
        std::shared_ptr<TokenTree> tree = std::make_shared<TokenTree>();

        ExpressionTree() {
            const auto addition = MakeRecursiveTrailingSpace(ExpressionToken::Addition);
            const auto subtraction = MakeRecursiveTrailingSpace(ExpressionToken::Subtraction);
            const auto multiplication = MakeRecursiveTrailingSpace(ExpressionToken::Multiplication);
            const auto division = MakeRecursiveTrailingSpace(ExpressionToken::Division);
            const auto modulus = MakeRecursiveTrailingSpace(ExpressionToken::Modulus);

            constexpr auto digits = std::array{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

            const auto numberTrailingSpace = MakeRecursiveTrailingSpace(ExpressionToken::Number);
            numberTrailingSpace->type = ExpressionToken::Number;

            const auto numberEnding = std::make_shared<TokenTree>();
            numberEnding->children[' '] = numberTrailingSpace;
            numberEnding->type = ExpressionToken::Number;

            const auto number = std::make_shared<TokenTree>();
            number->children[' '] = numberTrailingSpace;
            number->children['.'] = numberEnding;
            number->type = ExpressionToken::Number;

            tree->children = {
                {' ', tree},
                {'+', addition},
                {'-', subtraction},
                {'*', multiplication},
                {'/', division},
                {'%', modulus},
                {'(', ExpressionToken::LeftParenthesis},
                {')', ExpressionToken::RightParenthesis}
            };

            for (auto digit : digits) {
                tree->children[digit] = number;
                number->children[digit] = number;
                numberEnding->children[digit] = numberEnding;
            }
        }
    };

    const DefaultTree defaultTree{};
    const ExpressionTree expressionTree{};

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

    const std::shared_ptr<TokenTree> &GetExpressionTokenTree() {
        return expressionTree.tree;
    }
}
