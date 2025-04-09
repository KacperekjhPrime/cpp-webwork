#ifndef EXPRESSIONTOKEN_H
#define EXPRESSIONTOKEN_H
#include "TokenTypeConstants.h"

namespace webwork::ExpressionToken {
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

#endif //EXPRESSIONTOKEN_H
