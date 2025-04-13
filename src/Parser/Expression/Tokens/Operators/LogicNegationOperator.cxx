#include "LogicNegationOperator.h"
#include "../../../Thingamajig/Properties/Boolean.h"

namespace webwork::expression {
    std::shared_ptr<const Property> LogicNegationOperator::Calculate(const std::shared_ptr<const Property> &prop) const {
        const auto boolean = std::dynamic_pointer_cast<const properties::IBoolean>(prop);
        if (boolean == nullptr) {
            Log(LogLevel::Warning, "Operand of unary not operator is not required type {}.", GetTypeName<properties::IBoolean>());
            return nullptr;
        }
        return std::make_shared<properties::Boolean>(!boolean->GetBoolValue());
    }

    const std::shared_ptr<LogicNegationOperator> &LogicNegationOperator::GetInstance() {
        if (!instance) {
            instance = std::make_shared<LogicNegationOperator>();
        }
        return instance;
    }
}