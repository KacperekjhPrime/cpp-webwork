#ifndef NUMBER_H
#define NUMBER_H
#include <memory>
#include "../Property.h"
#include "Interfaces/IBoolean.h"
#include "Interfaces/INumber.h"

namespace webwork::properties {
    class Number final : public Property, public IBoolean, public INumber {
    public:
        double value{};

        explicit Number(double data = 0);

        std::string ToString() const override;
        bool GetBoolValue() const override;
        double GetNumberValue() const override;
    };
}

#endif //NUMBER_H
