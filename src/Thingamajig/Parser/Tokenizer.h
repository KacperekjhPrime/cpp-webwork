#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <vector>

#include "./BasicToken.h"
#include "./TokenTree.h"

namespace webwork {
    template <class T>
    void PushText(std::vector<BasicToken<T>> &tokens, std::string_view text, size_t i, size_t depth, size_t tokenStart) {
        const ssize_t length = i - depth - tokenStart;
        if (length > 0) {
            tokens.emplace_back(T{0}, std::string_view(text.data() + tokenStart, length));
        }
    }

    template <class T>
    void PushToken(std::vector<BasicToken<T>> &tokens, std::string_view text, T type, size_t i, size_t depth) {
        tokens.emplace_back(type, std::string_view(text.data() + i - depth, depth + 1));
    }

    /**
     * Separates text into an array of <c>BasicToken</c>s according to <c>TokenTree</c>
     * @tparam T Type of the token type enum. Value 0 is always reserved for text
     * @param text Text to parse
     * @param tree <c>TokenTree</c> of rules used divide the text. Unmatched string become <c>TokenType::Text</c>
     * @return <c>std::vector</c> of parsed tokens
     */
    template <class T>
    std::vector<BasicToken<T>> TokenizeText(std::string_view text, const std::shared_ptr<TokenTree<T>> &tree) {
        std::vector<BasicToken<T>> tokens;

        std::shared_ptr<const TokenTree<T>> currentTree = tree;
        size_t tokenStart = 0;
        size_t depth = 0;
        std::optional<std::pair<size_t, T>> lastValidToken = std::nullopt;

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
                    currentTree = tree;
                    i--;
                }
                depth = 0;
                continue;
            }

            const auto &value = nextTree->second;
            if (std::holds_alternative<T>(value)) {
                PushText(tokens, text, i, depth, tokenStart);
                PushToken(tokens, text, std::get<T>(value), i, depth);
                tokenStart = i + 1;
                depth = 0;
                lastValidToken = std::nullopt;
            } else {
                currentTree = std::get<std::shared_ptr<TokenTree<T>>>(value);
                depth++;
                if (currentTree->type.has_value()) {
                    lastValidToken = {{i, currentTree->type.value()}};
                }
            }
        }
        PushText(tokens, text, text.length(), depth, tokenStart);

        return tokens;
    }
}

#endif //TOKENIZER_H
