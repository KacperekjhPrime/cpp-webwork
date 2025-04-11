#include "Parenthesis.h"

#include "../Expression.h"
#include "IBinaryOperator.h"

namespace webwork::expression {
    // TODO: Add Block::OnChildAdd(), Block::OnClose() to handle invalid expressions

    Parenthesis::Parenthesis() : Block(ExpressionToken::RightParenthesis, "parenthesis"), startIndex(0) {}

    Parenthesis::Parenthesis(std::string_view text, const Chunk &chunk) : Block(ExpressionToken::RightParenthesis, "parenthesis"), startIndex(chunk.GetTextIndex(text)) {}

    std::shared_ptr<const Property> Parenthesis::Evaluate(const std::shared_ptr<const Scope> &scope) const {
        if (children.empty()) {
            throw std::runtime_error(std::format("Cannot evaluate an empty exception at {}", startIndex));
        }

        if (children.size() == 1) {
            const auto value = std::dynamic_pointer_cast<IEvaluable>(children[0]);
            if (!value) {
                throw std::runtime_error("Only child of Parenthesis in not IEvaluable.");
            }
            return value->Evaluate(scope);
        }

        if (children.size() % 2 == 0) {
            throw std::runtime_error("Cannot evaluate an expression with an even number of children");
        }

        auto lhs = std::dynamic_pointer_cast<IEvaluable>(children[0])->Evaluate(scope);
        if (lhs == nullptr) throw std::runtime_error(std::format("Expression element at index 0 is not IEvaluable."));

        for (size_t i = 1; i < children.size() - 1; i += 2) {
            const auto op = std::dynamic_pointer_cast<IBinaryOperator>(children[i]);
            if (op == nullptr) throw std::runtime_error(std::format("Expression element at index {} is not IBinaryOperator.", i));

            const auto rhs = std::dynamic_pointer_cast<IEvaluable>(children[i + 1]);
            if (rhs == nullptr) throw std::runtime_error(std::format("Expression element at index {} is not IEvaluable.", i + 1));

            lhs = op->Calculate(lhs, rhs->Evaluate(scope));
        }

        return lhs;
    }
}


