#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <filesystem>

#include "ComponentData.h"
#include "../../Properties/Helper.h"

namespace webwork {
    struct ModuleConfig;
}

namespace webwork::thingamajig {
    namespace detail {
        template <class T>
        auto GetPropertyValue(const std::shared_ptr<properties::Scope> &scope, const std::string &key) {
            using Interface = properties::PropertyInterfaceT<T>;
            return Interface::GetValue(*scope->GetProperty<Interface>(key));
        }
    }

    class Components {
        const ModuleConfig &config;
        mutable std::map<std::filesystem::path, std::shared_ptr<const ComponentData>> components;

    public:
        explicit Components(const ModuleConfig &config);

        const std::shared_ptr<const ComponentData> &GetComponent(const std::filesystem::path &path) const;

        void DefineComponent(const std::filesystem::path &path, const ComponentData::BeforeRender &beforeRender);
    };
}

#endif //COMPONENTS_H
