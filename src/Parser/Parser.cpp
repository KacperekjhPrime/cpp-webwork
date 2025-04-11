#include "Parser.h"

#include <ranges>
#include <stack>

namespace webwork {
    void PushTextToken(std::vector<BasicToken> &tokens, std::string_view text, size_t i, size_t depth, size_t tokenStart) {
        const ssize_t length = i - depth - tokenStart;
        if (length > 0) {
            tokens.emplace_back(TokenText, std::string_view(text.data() + tokenStart, length));
        }
    }

    void PushToken(std::vector<BasicToken> &tokens, std::string_view text, TokenT type, size_t i, size_t depth) {
        tokens.emplace_back(type, std::string_view(text.data() + i - depth, depth + 1));
    }

    void PushTextChunk(std::vector<Chunk> &chunks, const std::vector<BasicToken> &tokens, size_t i, size_t depth) {
        auto &last = chunks.back();
        if (chunks.size() > 0 && last.type == TokenText) {
            last.tokens = {last.tokens.data(), last.tokens.size() + depth};
        } else {
            const auto data = tokens.data() + i - depth;
            chunks.push_back({{data, depth + 1}, TokenText});
        }
    }

    void PushChunk(std::vector<Chunk> &chunks, const std::vector<BasicToken> &tokens, size_t i, size_t depth, TokenT type, bool &escape) {
        if (escape) {
            escape = false;
            if ((type & TokenInescapableBit) == 0) {
                PushTextChunk(chunks, tokens, i, depth);
                return;
            }
            PushTextChunk(chunks, tokens, i - depth - 1, 0);
        }

        if (type == TokenText) {
            PushTextChunk(chunks, tokens, i, depth);
        } else {
            const auto data = tokens.data() + i - depth;
            chunks.push_back({ { data, depth + 1 }, type });
        }
    }

    std::shared_ptr<TokenTree> MakeRecursiveTrailingSpace(TokenT type) {
        const auto tree = std::make_shared<TokenTree>();
        tree->children[' '] = tree;
        tree->type = type;
        return tree;
    }

    std::vector<BasicToken> TokenizeText(std::string_view text, const std::shared_ptr<TokenTree> &tree) {
        std::vector<BasicToken> tokens;

        std::shared_ptr<const TokenTree> currentTree = tree;
        size_t tokenStart = 0;
        size_t depth = 0;
        std::optional<std::pair<size_t, TokenT>> lastValidToken = std::nullopt;

        for (size_t i = 0; i < text.size(); i++) {
            const auto &nextTree = currentTree->children.find(text[i]);
            if (nextTree == currentTree->children.end()) {
                if (lastValidToken.has_value()) {
                    const auto [index, type] = lastValidToken.value();
                    depth -= i - index;
                    PushTextToken(tokens, text, index, depth, tokenStart);
                    PushToken(tokens, text, type, index, depth);
                    tokenStart = index + 1;
                    i = index;
                    lastValidToken = std::nullopt;
                } else if (currentTree != tree) {
                    i--;
                }
                currentTree = tree;
                depth = 0;
                continue;
            }

            const auto &value = nextTree->second;
            if (std::holds_alternative<TokenT>(value)) {
                PushTextToken(tokens, text, i, depth, tokenStart);
                PushToken(tokens, text, std::get<TokenT>(value), i, depth);
                tokenStart = i + 1;
                depth = 0;
                lastValidToken = std::nullopt;
            } else {
                currentTree = std::get<std::shared_ptr<TokenTree>>(value);
                depth++;
                if (currentTree->type.has_value()) {
                    lastValidToken = {{i, currentTree->type.value()}};
                }
            }
        }

        if (lastValidToken.has_value()) {
            const auto [index, type] = lastValidToken.value();
            PushToken(tokens, text, type, text.length(), depth);
        } else {
            PushTextToken(tokens, text, text.length(), depth, tokenStart);
        }

        return tokens;
    }

    std::vector<Chunk> MergeTokens(const std::vector<BasicToken> &tokens, const std::shared_ptr<MergeRules> &rules) {
        std::vector<Chunk> chunks;

        auto currentRules = rules;
        std::optional<std::pair<size_t, TokenT>> lastValidChunk = std::nullopt;
        size_t depth = 0;
        bool escapeNext = false;

        for (size_t i = 0; i < tokens.size(); i++) {
            if (!escapeNext && tokens[i].type == TokenEscape) {
                escapeNext = true;
                continue;
            }

            const auto nextTree = currentRules->children.find(tokens[i].type);
            if (nextTree == currentRules->children.end()) {
                if (lastValidChunk.has_value()) {
                    const auto [index, type] = *lastValidChunk;
                    PushChunk(chunks, tokens, index, depth + index - i, type, escapeNext);
                    i = index;
                } else if (currentRules == rules) {
                    PushChunk(chunks, tokens, i, 0, tokens[i].type, escapeNext);
                } else {
                    i -= depth;
                }
                currentRules = rules;
                depth = 0;
            } else {
                const auto &value = nextTree->second;
                if (std::holds_alternative<std::shared_ptr<MergeRules>>(value)) {
                    const auto &tree = std::get<std::shared_ptr<MergeRules>>(value);
                    if (tree->type.has_value()) {
                        lastValidChunk = std::make_pair(i, tree->type.value());
                    }
                    currentRules = tree;
                } else {
                    PushChunk(chunks, tokens, i, depth, std::get<TokenT>(value), escapeNext);
                    depth = 0;
                    currentRules = rules;
                }
                depth++;
            }
        }

        if (escapeNext) {
            PushTextChunk(chunks, tokens, tokens.size(), 0);
        }

        return chunks;
    }
}
