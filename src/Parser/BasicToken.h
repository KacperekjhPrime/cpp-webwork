#ifndef BASICTOKEN_H
#define BASICTOKEN_H

#include <string_view>

#include "TokenTypeConstants.h"

namespace webwork {
    struct BasicToken {
        TokenT type;
        std::string_view text;
    };
}

#endif //BASICTOKEN_H
