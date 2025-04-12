#ifndef INUMBER_H
#define INUMBER_H

namespace webwork::properties {
    class INumber {
    public:
        virtual ~INumber() = default;

        virtual double GetNumberValue() const = 0;
    };
}

#endif //INUMBER_H
