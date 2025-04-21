#include "ModuleConfig.h"

namespace webwork {
    ModuleConfig::ModuleConfig(const std::filesystem::path &componentDirectory) : componentDirectory(componentDirectory), components(*this) {};

    std::shared_ptr<const ModuleConfig> currentConfig;

    const std::shared_ptr<const ModuleConfig> &GetCurrentModuleConfig() {
        return currentConfig;
    }

    void SetCurrentModuleConfig(const std::shared_ptr<const ModuleConfig> &config) {
        currentConfig = config;
    }
}