#ifndef THINGAMAJIG_FOR_H
#define THINGAMAJIG_FOR_H
#include "BlockBase.h"
#include "../Token.h"
#include "../../Expression/Tokens/Parenthesis.h"

namespace webwork::thingamajig {
    class For final : public Token, public BlockBase {
    public:
        const std::string variable;
        const std::optional<std::string> index;
        const std::shared_ptr<const expression::Parenthesis> expression;

        For(size_t textIndex, std::string_view variable, const std::optional<std::string_view> &index, const std::shared_ptr<expression::Parenthesis> &expression);

        std::string GetContent(const std::shared_ptr<Scope> &scope) const override;
    };
} // webwork

#endif //FOR_H
