#ifndef NUMERICOPERATOR_H
#define NUMERICOPERATOR_H

#include "../../Token.h"
#include "../Interfaces/IBinaryOperator.h"
#include "../../../Thingamajig/Properties/Number.h"
#include "../../../../Helper.h"
#include "../../../../Logging.h"

namespace webwork::expression {
    template <double(*Op)(double lhs, double rhs), ConstString Name>
    class NumericBinaryOperator : public Token, public IBinaryOperator {
    public:
        std::shared_ptr<const Property> Calculate(const std::shared_ptr<const Property> &a, const std::shared_ptr<const Property> &b) const override {
            const auto left = std::dynamic_pointer_cast<const properties::Number>(a);
            if (left == nullptr) {
                Log(LogLevel::Warning, "Left side of binary {} operator is not required type {}.", Name.data, GetTypeName<properties::Number>());
                return nullptr;
            }
            const auto right = std::dynamic_pointer_cast<const properties::Number>(b);
            if (right == nullptr) {
                Log(LogLevel::Warning, "Right side of binary {} operator is not required type {}.", Name.data, GetTypeName<properties::Number>());
                return nullptr;
            }

            return std::make_shared<properties::Number>(Calculate(left->data, right->data));
        }

        static double Calculate(double lhs, double rhs) {
            return Op(lhs, rhs);
        }
    };
}

#endif //NUMERICOPERATOR_H
