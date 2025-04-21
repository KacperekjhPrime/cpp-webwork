#ifndef COMPONENTDATA_H
#define COMPONENTDATA_H
#include <functional>

#include "Tokens/Root.h"
#include "../../Properties/Scope.h"

namespace webwork::thingamajig {
    class ComponentData {
    public:
        template <class ...Ts>
        using BeforeRenderParametrized = std::function<void(const std::shared_ptr<properties::Scope> &scope, Ts ...params)>;
        using BeforeRender = std::function<void(const std::shared_ptr<properties::Scope> &scope)>;

        std::shared_ptr<const Root> root;
        BeforeRender beforeRender;

        ComponentData(const std::shared_ptr<const Root> &root, const BeforeRender &beforeRender);

        std::string GetContent(const std::shared_ptr<const properties::Scope> &scope, const std::shared_ptr<properties::Object> &properties) const;
    };
}

#endif //COMPONENTDATA_H
