#ifndef BASICTOKEN_H
#define BASICTOKEN_H

#include <string_view>

namespace webwork {
    template <class T>
    struct BasicToken {
        T type;
        std::string_view text;
    };
}

#endif //BASICTOKEN_H
