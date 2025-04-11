#ifndef EXPRESSION_PARENTHESIS_H
#define EXPRESSION_PARENTHESIS_H
#include "../IEvaluable.h"
#include "../Token.h"
#include "../../Chunk.h"
#include "../../Block.h"

namespace webwork::expression {
    class Parenthesis final : public Token, public Block<Token>, public IEvaluable {
    public:
        const size_t startIndex;

        Parenthesis();
        Parenthesis(std::string_view text, const Chunk &chunk);

        std::shared_ptr<const Property> Evaluate(const std::shared_ptr<const Scope> &scope) const override;
    };
}

#endif //EXPRESSION_PARENTHESIS_H
