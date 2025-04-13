#ifndef IBOOLEAN_H
#define IBOOLEAN_H

namespace webwork::properties {
    class IBoolean {
    public:
        virtual ~IBoolean() = default;

        virtual bool GetBoolValue() const = 0;

        static bool GetValue(const IBoolean &prop);
    };
}

#endif //IBOOLEAN_H
