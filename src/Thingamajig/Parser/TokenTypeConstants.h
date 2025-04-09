#ifndef TOKENTYPECONSTATNTS_H
#define TOKENTYPECONSTATNTS_H

#include <type_traits>

namespace webwork {
    template <class T>
    concept TokenT = std::is_same_v<std::underlying_type_t<T>, unsigned int>;

    constexpr unsigned int TokenText = 0;
    constexpr unsigned int TokenEscape = 1;

    constexpr unsigned int TokensStart = 2;

    constexpr unsigned int TokenAllowStrayBit = 1<<16;
}

#endif //TOKENTYPECONSTATNTS_H