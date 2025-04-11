#ifndef IBOOLEAN_H
#define IBOOLEAN_H

namespace webwork {
    class IBoolean {
    public:
        virtual ~IBoolean() = default;

        virtual bool GetBoolValue() const = 0;
    };
}

#endif //IBOOLEAN_H
