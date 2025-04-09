#include "Parser.h"

#include <utility>
#include <stack>

namespace webwork {
    using namespace tokens;

    std::shared_ptr<Root> AssembleTokenTree(const std::vector<BasicToken<TokenType>> &tokens, const MergeRules &rules) {
        const auto root = std::make_shared<Root>();

        auto *currentRules = &rules;
        size_t depth = 0;
        std::optional<size_t> escapeFrom = std::nullopt;

        std::stack<std::shared_ptr<Block>> parents;
        parents.push(root);

        for (size_t i = 0; i < tokens.size(); i++) {
            if (std::to_underlying(tokens[i].type) == TokenEscape && !escapeFrom.has_value()) {
                escapeFrom = i + 1;
                continue;
            }

            const auto &nextTree = currentRules->children.find(tokens[i].type);
            if (nextTree == currentRules->children.end()) {
                if (escapeFrom.has_value()) {
                    if (currentRules != &rules) {
                        EscapeTokens(parents.top()->children, tokens, escapeFrom.value(), i - 1);
                        currentRules = &rules;
                        depth = 0;
                        i--;
                    } else {
                        if (tokens[i].type == TokenType::Text) {
                            const auto index = escapeFrom.value() - 1;
                            auto mergedText = std::string(tokens[index].text);
                            mergedText += tokens[i].text;
                            parents.top()->children.push_back(std::make_shared<tokens::Text>(GetTextIndex(tokens, index), mergedText));
                        } else {
                            parents.top()->children.push_back(std::make_shared<tokens::Text>(GetTextIndex(tokens, i), tokens[i].text));
                        }
                    }
                    escapeFrom.reset();
                } else if (currentRules != &rules) {
                    throw std::runtime_error(std::format("Unexpected token at {}: {}", tokens[i].text.data() - tokens[0].text.data(), tokens[i].text));
                } else if (tokens[i].type == parents.top()->closingToken) {
                    parents.pop();
                } else if (tokens[i].type == TokenType::Text || (std::to_underlying(tokens[i].type) & TokenAllowStrayBit) > 0) {
                    parents.top()->children.push_back(std::make_shared<tokens::Text>(GetTextIndex(tokens, i), tokens[i].text));
                } else {
                    throw std::runtime_error(std::format("Unexpected token at {}: {}", tokens[i].text.data() - tokens[0].text.data(), tokens[i].text));
                }
                continue;
            }

            if (std::holds_alternative<TokenCreator>(nextTree->second)) {
                if (escapeFrom.has_value()) {
                    EscapeTokens(parents.top()->children, tokens, escapeFrom.value(), i);
                    escapeFrom.reset();
                } else {
                    const auto token = std::get<TokenCreator>(nextTree->second)(tokens, GetTextIndex(tokens, i - depth), i);
                    parents.top()->children.push_back(token);

                    const auto parent = std::dynamic_pointer_cast<Block>(token);
                    if (parent) {
                        parents.push(parent);
                    }
                }
                currentRules = &rules;
                depth = 0;
            } else {
                currentRules = &std::get<MergeRules>(nextTree->second);
                depth++;
            }
        }

        if (escapeFrom.has_value()) {
            parents.top()->children.push_back(std::make_shared<tokens::Text>(GetTextIndex(tokens, escapeFrom.value() - 1), tokens[escapeFrom.value() - 1].text));
        }

        if (parents.size() > 1) {
            const auto token = std::dynamic_pointer_cast<Token>(parents.top());
            throw std::runtime_error(std::format("Unterminated {} block at {}.", parents.top()->name, token->startIndex));
        }

        return root;
    }
}
