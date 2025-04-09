#ifndef PARSER_H
#define PARSER_H
#include <vector>

#include "BasicToken.h"
#include "TokenMergeRules.h"
#include "TokenTree.h"
#include "../Tokens/Root.h"
#include "../Tokens/Text.h"

namespace webwork {
    template <class T>
    size_t GetTextIndex(const std::vector<BasicToken<T>> &tokens, size_t tokenIndex) {
        return tokens[tokenIndex].text.data() - tokens[0].text.data();
    }

    template <class T>
    void EscapeTokens(std::vector<std::shared_ptr<Token>> &merged, const std::vector<BasicToken<T>> &tokens, size_t escapeFrom, size_t i) {
        const auto *ptr = tokens[escapeFrom].text.data();
        size_t textLength = 0;
        for (size_t j = escapeFrom; j <= i; j++) {
            textLength += tokens[j].text.size();
        }
        merged.push_back(std::make_shared<tokens::Text>(GetTextIndex(tokens, i), std::string_view(ptr, textLength)));
    }

    /**
     * Merges, escapes and assembles tokens into a tree according to <c>MergeRules</c>
     * @param tokens Array of <c>BasicToken</c>s to process
     * @param rules <c>TokenTree</c> of rules used to merge the tokens and convert them into <c>Token</c>s
     * @return Tree of <c>Token</c>s starting with <c>Root</c>
     */
    std::shared_ptr<tokens::Root> AssembleTokenTree(const std::vector<BasicToken<TokenType>> &tokens, const MergeRules &rules);
}

#endif //PARSER_H
