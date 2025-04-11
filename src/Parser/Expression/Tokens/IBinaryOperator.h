#ifndef BINARYOPERATOR_H
#define BINARYOPERATOR_H
#include "../Token.h"

namespace webwork::expression {
    class IBinaryOperator : public Token {
    public:
        virtual std::shared_ptr<const Property> Calculate(const std::shared_ptr<const Property> &a, const std::shared_ptr<const Property> &b) = 0;
    };
}

#endif //BINARYOPERATOR_H
