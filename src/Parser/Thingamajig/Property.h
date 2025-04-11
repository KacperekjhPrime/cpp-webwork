#ifndef PROPERTY_H
#define PROPERTY_H
#include <string>

namespace webwork {
    class Property {
    public:
        virtual std::string ToString() const = 0;

        virtual ~Property() = default;
    };
}

#endif //PROPERTY_H
