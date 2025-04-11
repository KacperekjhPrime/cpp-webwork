#ifndef BOOLEAN_H
#define BOOLEAN_H
#include "../Property.h"
#include "Interfaces/IBoolean.h"

namespace webwork::properties {
    class Boolean final : public Property, public IBoolean {
    public:
        bool value;

        explicit Boolean(bool value = false);

        std::string ToString() const override;
        bool GetBoolValue() const override;
    };
}

#endif //BOOLEAN_H
