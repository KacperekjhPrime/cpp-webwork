#include "Parser.h"

#include <stack>

#include "Tokens/Text.h"

namespace webwork {
    void PushText(std::vector<BasicToken> &tokens, std::string_view text, size_t i, size_t depth, size_t tokenStart) {
        const ssize_t length = i - depth - tokenStart;
        if (length > 0) {
            tokens.emplace_back(TokenType::Text, std::string_view(text.data() + tokenStart, length));
        }
    }

    void PushToken(std::vector<BasicToken> &tokens, std::string_view text, TokenType type, size_t i, size_t depth) {
        tokens.emplace_back(type, std::string_view(text.data() + i - depth, depth + 1));
    }

    std::vector<BasicToken> ParseTokens(std::string_view text, const TokenTree &tree) {
        std::vector<BasicToken> tokens;

        const TokenTree *currentTree = &tree;
        size_t tokenStart = 0;
        size_t depth = 0;
        std::optional<std::pair<size_t, TokenType>> lastValidToken = std::nullopt;

        for (size_t i = 0; i < text.size(); i++) {
            const auto &nextTree = currentTree->children.find(text[i]);
            if (nextTree == currentTree->children.end()) {
                if (lastValidToken.has_value()) {
                    const auto [index, type] = lastValidToken.value();
                    depth -= i - index;
                    PushText(tokens, text, index, depth, tokenStart);
                    PushToken(tokens, text, type, index, depth);
                    tokenStart = index + 1;
                    i = index;
                    lastValidToken = std::nullopt;
                } else if (currentTree != &tree) {
                    currentTree = &tree;
                    i--;
                }
                depth = 0;
                continue;
            }

            const auto &value = nextTree->second;
            if (std::holds_alternative<TokenType>(value)) {
                PushText(tokens, text, i, depth, tokenStart);
                PushToken(tokens, text, std::get<TokenType>(value), i, depth);
                tokenStart = i + 1;
                depth = 0;
                lastValidToken = std::nullopt;
            } else {
                currentTree = &std::get<TokenTree>(value);
                depth++;
                if (currentTree->type.has_value()) {
                    lastValidToken = {{i, currentTree->type.value()}};
                }
            }
        }
        PushText(tokens, text, text.length(), depth, tokenStart);

        return tokens;
    }

    size_t GetTextIndex(const std::vector<BasicToken> &tokens, size_t tokenIndex) {
        return tokens[tokenIndex].text.data() - tokens[0].text.data();
    }

    void EscapeTokens(std::vector<std::shared_ptr<Token>> &merged, const std::vector<BasicToken> &tokens, size_t escapeFrom, size_t i) {
        const auto *ptr = tokens[escapeFrom].text.data();
        size_t textLength = 0;
        for (size_t j = escapeFrom; j <= i; j++) {
            textLength += tokens[j].text.size();
        }
        merged.push_back(std::make_shared<Text>(GetTextIndex(tokens, i), std::string_view(ptr, textLength)));
    }

    std::shared_ptr<Root> AssembleTokenTree(const std::vector<BasicToken> &tokens, const MergeRules &rules) {
        const auto root = std::make_shared<Root>();

        auto *currentRules = &rules;
        size_t depth = 0;
        std::optional<size_t> escapeFrom = std::nullopt;

        std::stack<std::shared_ptr<Block>> parents;
        parents.push(root);

        for (size_t i = 0; i < tokens.size(); i++) {
            if (tokens[i].type == TokenType::Escape && !escapeFrom.has_value()) {
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
                            parents.top()->children.push_back(std::make_shared<Text>(GetTextIndex(tokens, index), mergedText));
                        } else {
                            parents.top()->children.push_back(std::make_shared<Text>(GetTextIndex(tokens, i), tokens[i].text));
                        }
                    }
                    escapeFrom.reset();
                } else if (currentRules != &rules) {
                    throw std::runtime_error(std::format("Unexpected token at {}: {}", tokens[i].text.data() - tokens[0].text.data(), tokens[i].text));
                } else if (tokens[i].type == parents.top()->closingToken) {
                    parents.pop();
                } else if (tokens[i].type == TokenType::Text) {
                    parents.top()->children.push_back(std::make_shared<Text>(GetTextIndex(tokens, i), tokens[i].text));
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
            parents.top()->children.push_back(std::make_shared<Text>(GetTextIndex(tokens, escapeFrom.value() - 1), tokens[escapeFrom.value() - 1].text));
        }

        if (parents.size() > 1) {
            const auto token = std::dynamic_pointer_cast<Token>(parents.top());
            throw std::runtime_error(std::format("Unterminated {} block at {}.", parents.top()->name, token->startIndex));
        }

        return root;
    }
}
