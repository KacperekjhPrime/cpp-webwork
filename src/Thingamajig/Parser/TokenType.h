#ifndef TOKENTYPE_H
#define TOKENTYPE_H

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
}

#endif //TOKENTYPE_H