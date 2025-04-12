#include "If.h"

#include "../Thingamajig.h"
#include "../Properties/Interfaces/IBoolean.h"
#include "../../../Logging.h"

namespace webwork::thingamajig {
    If::If(size_t textIndex, const std::shared_ptr<expression::Parenthesis> &expression) : Token(textIndex), BlockBase(TokenType::EndIf, "if"), expression(expression) {}

    std::string If::GetContent(const std::shared_ptr<Scope> &scope) const {
        // TODO: Parse condition properly instead of treating it as a property name
        const auto result = expression->Evaluate(scope);
        const auto boolean = std::dynamic_pointer_cast<const properties::IBoolean>(result);
        if (!boolean) {
            Log(LogLevel::Warning, "Expression at {} does not evaluate into IBoolean.", startIndex);
            return "";
        }

        if (boolean->GetBoolValue()) {
            std::string text = "";
            for (const auto &child : children) {
                text += child->GetContent(scope);
            }
            return text;
        }
        return "";
    }
}
