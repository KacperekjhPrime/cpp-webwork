#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include <memory>
#include "../Property.h"

namespace webwork::properties {
    class Array final : public Property {
    public:
        std::vector<std::shared_ptr<Property>> value;
    };
}

#endif //ARRAY_H
