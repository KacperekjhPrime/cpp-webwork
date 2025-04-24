#include "Parenthesis.h"

#include "../Expression.h"
#include "Interfaces/IBinaryOperator.h"
#include "Interfaces/IPrefixUnaryOperator.h"

namespace webwork::expression {

    Parenthesis::Parenthesis() : Block(ExpressionToken::RightParenthesis, "parenthesis"), startIndex(0) {}

    Parenthesis::Parenthesis(std::string_view text, const Chunk &chunk) : Block(ExpressionToken::RightParenthesis, "parenthesis"), startIndex(chunk.GetTextIndex(text)) {}

    std::shared_ptr<const Property> Parenthesis::Evaluate(const std::shared_ptr<const properties::Scope> &scope) const {
        bool hasLhs = false;
        std::shared_ptr<const Property> lhs = nullptr;

        for (const auto &operation : operations) {
            auto rhs = operation.expression->Evaluate(scope);
            if (operation.prefixOperator) {
                rhs = operation.prefixOperator->CalculatePrefix(rhs, scope);
            }
            if (operation.postfixOperator) {
                rhs = operation.postfixOperator->CalculatePostfix(rhs, scope);
            }
            if (hasLhs) {
                lhs = operation.binaryOperator->Calculate(lhs, rhs, scope);
            } else {
                lhs = rhs;
                hasLhs = true;
            }
        }

        return lhs;
    }

    void Parenthesis::AddChild(const std::shared_ptr<Token> &child) {
        if (operations.back().expression) {
            if (!operations.back().postfixOperator) {
                const auto postfix = std::dynamic_pointer_cast<IPostfixUnaryOperator>(child);
                operations.back().postfixOperator = postfix;
                if (postfix) return;
            }
            operations.emplace_back();
        }

        auto &last = operations.back();
        if (last.binaryOperator || operations.size() == 1) {
            if (!last.prefixOperator) {
                last.prefixOperator = std::dynamic_pointer_cast<const IPrefixUnaryOperator>(child);
                if (last.prefixOperator) return;
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
        if (!operations.back().expression) {
            throw std::runtime_error("Empty parenthesis.");
        }
    }
}


