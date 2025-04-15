#include "Text.h"

#include "../../Parser.h"

namespace webwork::thingamajig {
    Text::Text(std::string_view text, const Chunk &chunk) : Token(chunk.GetTextIndex(text)), text(chunk.GetText()) {}

    std::string Text::GetContent(const std::shared_ptr<properties::Scope> &) const {
        return std::string(text);
    }
}
