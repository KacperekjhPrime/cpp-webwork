#ifndef BINARYOPERATORS_H
#define BINARYOPERATORS_H
#include "NumericBinaryOperator.h"
#include <cmath>

namespace webwork::expression {
    double Add(double lhs, double rhs);
    double Multiply(double lhs, double rhs);
    double Divide(double lhs, double rhs);

    using AdditionOperator = NumericBinaryOperator<Add, "+">;
    using MultiplicationOperator = NumericBinaryOperator<Multiply, "*">;
    using DivisionOperator = NumericBinaryOperator<Divide, "/">;
    using ModulusOperator = NumericBinaryOperator<std::fmod, "%">;
}

#endif //BINARYOPERATORS_H
