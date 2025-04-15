#include "Chunk.h"

namespace webwork {
    size_t Chunk::GetTextIndex(std::string_view text) const {
        return tokens.front().text.data() - text.data();
    }

    std::string_view Chunk::GetText() const {
        return GetText(0, tokens.size() - 1);
    }

    std::string_view Chunk::GetText(size_t from, size_t to) const {
        const auto start = tokens[from].text.data();
        const auto end = tokens[to].text;
        return std::string_view(start, end.data() - start + end.size());
    }
}