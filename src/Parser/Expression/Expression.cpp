#include "Expression.h"

#include "Tokens/Boolean.h"
#include "Tokens/Number.h"
#include "Tokens/Variable.h"
#include "Tokens/Operators/BinaryOperators.h"
#include "Tokens/Operators/LogicNegationOperator.h"
#include "Tokens/Operators/SubtractionOperator.h"

namespace webwork::expression {
    template <class T>
    concept OperatorToken = requires()
    {
        { T::GetInstance() } -> std::convertible_to<std::shared_ptr<T>>;
    };

    template <OperatorToken T>
    constexpr TokenCreator<Token> GetOperatorCreator() {
        return [](std::string_view, const Chunk &){ return T::GetInstance(); };
    }

    std::shared_ptr<TokenTree> MakeTokenTree() {
        const auto tree = std::make_shared<TokenTree>();

        constexpr auto digits = std::array{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

        const auto numberTrailingSpace = MakeRecursiveTrailingSpace(ExpressionToken::Number);

        const auto numberEnding = std::make_shared<TokenTree>();
        numberEnding->children[' '] = numberTrailingSpace;
        numberEnding->type = ExpressionToken::Number;

        const auto number = std::make_shared<TokenTree>();
        number->children[' '] = numberTrailingSpace;
        number->children['.'] = numberEnding;
        number->type = ExpressionToken::Number;

        tree->children = {
            {' ', tree},
            {'+', ExpressionToken::Addition},
            {'-', ExpressionToken::Subtraction},
            {'*', ExpressionToken::Multiplication},
            {'/', ExpressionToken::Division},
            {'%', ExpressionToken::Modulus},
            {'(', ExpressionToken::LeftParenthesis},
            {')', ExpressionToken::RightParenthesis},
            {',', ExpressionToken::Comma},
            {'^', ExpressionToken::LogicXor},
            {'!', ExpressionToken::LogicNegation}
        };

        tree->AddBranch(std::string_view("&&"), ExpressionToken::LogicAnd);
        tree->AddBranch(std::string_view("||"), ExpressionToken::LogicOr);
        tree->AddBranch(std::string_view("true"), ExpressionToken::True);
        tree->AddBranch(std::string_view("false"), ExpressionToken::False);

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
        {ExpressionToken::LeftParenthesis, GetTokenCreator<Parenthesis>()},
        {ExpressionToken::LogicAnd, GetOperatorCreator<LogicAndOperator>()},
        {ExpressionToken::LogicOr, GetOperatorCreator<LogicOrOperator>()},
        {ExpressionToken::LogicXor, GetOperatorCreator<LogicXorOperator>()},
        {ExpressionToken::LogicNegation, GetOperatorCreator<LogicNegationOperator>()},
        {ExpressionToken::True, [](std::string_view, const Chunk &) {
            return std::make_shared<Boolean>(true);
        }},
        {ExpressionToken::False, [](std::string_view, const Chunk &) {
            return std::make_shared<Boolean>(false);
        }}
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
