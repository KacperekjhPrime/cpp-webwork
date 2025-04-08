#ifndef NUMBER_H
#define NUMBER_H
#include <memory>
#include "../Property.h"

namespace webwork::properties {
    class Number final : public Property {
    public:
        double data{};

        explicit Number(double data = 0);

        std::string ToString() const override;
    };
}

#endif //NUMBER_H
