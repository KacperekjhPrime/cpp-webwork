#ifndef ROOT_H
#define ROOT_H
#include "../Token.h"
#include "../Block.h"

namespace webwork {
    class Root final : public Token, public Block {
    public:
        Root();

        std::string GetContent() const override;
    };
} // webwork

#endif //ROOT_H
