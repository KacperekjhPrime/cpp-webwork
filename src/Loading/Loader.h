#ifndef LOADER_H
#define LOADER_H
#include <filesystem>
#include <vector>

#include "Module.h"

#define STRINGIFY(x) #x
#define STRINGIFY_CONTENT(x) STRINGIFY(x)

#define MODULE_ENTRY OnModuleLoad
#define MODULE_ENTRY_NAME STRINGIFY_CONTENT(MODULE_ENTRY)

#ifdef WIN32
#define API_EXPORT extern "C" __declspec(dllexport)
#else
#define API_EXPORT extern "C"
#endif

namespace webwork {
    Module *LoadModule(const std::filesystem::path &path);
    std::vector<Module *> LoadModules();
}

#endif //LOADER_H