#include "Expression.h"

namespace webwork::thingamajig {
    Expression::Expression(size_t textIndex, const std::shared_ptr<const expression::Parenthesis> &expression) : Token(textIndex), expression(expression) {}

    std::string Expression::GetContent(const std::shared_ptr<Scope> &scope) const {
        if (expression == nullptr) return "";

        const auto result = expression->Evaluate(scope);
        if (result == nullptr) return "";

        return result->ToString();
    }
}