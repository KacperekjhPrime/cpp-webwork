#include "Tokenizer.h"

namespace webwork {
    void PushText(std::vector<BasicToken> &tokens, std::string_view text, size_t i, size_t depth, size_t tokenStart) {
        const ssize_t length = i - depth - tokenStart;
        if (length > 0) {
            tokens.emplace_back(TokenText, std::string_view(text.data() + tokenStart, length));
        }
    }

    void PushToken(std::vector<BasicToken> &tokens, std::string_view text, TokenT type, size_t i, size_t depth) {
        tokens.emplace_back(type, std::string_view(text.data() + i - depth, depth + 1));
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
                    PushText(tokens, text, index, depth, tokenStart);
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
                PushText(tokens, text, i, depth, tokenStart);
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
            PushText(tokens, text, text.length(), depth, tokenStart);
        }

        return tokens;
    }
}