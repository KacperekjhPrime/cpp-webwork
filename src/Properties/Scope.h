#ifndef SCOPE_H
#define SCOPE_H
#include <memory>

#include "Object.h"
#include "../Logging.h"
#include "../Helper.h"

namespace webwork::properties {
    class Scope {
    public:
        std::shared_ptr<const Object> object;
        std::shared_ptr<const Scope> previous;

        explicit Scope(const std::shared_ptr<const Object> &object, const std::shared_ptr<const Scope> &previous = nullptr);

        std::shared_ptr<const Property> GetProperty(const std::string &name) const;

        template <class T>
        auto GetProperty(const std::string &name) const {
            const auto property = std::dynamic_pointer_cast<std::add_const_t<T>>(GetProperty(name));
            if (!property) {
                Log(LogLevel::Warning, "Property {} is not of required type: {}", name, GetTypeName<T>());
            }
            return property;
        }
    };
}

#endif //SCOPE_H
