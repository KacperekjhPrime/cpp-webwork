#include "If.h"

#include <cassert>

#include "../Thingamajig.h"
#include "../Properties/Interfaces/IBoolean.h"
#include "../../../Logging.h"

namespace webwork::tokens {
    If::If(std::string_view text, const Chunk &chunk) : Token(chunk.GetTextIndex(text)), Block(thingamajig::TokenType::TokenType::EndIf, "if"), condition(chunk.tokens[1].text) {
        assert(chunk.tokens.size() == 3);
    }

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
