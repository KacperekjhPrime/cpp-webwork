#include "Thingamajig.h"

#include <assert.h>

#include "../Expression/Expression.h"
#include "Tokens/Expression.h"
#include "Tokens/If.h"
#include "Tokens/For.h"

namespace webwork::thingamajig {
    std::shared_ptr<TokenTree> MakeThingamajigTreeTree() {
        const auto tree = std::make_shared<TokenTree>();

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

        tree->AddBranch(std::string_view("{if"), {recursiveIfEnding});
        tree->AddBranch(std::string_view("{for"), {recursiveForEnding});
        tree->AddBranch(std::string_view("{endif}"), {TokenType::EndIf});
        tree->AddBranch(std::string_view("{endfor}"), {TokenType::EndFor});
        tree->AddBranch(std::string_view(","), {recursiveCommaEnding});

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
            {TokenType::VariableOpening, MakeRecursiveText(TokenType::VariableClosing, TokenType::VariableOpening)},
            {TokenType::If, MakeRecursiveText(TokenType::VariableClosing, TokenType::If)},
        };

        const auto forBranchEnding = MakeRecursiveText(TokenType::VariableClosing, TokenType::For);

        constexpr auto forTokensIndexless = std::array<TokenT, 3>{TokenType::For, TokenType::Text, TokenType::In};
        rules->AddBranch(forTokensIndexless, forBranchEnding);

        constexpr auto forTokensIndexed = std::array<TokenT, 5>{TokenType::For, TokenType::Text, TokenType::Comma, TokenType::Text, TokenType::In};
        rules->AddBranch(forTokensIndexed, forBranchEnding);

        return rules;
    }

    const auto tree = MakeThingamajigTreeTree();
    const auto rules = MakeThingamajigMergeRules();

    const auto tokenMap = std::map<TokenT, TokenCreator<Token>> {
        {TokenType::VariableOpening, [](std::string_view text, const Chunk &chunk) -> std::shared_ptr<Token> {
            assert(chunk.tokens.size() > 2);
            const auto expression = chunk.GetText(1, chunk.tokens.size() - 2);
            return std::make_shared<Expression>(chunk.GetTextIndex(text), expression::ParseExpression(expression));
        }},
        {TokenType::If, [](std::string_view text, const Chunk &chunk) -> std::shared_ptr<Token> {
            assert(chunk.tokens.size() > 2);
            const auto expression = chunk.GetText(1, chunk.tokens.size() - 2);
            return std::make_shared<If>(chunk.GetTextIndex(text), expression::ParseExpression(expression));
        }},
        {TokenType::For, [](std::string_view text, const Chunk &chunk) -> std::shared_ptr<Token> {
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