#ifndef VARIABLE_H
#define VARIABLE_H

#include "../Token.h"

namespace webwork::tokens {
    class Variable final : public Token {
    public:
        std::string variableName;

        Variable(size_t startIndex, std::string_view variableName);

        std::string GetContent(const std::shared_ptr<Scope> &scope) const override;
    };
}

#endif //VARIABLE_H
