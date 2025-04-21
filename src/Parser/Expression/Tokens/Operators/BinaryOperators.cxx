#include "BinaryOperators.h"

namespace webwork::expression::detail {
    double Add(double lhs, double rhs) {
        return lhs + rhs;
    }

    double Multiply(double lhs, double rhs) {
        return lhs * rhs;
    }

    double Divide(double lhs, double rhs) {
        return lhs / rhs;
    }

    bool LogicAnd(bool lhs, bool rhs) {
        return lhs && rhs;
    }

    bool LogicOr(bool lhs, bool rhs) {
        return lhs || rhs;
    }

    bool LogicXor(bool lhs, bool rhs) {
        return lhs ^ rhs;
    }

    bool GreaterThan(double lhs, double rhs) {
        return lhs > rhs;
    }

    bool LessThan(double lhs, double rhs) {
        return lhs < rhs;
    }

    bool GreaterOrEqualTo(double lhs, double rhs) {
        return lhs >= rhs;
    }

    bool LessOrEqualTo(double lhs, double rhs) {
        return lhs <= rhs;
    }

    bool EqualTo(double lhs, double rhs) {
        return lhs == rhs;
    }

    bool NotEqualTo(double lhs, double rhs) {
        return lhs != rhs;
    }
}