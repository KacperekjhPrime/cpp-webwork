#ifndef OBJECT_H
#define OBJECT_H
#include <map>
#include <memory>

#include "Property.h"

namespace webwork::properties {
    class Object final : public Property {
        std::map<std::string, std::shared_ptr<const Property>> properties;

    public:
        std::shared_ptr<const Property> Get(const std::string &key) const;
        void Set(const std::string &key, const std::shared_ptr<const Property> &value);
    };
}

#endif //OBJECT_H
