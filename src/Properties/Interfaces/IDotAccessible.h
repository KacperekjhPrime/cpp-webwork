#ifndef IDOTACCESSIBLE_H
#define IDOTACCESSIBLE_H
#include <memory>

#include "../Property.h"

namespace webwork::properties {
    class IDotAccessible {
    public:
        virtual ~IDotAccessible() = default;

        virtual std::shared_ptr<const Property> GetProperty(const std::string &key) const = 0;
    };
}

#endif //IDOTACCESSIBLE_H