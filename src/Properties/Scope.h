#ifndef SCOPE_H
#define SCOPE_H
#include <memory>

#include "Object.h"
#include "../Logging.h"
#include "../Helper.h"

namespace webwork::properties {
    class Scope {
        std::shared_ptr<Object> object;
        std::shared_ptr<const Scope> previous;

    public:
        explicit Scope(const std::shared_ptr<Object> &object, const std::shared_ptr<const Scope> &previous = nullptr);

        template <class T = Property>
        std::shared_ptr<std::add_const_t<T>> GetProperty(const std::string &name) const {
            if (object) {
                const auto property = std::dynamic_pointer_cast<std::add_const_t<T>>(object->GetProperty(name));
                if (property) {
                    return property;
                }
            }

            if (previous) {
                return previous->GetProperty<T>(name);
            }

            if constexpr (std::is_same_v<T, Property>) {
                Log(LogLevel::Warning, "Property {} is undefined.", name);
            } else {
                Log(LogLevel::Warning, "Property {} or is not of type {}.", name, GetTypeName<T>());
            }
            return nullptr;
        }

        std::shared_ptr<const Object> GetObject() const;
        std::shared_ptr<Object> &GetObject();
    };
}

#endif //SCOPE_H
