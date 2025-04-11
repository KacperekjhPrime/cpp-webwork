#ifndef NUMBER_H
#define NUMBER_H
#include <memory>
#include "../Property.h"
#include "Interfaces/IBoolean.h"

namespace webwork::properties {
    class Number final : public Property, public IBoolean {
    public:
        double data{};

        explicit Number(double data = 0);

        std::string ToString() const override;
        bool GetBoolValue() const override;
    };
}

#endif //NUMBER_H
