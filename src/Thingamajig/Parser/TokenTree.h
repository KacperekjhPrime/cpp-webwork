#ifndef TOKENTREE_H
#define TOKENTREE_H

#include <memory>

#include "TokenTypeConstants.h"
#include "Tree.h"

namespace webwork {
    using TokenTree = Tree<char, TokenT>;

    const std::shared_ptr<TokenTree> &GetDefaultTokenTree();
    const std::shared_ptr<TokenTree> &GetExpressionTokenTree();
}

#endif //TOKENTREE_H
