#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <memory>

#include "../Parser.h"
#include "../TokenTypeConstants.h"

namespace webwork::expression {
    namespace ExpressionToken {
        enum ExpressionToken : unsigned {
            Text = TokenText,

            Addition = TokensStart,
            Subtraction,
            Multiplication,
            Division,
            Modulus,
            LeftParenthesis,
            RightParenthesis,
            Number
        };
    }

    const std::shared_ptr<TokenTree> &GetExpressionTokenTree();
}

#endif //EXPRESSION_H
