#include "BinaryOperators.h"

namespace webwork::expression {
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
}