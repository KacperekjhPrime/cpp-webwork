#include "Components.h"
#include "Thingamajig.h"
#include "../../ModuleConfig.h"

namespace webwork::thingamajig {
    Components::Components(const ModuleConfig &config) : config(config) {}

    const std::shared_ptr<const ComponentData> &Components::GetComponent(const std::filesystem::path &path) const {
        const auto fullPath = weakly_canonical(absolute(config.componentDirectory / path));

        const auto it = components.find(fullPath);
        if (it != components.end()) {
            return it->second;
        }

        Log(LogLevel::Info, "Implicitly loading component: {}.", fullPath.string());

        const auto root = ParseThingamajig(ReadTextFile(fullPath));
        components.emplace(fullPath, std::make_shared<const ComponentData>(root, nullptr));
        return components[fullPath];
    }

    void Components::DefineComponent(const std::filesystem::path &path, const ComponentData::BeforeRender &beforeRender) {
        const auto fullPath = weakly_canonical(absolute(config.componentDirectory / path));
        Log(LogLevel::Info, "Explicitly loading component: {}.", fullPath.string());
        const auto root = ParseThingamajig(ReadTextFile(fullPath));
        components.emplace(fullPath, std::make_shared<const ComponentData>(root, beforeRender));
    }
}
