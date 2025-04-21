#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <memory>

#include "Token.h"
#include "../Parser.h"
#include "../TokenTypeConstants.h"
#include "Tokens/Parenthesis.h"

namespace webwork::expression {
    namespace ExpressionToken {
        enum ExpressionToken : TokenT {
            Text = TokenText,

            Addition = TokensStart,
            Subtraction,
            Multiplication,
            Division,
            Modulus,

            LogicAnd,
            LogicOr,
            LogicXor,
            LogicNegation,

            GreaterThan,
            LessThan,
            GreaterOrEqualTo,
            LessOrEqualTo,
            EqualTo,
            NotEqualTo,

            LeftParenthesis,
            RightParenthesis,
            LeftSquareParenthesis,
            RightSquareParenthesis,
            Number,
            Comma,
            True,
            False,

            FunctionCall,
            Indexing
        };
    }

    const std::shared_ptr<TokenTree> &GetExpressionTokenTree();
    const std::shared_ptr<MergeRules> &GetExpressionMergeRules();
    const std::map<TokenT, TokenCreator<Token>> &GetExpressionTokenMap();

    std::shared_ptr<Parenthesis> ParseExpression(std::string_view text);
}

#endif //EXPRESSION_H
