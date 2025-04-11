#include "Chunk.h"

namespace webwork {
    size_t Chunk::GetTextIndex(std::string_view text) const {
        return tokens.front().text.data() - text.data();
    }

    std::string_view Chunk::GetText() const {
        const auto start = tokens.front().text.data();
        const auto end = tokens.back().text;
        return std::string_view(start, end.data() - start + end.size());
    }
}