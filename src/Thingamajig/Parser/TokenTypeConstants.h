#ifndef TOKENTYPECONSTATNTS_H
#define TOKENTYPECONSTATNTS_H

namespace webwork {
    using TokenT = unsigned int;

    constexpr TokenT TokenText = 0;
    constexpr TokenT TokenEscape = 1;

    constexpr TokenT TokensStart = 2;

    constexpr TokenT TokenAllowStrayBit = 1<<16;

    constexpr TokenT TokenEmpty = -1u;
}

#endif //TOKENTYPECONSTATNTS_H