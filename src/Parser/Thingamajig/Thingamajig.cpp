#include "Thingamajig.h"

#include <assert.h>

#include "../Expression/Expression.h"
#include "Tokens/Component.h"
#include "Tokens/Expression.h"
#include "Tokens/If.h"
#include "Tokens/For.h"

namespace webwork::thingamajig {
    std::shared_ptr<TokenTree> MakeThingamajigTreeTree() {
        const auto tree = std::make_shared<TokenTree>();

        const auto in = std::make_shared<TokenTree>();
        in->children[' '] = in;
        in->AddBranch(std::string("in"), MakeRecursiveTrailingSpace(TokenType::In));

        tree->children = {
            {'{', TokenType::ExpressionOpening},
            {'}', TokenType::ExpressionClosing},
            {'\\', TokenType::Escape},
            {' ', in}
        };

        tree->AddBranch(std::string_view("{if"), MakeRecursiveTrailingSpace(TokenType::IfOpening));
        tree->AddBranch(std::string_view("{for"), MakeRecursiveTrailingSpace(TokenType::ForOpening));
        tree->AddBranch(std::string_view("{@"), TokenType::ComponentOpening);
        tree->AddBranch(std::string_view("{endif}"), {TokenType::EndIf});
        tree->AddBranch(std::string_view("{endfor}"), {TokenType::EndFor});
        tree->AddBranch(std::string_view(","), MakeRecursiveTrailingSpace(TokenType::Comma));
        tree->AddBranch(std::string_view("="), MakeRecursiveTrailingSpace(TokenType::Equals));

        return tree;
    }

    std::shared_ptr<MergeRules> MakeRecursiveText(TokenT endingToken, const MergeRules::Child &ending) {
        const auto tree = std::make_shared<MergeRules>();
        tree->children[TokenType::Text] = tree;
        tree->children[endingToken] = ending;
        return tree;
    }

    std::shared_ptr<MergeRules> MakeThingamajigMergeRules() {
        const auto rules = std::make_shared<MergeRules>();

        rules->children = {
            {TokenType::ExpressionOpening, MakeRecursiveText(TokenType::ExpressionClosing, MergedToken::Expression)},
            {TokenType::IfOpening, MakeRecursiveText(TokenType::ExpressionClosing, MergedToken::If)},
        };

        const auto forBranchEnding = MakeRecursiveText(TokenType::ExpressionClosing, MergedToken::For);

        constexpr auto forTokensIndexless = std::array<TokenT, 3>{TokenType::ForOpening, TokenType::Text, TokenType::In};
        rules->AddBranch(forTokensIndexless, forBranchEnding);

        constexpr auto forTokensIndexed = std::array<TokenT, 5>{TokenType::ForOpening, TokenType::Text, TokenType::Comma, TokenType::Text, TokenType::In};
        rules->AddBranch(forTokensIndexed, forBranchEnding);

        const auto componentParameterStart = std::make_shared<MergeRules>();

        const auto componentParameterEnding = std::make_shared<MergeRules>();
        componentParameterEnding->children = {
            {TokenType::Comma, componentParameterStart},
            {TokenType::ExpressionClosing, MergedToken::Component},
            {TokenType::Text, componentParameterEnding}
        };

        constexpr auto componentParameterStartTokens = std::array<TokenT, 3>{TokenType::Text, TokenType::Equals, TokenType::Text};
        componentParameterStart->AddBranch(componentParameterStartTokens, componentParameterEnding);

        const auto componentEnding = std::make_shared<MergeRules>();
        componentEnding->children = {
            {TokenType::Comma, componentParameterStart},
            {TokenType::ExpressionClosing, MergedToken::Component}
        };

        constexpr auto componentTokens = std::array<TokenT, 2>{TokenType::ComponentOpening, TokenType::Text};
        rules->AddBranch(componentTokens, componentEnding);

        return rules;
    }

    const auto tree = MakeThingamajigTreeTree();
    const auto rules = MakeThingamajigMergeRules();

    const auto tokenMap = std::map<TokenT, TokenCreator<Token>> {
        {MergedToken::Expression, [](std::string_view text, const Chunk &chunk) -> std::shared_ptr<Token> {
            assert(chunk.tokens.size() > 2);
            const auto expression = chunk.GetText(1, chunk.tokens.size() - 2);
            return std::make_shared<Expression>(chunk.GetTextIndex(text), expression::ParseExpression(expression));
        }},
        {MergedToken::If, [](std::string_view text, const Chunk &chunk) -> std::shared_ptr<Token> {
            assert(chunk.tokens.size() > 2);
            const auto expression = chunk.GetText(1, chunk.tokens.size() - 2);
            return std::make_shared<If>(chunk.GetTextIndex(text), expression::ParseExpression(expression));
        }},
        {MergedToken::For, [](std::string_view text, const Chunk &chunk) -> std::shared_ptr<Token> {
            const auto &tokens = chunk.tokens;

            assert(tokens.size() > 3);
            const bool hasIndex = tokens[2].type == TokenType::Comma;

            std::optional<std::string_view> index;
            size_t expressionStart = hasIndex ? 5 : 3;
            if (hasIndex) {
                index = tokens[3].text;
                expressionStart = 5;
            }

            const size_t expressionEnd = tokens.size() - 2;
            const auto expression = expression::ParseExpression(chunk.GetText(expressionStart, expressionEnd));

            return std::make_shared<For>(chunk.GetTextIndex(text), tokens[1].text, index, expression);
        }},
        {MergedToken::Component, [](std::string_view text, const Chunk &chunk) {
            const auto &tokens = chunk.tokens;

            assert(tokens.size() > 2);
            std::vector<Component::Value> values;

            if (tokens.size() > 3) {
                size_t valueStart = 3;
                for (size_t i = 5; i < tokens.size(); i++) {
                    if (tokens[i].type == TokenType::Comma || tokens[i].type == TokenType::ExpressionClosing) {
                        const auto expression = expression::ParseExpression(chunk.GetText(valueStart + 2, i - 1));
                        values.push_back({std::string(tokens[valueStart].text), expression});
                        valueStart = i + 1;
                        i++;
                    }
                }
            }

            return std::make_shared<Component>(chunk.GetTextIndex(text), chunk.tokens[1].text, values);
        }}
    };

    const std::shared_ptr<TokenTree> &GetThingamajigTokenTree() {
        return tree;
    }

    const std::shared_ptr<MergeRules> &GetThingamajigMergeRules() {
        return rules;
    }

    const std::map<TokenT, TokenCreator<Token>> &GetThingamajigTokenMap() {
        return tokenMap;
    }

    std::shared_ptr<Root> ParseThingamajig(std::string_view text) {
        const auto tokens = TokenizeText(text, GetThingamajigTokenTree());
        const auto chunks = MergeTokens(tokens, GetThingamajigMergeRules());
        return AssembleTree<Token, Root, Text>(text, chunks, GetThingamajigTokenMap());
    }
}