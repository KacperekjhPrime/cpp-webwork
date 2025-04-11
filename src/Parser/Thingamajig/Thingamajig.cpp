#include "Thingamajig.h"

#include <assert.h>

#include "../Expression/Expression.h"
#include "Tokens/Expression.h"
#include "Tokens/If.h"
#include "Tokens/For.h"

namespace webwork::thingamajig {
    using namespace tokens;

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

    std::shared_ptr<MergeRules> MakeThingamajigMergeRules() {
        const auto rules = std::make_shared<MergeRules>();

        constexpr auto variableTokens = std::array<TokenT, 3>{TokenType::VariableOpening, TokenType::Text, TokenType::VariableClosing};
        rules->AddBranch(variableTokens, TokenType::VariableOpening);

        constexpr auto ifTokens = std::array<TokenT, 3>{TokenType::If, TokenType::Text, TokenType::VariableClosing};
        rules->AddBranch(ifTokens, TokenType::If);

        constexpr auto indexlessForTokens = std::array<TokenT, 5>{TokenType::For, TokenType::Text, TokenType::In, TokenType::Text, TokenType::VariableClosing};
        rules->AddBranch(indexlessForTokens, TokenType::For);

        constexpr auto indexedForTokens = std::array<TokenT, 7>{TokenType::For, TokenType::Text, TokenType::Comma, TokenType::Text, TokenType::In, TokenType::Text, TokenType::VariableClosing};
        rules->AddBranch(indexedForTokens, TokenType::For);

        return rules;
    }

    const auto tree = MakeThingamajigTreeTree();
    const auto rules = MakeThingamajigMergeRules();

    const auto tokenMap = std::map<TokenT, TokenCreator<Token>> {
        {TokenType::VariableOpening, [](std::string_view text, const Chunk &chunk) -> std::shared_ptr<Token> {
            assert(chunk.tokens.size() == 3);
            return std::make_shared<Expression>(chunk.GetTextIndex(text), expression::ParseExpression(chunk.tokens[1].text));
        }},
        {TokenType::If, [](std::string_view text, const Chunk &chunk) -> std::shared_ptr<Token> {
            assert(chunk.tokens.size() == 3);
            return std::make_shared<If>(chunk.GetTextIndex(text), expression::ParseExpression(chunk.tokens[1].text));
        }},
        {TokenType::For, GetTokenCreator<For>()},
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