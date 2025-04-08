#include "If.h"

namespace webwork::tokens {
    If::If(size_t startIndex, std::string_view condition) : Token(startIndex), Block(TokenType::EndIf, "if"), condition(condition) {}

    std::string If::GetContent() const {
        // TODO: Display conditional variables here
        std::string text = std::format("[if {}]", condition);
        for (const auto &child : children) {
            text += child->GetContent();
        }
        text += "[end if]";
        return text;
    }
}