#include "Text.h"

namespace webwork {
    Text::Text(size_t startIndex, std::string_view text) : Token(startIndex), text(text) {}

    std::string Text::GetContent() const {
        return std::string(text);
    }
}