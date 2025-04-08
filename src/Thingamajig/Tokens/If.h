#ifndef IF_H
#define IF_H
#include "../Block.h"
#include "../Token.h"

namespace webwork::tokens {
    class If final : public Token, public Block {
    public:
        const std::string condition;

        If(size_t startIndex, std::string_view condition);

        std::string GetContent(const std::shared_ptr<Scope> &scope) const override;
    };
} // webwork

#endif //IF_H
