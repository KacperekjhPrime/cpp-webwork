#ifndef SCOPE_H
#define SCOPE_H
#include <memory>

#include "Properties/Object.h"

namespace webwork {
    class Scope {
    public:
        std::shared_ptr<properties::Object> object;
        std::shared_ptr<Scope> previous;

        explicit Scope(const std::shared_ptr<properties::Object> &object, const std::shared_ptr<Scope> &previous = nullptr);

        std::shared_ptr<Property> GetProperty(const std::string &name) const;
    };
}

#endif //SCOPE_H
