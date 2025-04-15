#include "Function.h"

#include "Comma.h"
#include "../Expression.h"
#include "../../Thingamajig/Properties/Interfaces/IFunction.h"

namespace webwork::expression {
    Function::Function(std::string_view, const Chunk &chunk) : Block(ExpressionToken::RightParenthesis, "function parameters"),
        functionName(TrimSpaces(chunk.tokens[0].text)) {}


    void Function::AddChild(const std::shared_ptr<Token> &child) {
        if (expectsComma) {
            const auto comma = std::dynamic_pointer_cast<Comma>(child);
            if (!comma) throw std::runtime_error("Invalid function parameter token. Comma expected.");
            expectsComma = false;
        } else {
            const auto expression = std::dynamic_pointer_cast<IEvaluable>(child);
            if (!expression) throw std::runtime_error("Invalid function parameter token. IEvaluable expected.");
            params.push_back(expression);
            expectsComma = true;
        }
    }

    std::shared_ptr<const Property> Function::Evaluate(const std::shared_ptr<const Scope> &scope) const {
        const auto function = scope->GetProperty<properties::IFunction>(functionName);
        if (!function) {
            return nullptr;
        }

        std::vector<std::shared_ptr<const Property>> properties;
        properties.reserve(params.size());

        for (const auto &param : params) {
            properties.push_back(param->Evaluate(scope));
        }

        return function->Execute(properties);
    }
}
