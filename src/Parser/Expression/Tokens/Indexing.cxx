#include <cmath>
#include "Indexing.h"

#include "../Expression.h"
#include "../../../Properties/Array.h"

namespace webwork::expression {
    Indexing::Indexing(std::string_view, const Chunk &chunk) : Block(ExpressionToken::RightSquareParenthesis, "indexing"), arrayName(chunk.tokens[0].text) {}

    void Indexing::AddChild(const std::shared_ptr<Token> &child) {
        if (indexExpression) {
            throw std::runtime_error("Cannot add more than one index expression.");
        }
        const auto evaluable = std::dynamic_pointer_cast<const IEvaluable>(child);
        if (!evaluable) {
            throw std::runtime_error("Index expression is not IEvaluable.");
        }
        indexExpression = evaluable;
    }

    void Indexing::CloseBlock() {
        if (!indexExpression) {
            throw std::runtime_error("Missing index expression.");
        }
    }

    std::shared_ptr<const Property> Indexing::Evaluate(const std::shared_ptr<const properties::Scope> &scope) const {
        const auto array = scope->GetProperty<properties::Array>(arrayName);
        if (!array) {
            return nullptr;
        }

        const auto interface = std::dynamic_pointer_cast<const properties::INumber>(indexExpression->Evaluate(scope));
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
