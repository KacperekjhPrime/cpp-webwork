#ifndef TOKENTYPECONSTATNTS_H
#define TOKENTYPECONSTATNTS_H

namespace webwork {
    using TokenT = unsigned;

    constexpr TokenT TokenStrayToTextBit = 1<<16;
    constexpr TokenT TokenInescapableBit = 1<<17;

    constexpr TokenT TokenText = TokenStrayToTextBit | TokenInescapableBit;
    constexpr TokenT TokenEscape = 1;

    constexpr TokenT TokensStart = 2;

    constexpr TokenT TokenEmpty = -1u;
}

#endif //TOKENTYPECONSTATNTS_H