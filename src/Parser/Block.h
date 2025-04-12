#ifndef NESTABLETOKEN_H
#define NESTABLETOKEN_H
#include <memory>
#include <vector>

#include "TokenTypeConstants.h"

namespace webwork {
    template <class T>
    class Block {
    protected:
        Block(TokenT closingToken, std::string_view name) : closingToken(closingToken), name(name) {}

    public:
        const TokenT closingToken;
        const std::string name;

        virtual ~Block() = default;

        virtual void AddChild(const std::shared_ptr<T> &child) = 0;
        virtual void CloseBlock() {}
    };
}

#endif //NESTABLETOKEN_H