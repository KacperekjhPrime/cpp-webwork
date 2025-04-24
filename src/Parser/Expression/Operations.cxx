#include "Operations.h"

#include "Tokens/Operators/Noop.h"

namespace webwork::expression {
    Operations::Operations() : operations({Operation{.binaryOperator = Noop::GetInstance()}}) {}

    std::shared_ptr<const Property> Operations::Evaluate(const std::shared_ptr<const properties::Scope> &scope) const {
        std::shared_ptr<const Property> lhs = nullptr;

        for (const auto &operation : operations) {
            auto rhs = operation.expression->Evaluate(scope);
            for (const auto &prefix : operation.prefixOperators) {
                rhs = prefix->CalculatePrefix(rhs, scope);
            }
            for (const auto &postfix : operation.postfixOperators) {
                rhs = postfix->CalculatePostfix(rhs, scope);
            }
            lhs = operation.binaryOperator->Calculate(lhs, rhs, scope);
        }

        return lhs;
    }

    void Operations::AddElement(const std::shared_ptr<Token> &child) {
        auto &last = operations.back();

        if (last.expression) {
            auto postfix = std::dynamic_pointer_cast<const IPostfixUnaryOperator>(child);
            if (postfix) {
                last.postfixOperators.emplace_back(postfix);
                return;
            }

            operations.emplace_back();
            AddElement(child);
        } else if (last.binaryOperator) {
            auto prefix = std::dynamic_pointer_cast<const IPrefixUnaryOperator>(child);
            if (prefix) {
                last.prefixOperators.emplace_back(std::move(prefix));
                return;
            }

            last.expression = std::dynamic_pointer_cast<const IEvaluable>(child);
            if (last.expression) return;

            throw std::runtime_error("Invalid expression token. Expected IPrefixUnaryOperator or IEvaluable.");
        } else {
            last.binaryOperator = std::dynamic_pointer_cast<const IBinaryOperator>(child);
            if (last.binaryOperator) return;

            throw std::runtime_error("Invalid expression token. Expected IBinaryOperator.");
        }
    }

    void Operations::CloseExpression() const {
        if (!operations.back().expression) {
            throw std::runtime_error("Missing IEvaluable at the end of the expression.");
        }
    }
}
