#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include <memory>
#include "../Property.h"

namespace webwork::properties {
    class Array final : public Property {
        std::vector<std::shared_ptr<Property>> array;

        std::string ToString() const override;
    };
}

#endif //ARRAY_H
