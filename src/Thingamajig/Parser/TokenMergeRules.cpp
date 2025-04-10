#include "TokenMergeRules.h"

#include "../Tokens/Variable.h"
#include "../Tokens/If.h"
#include "../Tokens/For.h"

namespace webwork {
    using namespace tokens;

    struct TokenMergeRules {
        std::shared_ptr<MergeRules> rules = std::make_shared<MergeRules>();

        TokenMergeRules() {
            constexpr auto variableTokens = std::array<TokenT, 3>{TokenType::VariableOpening, TokenType::Text, TokenType::VariableClosing};
            rules->AddBranch(variableTokens, [](auto index, auto tokens) {
                return std::make_shared<Variable>(index, tokens[1].text);
            });

            constexpr auto ifTokens = std::array<TokenT, 3>{TokenType::If, TokenType::Text, TokenType::VariableClosing};
            rules->AddBranch(ifTokens, [](auto index, auto tokens) {
                return std::make_shared<If>(index, tokens[1].text);
            });

            constexpr auto indexlessForTokens = std::array<TokenT, 5>{TokenType::For, TokenType::Text, TokenType::In, TokenType::Text, TokenType::VariableClosing};
            rules->AddBranch(indexlessForTokens, [](auto index, auto tokens) {
                return std::make_shared<For>(index, tokens[1].text, tokens[3].text, std::nullopt);
            });

            constexpr auto indexedForTokens = std::array<TokenT, 7>{TokenType::For, TokenType::Text, TokenType::Comma, TokenType::Text, TokenType::In, TokenType::Text, TokenType::VariableClosing};
            rules->AddBranch(indexedForTokens, [](auto index, auto tokens) {
                return std::make_shared<For>(index, tokens[1].text, tokens[5].text, tokens[3].text);
            });
        }
    };

    TokenMergeRules mergeRules{};

    const std::shared_ptr<MergeRules> &GetDefaultMergeRules() {
        return mergeRules.rules;
    }
}
