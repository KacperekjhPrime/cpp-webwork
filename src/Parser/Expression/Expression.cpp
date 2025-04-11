#include "Expression.h"

#include "Tokens/Number.h"
#include "Tokens/Variable.h"
#include "Tokens/Operators/BinaryOperators.h"

namespace webwork::expression {
    template <class T>
    constexpr TokenCreator<Token> GetOperatorCreator() {
        return [](std::string_view, const Chunk &){ return std::make_shared<T>(); };
    }

    std::shared_ptr<TokenTree> MakeTokenTree() {
        const auto tree = std::make_shared<TokenTree>();

        const auto addition = MakeRecursiveTrailingSpace(ExpressionToken::Addition);
        const auto subtraction = MakeRecursiveTrailingSpace(ExpressionToken::Subtraction);
        const auto multiplication = MakeRecursiveTrailingSpace(ExpressionToken::Multiplication);
        const auto division = MakeRecursiveTrailingSpace(ExpressionToken::Division);
        const auto modulus = MakeRecursiveTrailingSpace(ExpressionToken::Modulus);
        const auto comma = MakeRecursiveTrailingSpace(ExpressionToken::Comma);

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
            {')', ExpressionToken::RightParenthesis},
            {',', comma}
        };

        for (auto digit : digits) {
            tree->children[digit] = number;
            number->children[digit] = number;
            numberEnding->children[digit] = numberEnding;
        }

        return tree;
    }

    const auto tree = MakeTokenTree();

    const auto rules = std::make_shared<MergeRules>();

    const std::map<TokenT, TokenCreator<Token>> map = {
        {ExpressionToken::Addition, GetOperatorCreator<AdditionOperator>()},
        {ExpressionToken::Subtraction, GetOperatorCreator<SubtractionOperator>()},
        {ExpressionToken::Multiplication, GetOperatorCreator<MultiplicationOperator>()},
        {ExpressionToken::Division, GetOperatorCreator<DivisionOperator>()},
        {ExpressionToken::Modulus, GetOperatorCreator<ModulusOperator>()},
        {ExpressionToken::Number, GetTokenCreator<Number>()},
        {ExpressionToken::LeftParenthesis, GetTokenCreator<Parenthesis>()}
    };

    const std::shared_ptr<TokenTree> &GetExpressionTokenTree() {
        return tree;
    }

    const std::shared_ptr<MergeRules> &GetExpressionMergeRules() {
        return rules;
    }

    const std::map<TokenT, TokenCreator<Token>> &GetExpressionTokenMap() {
        return map;
    }

    std::shared_ptr<Parenthesis> ParseExpression(std::string_view text) {
        const auto tokens = TokenizeText(text, tree);
        const auto chunks = MergeTokens(tokens, rules);
        return AssembleTree<Token, Parenthesis, Variable>(text, chunks, map);
    }
}
