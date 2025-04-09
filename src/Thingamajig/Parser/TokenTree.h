#ifndef TOKENTREE_H
#define TOKENTREE_H

#include <map>
#include <memory>

#include "BasicToken.h"
#include "TokenTypeConstants.h"

namespace webwork {
    class TokenTree {
    public:
        using Child = std::variant<std::shared_ptr<TokenTree>, TokenT>;

        std::map<char, Child> children;
        std::optional<unsigned int> type;

        TokenTree() = default;
    };

    void AddTextBranch(const std::shared_ptr<TokenTree> &tree, std::string_view text, const TokenTree::Child &ending);

    const std::shared_ptr<TokenTree> &GetDefaultTokenTree();
}

#endif //TOKENTREE_H
