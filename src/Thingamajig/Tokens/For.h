#ifndef FOR_H
#define FOR_H
#include "../Block.h"
#include "../Token.h"

namespace webwork {
    class For final : public Token, public Block {
    public:
        const std::string variable;
        const std::string collection;
        const std::optional<std::string> index;

        For(size_t startIndex, std::string_view variable, std::string_view collection, const std::optional<std::string_view> &index);

        std::string GetContent() const override;
    };
} // webwork

#endif //FOR_H
