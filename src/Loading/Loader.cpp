#include "Loader.h"

#include "../Logging.h"
#include "../Mime.h"

namespace webwork {
#ifdef linux
#include <dlfcn.h>
    constexpr std::string_view moduleMime = "application/x-sharedlib";
#elifdef WIN32
#include <libloaderapi.h>
#include <errhandlingapi.h>
    constexpr std::string_view moduleMime = "application/vnd.microsoft.portable-executable";
#else
#error Unsupported platform. Currently supported platforms are Windows and Linux.
#endif

#ifdef linux
    void *OpenSharedObject(const std::filesystem::path &path) {
        return dlopen(path.c_str(), RTLD_LAZY);
    }

    void *GetObjectAddress(void *handle, std::string_view name) {
        return dlsym(handle, name.data());
    }

    const char *GetError() {
        return dlerror();
    }
#elifdef WIN32
    HMODULE OpenSharedObject(const std::filesystem::path &path) {
        return LoadLibraryA(path.generic_string().c_str());
    }

    FARPROC GetObjectAddress(HMODULE handle, std::string_view name) {
        return GetProcAddress(handle, name.data());
    }

    std::string GetError() {
        return std::system_category().message(static_cast<int>(GetLastError()));
    }
#endif

    Module *LoadModule(const std::filesystem::path &path) {
        Log(LogLevel::Info, "Loading module {}.", path.string());

        const auto handle = OpenSharedObject(path);
        if (!handle) {
            Log(LogLevel::Error, "Failed to load module '{}': {}", path.string(), GetError());
            return nullptr;
        }

        const auto load = reinterpret_cast<Module *(*)()>(GetObjectAddress(handle, MODULE_ENTRY_NAME));
        if (!load) {
            Log(LogLevel::Error, "{} does not have a valid module entry point: {}", path.string(), GetError());
            return nullptr;
        }

        return load();
    }

    std::vector<Module *> LoadModules(){
        const auto moduleDirectory = std::filesystem::current_path() / "Modules";
        std::vector<Module *> modules;

        if (!is_directory(moduleDirectory)) {
            Log(LogLevel::Warning, "{} is not a directory.", moduleDirectory.string());
            return modules;
        }

        for (const auto &entry : std::filesystem::directory_iterator(moduleDirectory)) {
            if (!entry.is_regular_file()) continue;

            const auto &path = entry.path();
            if (GetFileMime(path) != moduleMime) continue;
            if (auto module = LoadModule(path)) {
                modules.push_back(module);
            }
        }

        return modules;
    }
}
