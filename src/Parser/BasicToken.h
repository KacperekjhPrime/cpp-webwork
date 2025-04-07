#ifndef BASICTOKEN_H
#define BASICTOKEN_H

#include <string_view>

namespace webwork {
    enum class TokenType {
        Text,
        VariableOpening,
        VariableClosing,
        If,
        For,
        In,
        EndIf,
        EndFor,
        Comma,
        Escape,
        EndOfFile
    };

    struct BasicToken {
        TokenType type;
        std::string_view text;
    };
}

#endif //BASICTOKEN_H
