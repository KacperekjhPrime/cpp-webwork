#include "SubtractionOperator.h"

namespace webwork::expression {
    double Subtract(double lhs, double rhs) {
        return lhs - rhs;
    }

    std::shared_ptr<const Property> SubtractionOperator::Calculate(const std::shared_ptr<const Property> &prop) const {
        const auto number = std::dynamic_pointer_cast<const properties::Number>(prop);
        if (number == nullptr) {
            Log(LogLevel::Warning, "Operant of unary - operator is not required type {}.", GetTypeName<properties::Number>());
            return nullptr;
        }
        return std::make_shared<properties::Number>(-number->data);
    }
}