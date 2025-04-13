#ifndef ISTRING_H
#define ISTRING_H
#include <string>

namespace webwork::properties {
    class IString {
    public:
        virtual ~IString() = default;

        virtual std::string GetStringValue() const = 0;

        static std::string GetValue(const IString &prop);
    };
}

#endif //ISTRING_H
