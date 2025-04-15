#include "Parenthesis.h"

#include "../Expression.h"
#include "Interfaces/IBinaryOperator.h"
#include "Interfaces/IUnaryOperator.h"

namespace webwork::expression {
    Parenthesis::Parenthesis() : Block(ExpressionToken::RightParenthesis, "parenthesis"), startIndex(0) {}

    Parenthesis::Parenthesis(std::string_view text, const Chunk &chunk) : Block(ExpressionToken::RightParenthesis, "parenthesis"), startIndex(chunk.GetTextIndex(text)) {}

    std::shared_ptr<const Property> Parenthesis::Evaluate(const std::shared_ptr<const properties::Scope> &scope) const {
        auto lhs = initialExpression->Evaluate(scope);
        if (initialUnary) lhs = initialUnary->Calculate(lhs);

        for (const auto &operation : operations) {
            auto rhs = operation.expression->Evaluate(scope);
            if (operation.unaryOperator) {
                rhs = operation.unaryOperator->Calculate(rhs);
            }
            lhs = operation.binaryOperator->Calculate(lhs, rhs);
        }

        return lhs;
    }

    void Parenthesis::AddChild(const std::shared_ptr<Token> &child) {
        if (!initialExpression) {
            if (!initialUnary) {
                initialUnary = std::dynamic_pointer_cast<const IUnaryOperator>(child);
                if (initialUnary) return;
            }
            initialExpression = std::dynamic_pointer_cast<const IEvaluable>(child);
            if (initialExpression) return;
            throw std::runtime_error("Invalid expression token. IEvaluable expected.");
        }

        if (operations.empty() || operations.back().expression) {
            operations.emplace_back();
        }

        auto &last = operations.back();
        if (last.binaryOperator) {
            if (!last.unaryOperator) {
                last.unaryOperator = std::dynamic_pointer_cast<const IUnaryOperator>(child);
                if (last.unaryOperator) return;
            }
            last.expression = std::dynamic_pointer_cast<const IEvaluable>(child);
            if (last.expression) return;
            throw std::runtime_error("Invalid expression token. IEvaluable expected.");
        }

        last.binaryOperator = std::dynamic_pointer_cast<const IBinaryOperator>(child);
        if (last.binaryOperator) return;
        throw std::runtime_error("Invalid expression token. IBinaryOperator expected.");
    }

    void Parenthesis::CloseBlock() {
        if (!initialExpression) {
            throw std::runtime_error("Empty parenthesis.");
        }
    }
}


