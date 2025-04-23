#ifndef OBJECT_H
#define OBJECT_H
#include <map>
#include <memory>

#include "Property.h"
#include "Interfaces/IDotAccessible.h"

namespace webwork::properties {
    class Object final : public Property, public IDotAccessible {
        std::map<std::string, std::shared_ptr<const Property>> properties;

    public:
        std::shared_ptr<const Property> GetProperty(const std::string &key) const override;
        void SetProperty(const std::string &key, const std::shared_ptr<const Property> &value);
    };
}

#endif //OBJECT_H
