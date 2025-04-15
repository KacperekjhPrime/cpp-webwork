#ifndef NUMBER_H
#define NUMBER_H
#include <memory>
#include "Property.h"
#include "Interfaces/IBoolean.h"
#include "Interfaces/INumber.h"
#include "Interfaces/IString.h"

namespace webwork::properties {
    class Number final : public Property, public IBoolean, public INumber, public IString {
    public:
        double value{};

        explicit Number(double data = 0);

        bool GetBoolValue() const override;
        double GetNumberValue() const override;
        std::string GetStringValue() const override;
    };
}

#endif //NUMBER_H
