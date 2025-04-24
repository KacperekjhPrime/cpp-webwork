#include <cmath>
#include "IndexingOperator.h"

#include "../../Expression.h"
#include "../../../../Properties/Array.h"

namespace webwork::expression {
    IndexingOperator::IndexingOperator(std::string_view, const Chunk &chunk) : Block(ExpressionToken::RightSquareParenthesis, "indexing") {}

    void IndexingOperator::AddChild(const std::shared_ptr<Token> &child) {
        operations.AddElement(child);
    }

    void IndexingOperator::CloseBlock() {
        operations.CloseExpression();
    }

    std::shared_ptr<const Property> IndexingOperator::CalculatePostfix(const std::shared_ptr<const Property> &prop, const std::shared_ptr<const properties::Scope> &scope) const {
        const auto array = std::dynamic_pointer_cast<const properties::Array>(prop);
        if (!array) {
            Log(LogLevel::Warning, "Left side of unary index operator is not a number");
            return nullptr;
        }

        const auto interface = std::dynamic_pointer_cast<const properties::INumber>(operations.Evaluate(scope));
        if (!interface) {
            Log(LogLevel::Warning, "Index expression is not a number.");
            return nullptr;
        }

        const auto index = interface->GetNumberValue();
        const auto indexInt = std::floor(index);
        if (index < 0 || index >= array->value.size() || index != indexInt) {
            Log(LogLevel::Warning, "Index is out of range.");
            return nullptr;
        }

        return array->value[indexInt];
    }
}
