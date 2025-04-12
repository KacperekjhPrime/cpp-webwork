#include "SubtractionOperator.h"

namespace webwork::expression {
    double Subtract(double lhs, double rhs) {
        return lhs - rhs;
    }

    std::shared_ptr<const Property> SubtractionOperator::Calculate(const std::shared_ptr<const Property> &prop) const {
        const auto number = std::dynamic_pointer_cast<const properties::INumber>(prop);
        if (number == nullptr) {
            Log(LogLevel::Warning, "Operand of unary negation operator is not required type {}.", GetTypeName<properties::INumber>());
            return nullptr;
        }
        return std::make_shared<properties::Number>(-number->GetNumberValue());
    }
}