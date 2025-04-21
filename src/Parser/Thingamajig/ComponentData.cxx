#include "ComponentData.h"

namespace webwork::thingamajig {
    ComponentData::ComponentData(const std::shared_ptr<const Root> &root, const BeforeRender &beforeRender) : root(root), beforeRender(beforeRender) {}

    std::string ComponentData::GetContent(const std::shared_ptr<const properties::Scope> &scope, const std::shared_ptr<properties::Object> &properties) const {
        const auto newScope = std::make_shared<properties::Scope>(properties, scope);
        if (beforeRender) {
            beforeRender(newScope);
        }
        return root->GetContent(newScope);
    }
}