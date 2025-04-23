#include "Component.h"
#include "../../../ModuleConfig.h"

namespace webwork::thingamajig {
    Component::Component(size_t startIndex, std::string_view componentName, const std::vector<Value> &values) : Token(startIndex),
        component(GetCurrentModuleConfig()->components.GetComponent(componentName)), values(values) {}

    std::string Component::GetContent(const std::shared_ptr<const properties::Scope> &scope) const {
        const auto properties = std::make_shared<properties::Object>();
        for (const auto &[name, expression] : values) {
            properties->SetProperty(name, expression->Evaluate(scope));
        }
        return component->GetContent(scope, properties);
    }

}