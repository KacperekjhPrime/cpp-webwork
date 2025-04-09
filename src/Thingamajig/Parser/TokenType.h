#ifndef TOKENTYPE_H
#define TOKENTYPE_H
#include "TokenTypeConstants.h"

namespace webwork {
    enum class TokenType : unsigned int {
        Text = TokenText,
        Escape = TokenEscape,

        VariableOpening = TokensStart,
        VariableClosing,
        If,
        For,
        EndIf,
        EndFor,
        Comma,
        EndOfFile,

        In = TokenAllowStrayBit + 1
    };
}

#endif //TOKENTYPE_H