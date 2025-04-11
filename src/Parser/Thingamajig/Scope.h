#ifndef SCOPE_H
#define SCOPE_H
#include <memory>
#include <cxxabi.h>

#include "Properties/Object.h"
#include "../../Logging.h"

namespace webwork {
    class Scope {
    public:
        std::shared_ptr<const properties::Object> object;
        std::shared_ptr<const Scope> previous;

        explicit Scope(const std::shared_ptr<const properties::Object> &object, const std::shared_ptr<const Scope> &previous = nullptr);

        std::shared_ptr<const Property> GetProperty(const std::string &name) const;

        template <class T>
        auto GetProperty(const std::string &name) const {
            const auto property = std::dynamic_pointer_cast<std::add_const_t<T>>(GetProperty(name));
            if (!property) {
                int status = 0;
                const auto mangled = typeid(T).name();
                const auto demangled = abi::__cxa_demangle(mangled, nullptr, nullptr, &status);
                Log(LogLevel::Warning, "Property {} is not of required type: {}", name, status == 0 ? demangled : mangled);
                std::free(demangled);
            }
            return property;
        }
    };
}

#endif //SCOPE_H
