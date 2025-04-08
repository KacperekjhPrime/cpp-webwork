#include "If.h"

#include "../../Logging.h"
#include "../Properties/Interfaces/IBoolean.h"

namespace webwork::tokens {
    If::If(size_t startIndex, std::string_view condition) : Token(startIndex), Block(TokenType::EndIf, "if"), condition(condition) {}

    std::string If::GetContent(const std::shared_ptr<Scope> &scope) const {
        // TODO: Parse condition properly instead of treating it as a property name
        const auto boolean = std::dynamic_pointer_cast<const IBoolean>(scope->GetProperty(condition));
        if (boolean == nullptr) {
            Log(LogLevel::Warning, "Property {} does not implement IBoolean.", condition);
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
