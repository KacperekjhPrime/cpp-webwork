#ifndef VARIABLE_H
#define VARIABLE_H

#include "../Token.h"

namespace webwork::tokens {
    class Variable final : public Token {
    public:
        std::string_view variableName;

        Variable(size_t startIndex, std::string_view variableName);

        std::string GetContent() const override;
    };
}

#endif //VARIABLE_H
