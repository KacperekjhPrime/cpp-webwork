#ifndef TOKEN_H
#define TOKEN_H
#include <string>

#include "Scope.h"

namespace webwork {
    class Token {
    protected:
        explicit Token(size_t startIndex);

    public:
        const size_t startIndex;

        virtual ~Token() = default;

        /**
         * Generates and returns content of this Token
         */
        virtual std::string GetContent(const std::shared_ptr<Scope> &scope) const = 0;
    };
}

#endif //TOKEN_H
