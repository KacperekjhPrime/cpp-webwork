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
            in->AddBranch(std::string("in"), {recursiveInEnding});

            const auto recursiveCommaEnding = MakeRecursiveTrailingSpace(TokenType::Comma);

            tree->children = {
                {'{', TokenType::VariableOpening},
                {'}', TokenType::VariableClosing},
                {'\\', TokenType::Escape},
                {' ', in}
            };

            tree->AddBranch(std::string("{if"), {recursiveIfEnding});
            tree->AddBranch(std::string("{for"), {recursiveForEnding});
            tree->AddBranch(std::string("{endif}"), {TokenType::EndIf});
            tree->AddBranch(std::string("{endfor}"), {TokenType::EndFor});
            tree->AddBranch(std::string(","), {recursiveCommaEnding});
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

    const std::shared_ptr<TokenTree> &GetDefaultTokenTree() {
        return defaultTree.tree;
    }

    const std::shared_ptr<TokenTree> &GetExpressionTokenTree() {
        return expressionTree.tree;
    }
}
