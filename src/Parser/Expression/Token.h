#ifndef EXPRESSION_TOKEN_H
#define EXPRESSION_TOKEN_H
#include <memory>

#include "../Thingamajig/Property.h"
#include "../Thingamajig/Scope.h"

namespace webwork::expression {
    class Token {
    public:
        virtual ~Token() = default;
    };
}

#endif //TOKEN_H
