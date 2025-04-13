#ifndef STRING_H
#define STRING_H

#include "../Property.h"
#include "Interfaces/IString.h"

namespace webwork::properties {
    class String final : public Property, public IString {
    public:
        std::string value;

        explicit String(std::string_view data = "");

        std::string GetStringValue() const override;
    };
}

#endif //TEXT_H
