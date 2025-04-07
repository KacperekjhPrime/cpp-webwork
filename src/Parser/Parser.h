#ifndef PARSER_H
#define PARSER_H
#include <vector>

#include "BasicToken.h"
#include "TokenMergeRules.h"
#include "TokenTree.h"
#include "Tokens/Root.h"

namespace webwork {
    /**
     * Separates text into an array of <c>BasicToken</c>s according to <c>TokenTree</c>
     * @param text Text to parse
     * @param tree <c>TokenTree</c> of rules used divide the text. Unmatched string become <c>TokenType::Text</c>
     * @return <c>std::vector</c> of parsed tokens
     */
    std::vector<BasicToken> ParseTokens(std::string_view text, const TokenTree &tree);

    /**
     * Merges, escapes and assembles tokens into a tree according to <c>MergeRules</c>
     * @param tokens Array of <c>BasicToken</c>s to process
     * @param rules <c>TokenTree</c> of rules used to merge the tokens and convert them into <c>Token</c>s
     * @return Tree of <c>Token</c>s starting with <c>Root</c>
     */
    std::shared_ptr<Root> AssembleTokenTree(const std::vector<BasicToken> &tokens, const MergeRules &rules);
}

#endif //PARSER_H
