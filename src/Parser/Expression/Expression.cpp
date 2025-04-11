#include "Expression.h"

namespace webwork::expression {
    std::shared_ptr<TokenTree> MakeTokenTree() {
        const auto tree = std::make_shared<TokenTree>();

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

        return tree;
    }

    const auto tree = MakeTokenTree();

    const std::shared_ptr<TokenTree> &GetExpressionTokenTree() {
        return tree;
    }
}