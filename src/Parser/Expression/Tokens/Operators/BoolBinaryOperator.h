#ifndef BOOLEANOPERATOR_H
#define BOOLEANOPERATOR_H

#include "../../Token.h"
#include "../Interfaces/IBinaryOperator.h"
#include "../../../Thingamajig/Properties/Boolean.h"
#include "../../../../Helper.h"
#include "../../../../Logging.h"

namespace webwork::expression {
    template <bool(*Op)(bool lhs, bool rhs), ConstString Name>
    class BoolBinaryOperator : public Token, public IBinaryOperator {
    public:
        std::shared_ptr<const Property> Calculate(const std::shared_ptr<const Property> &a, const std::shared_ptr<const Property> &b) const override {
            const auto left = std::dynamic_pointer_cast<const properties::IBoolean>(a);
            if (left == nullptr) {
                Log(LogLevel::Warning, "Left side of binary {} operator is not required type {}.", Name.data, GetTypeName<properties::IBoolean>());
                return nullptr;
            }
            const auto right = std::dynamic_pointer_cast<const properties::IBoolean>(b);
            if (right == nullptr) {
                Log(LogLevel::Warning, "Right side of binary {} operator is not required type {}.", Name.data, GetTypeName<properties::IBoolean>());
                return nullptr;
            }

            return std::make_shared<properties::Boolean>(Op(left->GetBoolValue(), right->GetBoolValue()));
        }
    };
}

#endif //NUMERICOPERATOR_H
