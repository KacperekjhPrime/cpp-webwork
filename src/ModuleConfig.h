#ifndef MODULECONFIG_H
#define MODULECONFIG_H
#include <filesystem>

#include "Parser/Thingamajig/Components.h"

namespace webwork {
    struct ModuleConfig {
        const std::filesystem::path componentDirectory;
        thingamajig::Components components;

        explicit ModuleConfig(const std::filesystem::path &componentDirectory);
    };

    const std::shared_ptr<const ModuleConfig> &GetCurrentModuleConfig();
    void SetCurrentModuleConfig(const std::shared_ptr<const ModuleConfig> &config);
}

#endif //MODULECONFIG_H
