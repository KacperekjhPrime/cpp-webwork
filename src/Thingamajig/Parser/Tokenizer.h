#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <vector>

#include "./BasicToken.h"
#include "./TokenTree.h"

namespace webwork {
    void PushText(std::vector<BasicToken> &tokens, std::string_view text, size_t i, size_t depth, size_t tokenStart);
    void PushToken(std::vector<BasicToken> &tokens, std::string_view text, TokenT type, size_t i, size_t depth);

    /**
     * Separates text into an array of <c>BasicToken</c>s according to <c>TokenTree</c>
     * @param text Text to parse
     * @param tree <c>TokenTree</c> of rules used divide the text. Unmatched string become <c>TokenType::Text</c>
     * @return <c>std::vector</c> of parsed tokens
     */
    std::vector<BasicToken> TokenizeText(std::string_view text, const std::shared_ptr<TokenTree> &tree);
}

#endif //TOKENIZER_H
