#ifndef BINARYOPERATORS_H
#define BINARYOPERATORS_H
#include "NumericBinaryOperator.h"
#include "BoolBinaryOperator.h"
#include <cmath>

namespace webwork::expression {
    double Add(double lhs, double rhs);
    double Multiply(double lhs, double rhs);
    double Divide(double lhs, double rhs);

    bool LogicAnd(bool lhs, bool rhs);
    bool LogicOr(bool lhs, bool rhs);
    bool LogicXor(bool lhs, bool rhs);

    using AdditionOperator = NumericBinaryOperator<Add, "addition">;
    using MultiplicationOperator = NumericBinaryOperator<Multiply, "multiplication">;
    using DivisionOperator = NumericBinaryOperator<Divide, "division">;
    using ModulusOperator = NumericBinaryOperator<std::fmod, "remainder">;

    using LogicAndOperator = BoolBinaryOperator<LogicAnd, "logic and">;
    using LogicOrOperator = BoolBinaryOperator<LogicOr, "logic or">;
    using LogicXorOperator = BoolBinaryOperator<LogicXor, "logic xor">;
}

#endif //BINARYOPERATORS_H
