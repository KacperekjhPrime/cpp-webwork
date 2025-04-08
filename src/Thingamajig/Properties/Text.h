#ifndef TEXT_H
#define TEXT_H

#include "../Property.h"

namespace webwork::properties {
    class Text final : public Property {
    public:
        std::string data;

        explicit Text(std::string_view data = "");

        std::string ToString() const override;
    };
}

#endif //TEXT_H
