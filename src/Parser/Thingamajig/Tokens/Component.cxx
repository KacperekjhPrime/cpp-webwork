#include "Component.h"

namespace webwork::thingamajig {
    Component::Component(size_t startIndex, std::string_view componentName, const std::vector<Value> &values) : Token(startIndex), componentName(componentName), values(values) {}

    std::string Component::GetContent(const std::shared_ptr<properties::Scope> &scope) const {
        // TODO: Render components
        const auto object = std::make_shared<properties::Object>();
        for (const auto &[name, expression] : values) {
            object->GetProperty(name) = expression->Evaluate(scope);
        }
        return std::format("Rendered {}.", componentName);
    }

}