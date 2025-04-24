#include "Function.h"

#include "Comma.h"
#include "../Expression.h"
#include "../../../Properties/Interfaces/IFunction.h"

namespace webwork::expression {
    Function::Function(std::string_view, const Chunk &chunk) : Block(ExpressionToken::RightParenthesis, "function parameters"),
        functionName(TrimSpaces(chunk.tokens[0].text)) {}


    void Function::AddChild(const std::shared_ptr<Token> &child) {
        const auto comma = std::dynamic_pointer_cast<const Comma>(child);
        if (comma) {
            params.back().CloseExpression();
            params.emplace_back();
        } else {
            if (params.size() == 0) params.emplace_back();
            params.back().AddElement(child);
        }
    }

    void Function::CloseBlock() {
        params.back().CloseExpression();
    }

    std::shared_ptr<const Property> Function::Evaluate(const std::shared_ptr<const properties::Scope> &scope) const {
        const auto function = scope->GetProperty<properties::IFunction>(functionName);
        if (!function) {
            return nullptr;
        }

        std::vector<std::shared_ptr<const Property>> properties;
        properties.reserve(params.size());

        for (const auto &param : params) {
            properties.push_back(param.Evaluate(scope));
        }

        return function->Execute(properties);
    }
}
