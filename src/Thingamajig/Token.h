#ifndef TOKEN_H
#define TOKEN_H
#include <string>

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
        virtual std::string GetContent() const = 0;
    };
}

#endif //TOKEN_H
