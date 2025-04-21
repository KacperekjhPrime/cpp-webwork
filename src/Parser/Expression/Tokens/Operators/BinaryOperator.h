#ifndef BINARYOPERATOR_H
#define BINARYOPERATOR_H
#include "../../Token.h"
#include "../../../../Helper.h"
#include "../../../../Logging.h"
#include "../../../../Properties/Helper.h"
#include "../Interfaces/IBinaryOperator.h"

namespace webwork::expression {
    template <class R, class A, class B, R(*Op)(A lhs, B rhs), ConstString Name>
    class BinaryOperator final : public Token, public IBinaryOperator {
        static inline std::shared_ptr<BinaryOperator> instance;

    public:
        std::shared_ptr<const Property> Calculate(const std::shared_ptr<const Property> &a, const std::shared_ptr<const Property> &b) const override {
            using InterfaceA = properties::PropertyInterfaceT<A>;
            using InterfaceB = properties::PropertyInterfaceT<B>;

            const auto interfaceA = std::dynamic_pointer_cast<const InterfaceA>(a);
            if (!interfaceA) {
                Log(LogLevel::Warning, "Left side of binary {} operator is not of required type {}.", std::string_view(Name), GetTypeName<InterfaceA>());
                return nullptr;
            }

            const auto interfaceB = std::dynamic_pointer_cast<const InterfaceB>(b);
            if (!interfaceB) {
                Log(LogLevel::Warning, "Right side of binary {} operator is not of required type {}.", std::string_view(Name), GetTypeName<InterfaceB>());
                return nullptr;
            }

            const auto lhs = static_cast<A>(InterfaceA::GetValue(*interfaceA));
            const auto rhs = static_cast<B>(InterfaceB::GetValue(*interfaceB));

            return properties::CreateProperty(Op(lhs, rhs));
        }

        static const std::shared_ptr<BinaryOperator> &GetInstance() {
            if (!instance) {
                instance = std::make_shared<BinaryOperator>();
            }
            return instance;
        }
    };
}

#endif //BINARYOPERATOR_H