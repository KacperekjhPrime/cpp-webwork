#ifndef BOOLEAN_H
#define BOOLEAN_H
#include "../Property.h"
#include "Interfaces/IBoolean.h"
#include "Interfaces/INumber.h"
#include "Interfaces/IString.h"

namespace webwork::properties {
    class Boolean final : public Property, public IBoolean, public INumber, public IString {
    public:
        bool value;

        explicit Boolean(bool value = false);

        bool GetBoolValue() const override;
        double GetNumberValue() const override;
        std::string GetStringValue() const override;
    };
}

#endif //BOOLEAN_H
