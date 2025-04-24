#include "Parenthesis.h"

#include "../Expression.h"
#include "Interfaces/IBinaryOperator.h"
#include "Interfaces/IPrefixUnaryOperator.h"

namespace webwork::expression {

    Parenthesis::Parenthesis() : Block(ExpressionToken::RightParenthesis, "parenthesis"), startIndex(0) {}

    Parenthesis::Parenthesis(std::string_view text, const Chunk &chunk) : Block(ExpressionToken::RightParenthesis, "parenthesis"), startIndex(chunk.GetTextIndex(text)) {}

    std::shared_ptr<const Property> Parenthesis::Evaluate(const std::shared_ptr<const properties::Scope> &scope) const {
        return operations.Evaluate(scope);
    }

    void Parenthesis::AddChild(const std::shared_ptr<Token> &child) {
        operations.AddElement(child);
    }

    void Parenthesis::CloseBlock() {
        operations.CloseExpression();
    }
}


