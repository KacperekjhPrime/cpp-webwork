#ifndef OBJECT_H
#define OBJECT_H
#include <map>
#include <memory>

#include "Property.h"

namespace webwork::properties {
    class Object final : public Property {
        std::map<std::string, std::shared_ptr<const Property>> properties;

    public:
        std::shared_ptr<const Property> &GetProperty(const std::string &key);
        std::shared_ptr<const Property> GetProperty(const std::string &key) const;
    };
}

#endif //OBJECT_H
