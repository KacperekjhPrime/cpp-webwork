#ifndef COMMA_H
#define COMMA_H
#include <memory>

#include "../Token.h"

namespace webwork::expression {
    class Comma final : public Token {
        static inline std::shared_ptr<Comma> instance;

    public:
        static const std::shared_ptr<Comma> &GetInstance();
    };
}

#endif //COMMA_H
