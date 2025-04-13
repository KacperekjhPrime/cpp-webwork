#ifndef NUMERICOPERATOR_H
#define NUMERICOPERATOR_H

#include "../../Token.h"
#include "../Interfaces/IBinaryOperator.h"
#include "../../../Thingamajig/Properties/Number.h"
#include "../../../../Helper.h"
#include "../../../../Logging.h"

namespace webwork::expression {
    template <double(*Op)(double lhs, double rhs), ConstString Name>
    class NumericBinaryOperator final : public Token, public IBinaryOperator {
        static inline std::shared_ptr<NumericBinaryOperator> instance;

    public:
        std::shared_ptr<const Property> Calculate(const std::shared_ptr<const Property> &a, const std::shared_ptr<const Property> &b) const override {
            return CalculateImpl(a, b);
        }

        static std::shared_ptr<const Property> CalculateImpl(const std::shared_ptr<const Property> &a, const std::shared_ptr<const Property> &b) {
            const auto left = std::dynamic_pointer_cast<const properties::INumber>(a);
            if (left == nullptr) {
                Log(LogLevel::Warning, "Left side of binary {} operator is not required type {}.", Name.data, GetTypeName<properties::INumber>());
                return nullptr;
            }
            const auto right = std::dynamic_pointer_cast<const properties::INumber>(b);
            if (right == nullptr) {
                Log(LogLevel::Warning, "Right side of binary {} operator is not required type {}.", Name.data, GetTypeName<properties::INumber>());
                return nullptr;
            }

            return std::make_shared<properties::Number>(Op(left->GetNumberValue(), right->GetNumberValue()));
        }

        static const std::shared_ptr<NumericBinaryOperator> &GetInstance() {
            if (!instance) {
                instance = std::make_shared<NumericBinaryOperator>();
            }
            return instance;
        }
    };
}

#endif //NUMERICOPERATOR_H
