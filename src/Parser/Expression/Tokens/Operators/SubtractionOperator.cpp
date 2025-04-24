#include "SubtractionOperator.h"
#include "../../../../Properties/Number.h"
#include "../../../../Helper.h"
#include "../../../../Logging.h"

namespace webwork::expression {
    std::shared_ptr<const Property> SubtractionOperator::CalculatePrefix(const std::shared_ptr<const Property> &prop, const std::shared_ptr<const properties::Scope> &) const {
        const auto number = std::dynamic_pointer_cast<const properties::INumber>(prop);
        if (number == nullptr) {
            Log(LogLevel::Warning, "Operand of unary negation operator is not required type {}.", GetTypeName<properties::INumber>());
            return nullptr;
        }
        return std::make_shared<properties::Number>(-number->GetNumberValue());
    }

    std::shared_ptr<const Property> SubtractionOperator::Calculate(const std::shared_ptr<const Property> &a, const std::shared_ptr<const Property> &b, const std::shared_ptr<const properties::Scope> &) const {
        const auto interfaceA = std::dynamic_pointer_cast<const properties::INumber>(a);
        if (!interfaceA) {
            Log(LogLevel::Warning, "Left side of binary subtraction operator is not of required type INumber.");
            return nullptr;
        }

        const auto interfaceB = std::dynamic_pointer_cast<const properties::INumber>(b);
        if (!interfaceB) {
            Log(LogLevel::Warning, "Right side of binary subtraction operator is not of required type INumber.");
            return nullptr;
        }

        return std::make_shared<properties::Number>(interfaceA->GetNumberValue() - interfaceB->GetNumberValue());
    }

    std::shared_ptr<SubtractionOperator> SubtractionOperator::GetInstance() {
        if (!instance) {
            instance = std::make_shared<SubtractionOperator>();
        }
        return instance;
    }
}