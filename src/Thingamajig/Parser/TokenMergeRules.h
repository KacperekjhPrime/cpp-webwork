#ifndef TOKENMERGERULES_H
#define TOKENMERGERULES_H

#include <functional>
#include <map>

#include "BasicToken.h"
#include "TokenType.h"
#include "Tree.h"
#include "../Block.h"
#include "../Token.h"

namespace webwork {
    using TokenCreator = std::function<std::shared_ptr<Token>(size_t textIndex, std::span<const BasicToken> tokens)>;

    using MergeRules = Tree<TokenT, TokenCreator>;

    const std::shared_ptr<MergeRules> &GetDefaultMergeRules();
}

#endif //TOKENMERGERULES_H
