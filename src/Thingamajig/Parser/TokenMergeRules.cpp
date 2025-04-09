#include "TokenMergeRules.h"

#include "../Tokens/Variable.h"
#include "../Tokens/If.h"
#include "../Tokens/For.h"

namespace webwork {
    using namespace tokens;

    struct TokenMergeRules {
        MergeRules rules = {};

        TokenMergeRules() {
            constexpr auto variableTokens = std::array<TokenT, 3>{TokenType::VariableOpening, TokenType::Text, TokenType::VariableClosing};
            AddMergeBranch(rules, variableTokens, [](const auto &tokens, size_t index, size_t token) {
                return std::make_shared<Variable>(index, tokens[token - 1].text);
            });

            constexpr auto ifTokens = std::array<TokenT, 3>{TokenType::If, TokenType::Text, TokenType::VariableClosing};
            AddMergeBranch(rules, ifTokens, [](const auto &tokens, size_t index, size_t token) {
                return std::make_shared<If>(index, tokens[token - 1].text);
            });

            constexpr auto indexlessForTokens = std::array<TokenT, 5>{TokenType::For, TokenType::Text, TokenType::In, TokenType::Text, TokenType::VariableClosing};
            AddMergeBranch(rules, indexlessForTokens, [](const auto &tokens, size_t index, size_t token) {
                return std::make_shared<For>(index, tokens[token - 3].text, tokens[token - 1].text, std::nullopt);
            });

            constexpr auto indexedForTokens = std::array<TokenT, 7>{TokenType::For, TokenType::Text, TokenType::Comma, TokenType::Text, TokenType::In, TokenType::Text, TokenType::VariableClosing};
            AddMergeBranch(rules, indexedForTokens, [](const auto &tokens, size_t index, size_t token) {
                return std::make_shared<For>(index, tokens[token - 5].text, tokens[token - 1].text, tokens[token - 3].text);
            });
        }
    };

    TokenMergeRules mergeRules{};

    const MergeRules &GetDefaultMergeRules() {
        return mergeRules.rules;
    }
}
