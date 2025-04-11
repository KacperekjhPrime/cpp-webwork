#ifndef SCOPE_H
#define SCOPE_H
#include <memory>

#include "Properties/Object.h"

namespace webwork {
    class Scope {
    public:
        std::shared_ptr<const properties::Object> object;
        std::shared_ptr<const Scope> previous;

        explicit Scope(const std::shared_ptr<const properties::Object> &object, const std::shared_ptr<const Scope> &previous = nullptr);

        std::shared_ptr<const Property> GetProperty(const std::string &name) const;
    };
}

#endif //SCOPE_H
