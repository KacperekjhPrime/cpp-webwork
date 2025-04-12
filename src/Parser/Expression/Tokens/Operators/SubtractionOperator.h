#ifndef SUBTRACTIONOPERATOR_H
#define SUBTRACTIONOPERATOR_H
#include "NumericBinaryOperator.h"
#include "../Interfaces/IUnaryOperator.h"

namespace webwork::expression {
    double Subtract(double lhs, double rhs);

    class SubtractionOperator final : public NumericBinaryOperator<Subtract, "-">, public IUnaryOperator {
    public:
        std::shared_ptr<const Property> Calculate(const std::shared_ptr<const Property> &prop) const override;
    };
}

#endif //SUBTRACTIONOPERATOR_H
