#ifndef CHUNK_H
#define CHUNK_H
#include <span>

#include "BasicToken.h"

namespace webwork {
    struct Chunk {
        std::span<const BasicToken> tokens;
        TokenT type;

        /**
         * Calculates an index to the first character of the first token
         * @param text Text that the tokens were created from
         * @return index in <c>text</c>
         */
        size_t GetTextIndex(std::string_view text) const;

        /**
         * Concatenates text of all tokens
         * @return concatenated tokens
         */
        std::string_view GetText() const;
    };
}

#endif //CHUNK_H