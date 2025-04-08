#ifndef STRING_H
#define STRING_H

#include "../Property.h"

namespace webwork::properties {
    class String final : public Property {
    public:
        std::string data;

        explicit String(std::string_view data = "");

        std::string ToString() const override;
    };
}

#endif //TEXT_H
