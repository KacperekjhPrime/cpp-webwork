#ifndef BINARYOPERATORS_H
#define BINARYOPERATORS_H
#include <cmath>

#include "BinaryOperator.h"

namespace webwork::expression {
    namespace detail {
        double Add(double lhs, double rhs);
        double Multiply(double lhs, double rhs);
        double Divide(double lhs, double rhs);

        bool LogicAnd(bool lhs, bool rhs);
        bool LogicOr(bool lhs, bool rhs);
        bool LogicXor(bool lhs, bool rhs);

        bool GreaterThan(double lhs, double rhs);
        bool LessThan(double lhs, double rhs);
        bool GreaterOrEqualTo(double lhs, double rhs);
        bool LessOrEqualTo(double lhs, double rhs);
        bool EqualTo(double lhs, double rhs);
        bool NotEqualTo(double lhs, double rhs);
    }

    template <double(*Op)(double, double), ConstString Name>
    using NumericBinaryOperator = BinaryOperator<double, double, double, Op, Name>;

    template <bool(*Op)(bool, bool), ConstString Name>
    using BoolBinaryOperator = BinaryOperator<bool, bool, bool, Op, Name>;

    template <bool(*Op)(double, double), ConstString Name>
    using NumericComparisonOperator = BinaryOperator<bool, double, double, Op, Name>;

    using AdditionOperator = NumericBinaryOperator<detail::Add, "addition">;
    using MultiplicationOperator = NumericBinaryOperator<detail::Multiply, "multiplication">;
    using DivisionOperator = NumericBinaryOperator<detail::Divide, "division">;
    using ModulusOperator = NumericBinaryOperator<std::fmod, "remainder">;

    using LogicAndOperator = BoolBinaryOperator<detail::LogicAnd, "logic and">;
    using LogicOrOperator = BoolBinaryOperator<detail::LogicOr, "logic or">;
    using LogicXorOperator = BoolBinaryOperator<detail::LogicXor, "logic xor">;

    using GreaterThanOperator = NumericComparisonOperator<detail::GreaterThan, "greater than">;
    using LessThanOperator = NumericComparisonOperator<detail::LessThan, "less than">;
    using GreaterOrEqualToOperator = NumericComparisonOperator<detail::GreaterOrEqualTo, "greater or equal to">;
    using LessOrEqualToOperator = NumericComparisonOperator<detail::LessOrEqualTo, "less or equal to">;
    using EqualToOperator = NumericComparisonOperator<detail::EqualTo, "equal to">;
    using NotEqualToOperator = NumericComparisonOperator<detail::NotEqualTo, "not equal to">;
}

#endif //BINARYOPERATORS_H
