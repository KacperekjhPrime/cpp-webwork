#ifndef EXPRESSION_FUNCTION_H
#define EXPRESSION_FUNCTION_H
#include "../Operations.h"
#include "../Token.h"
#include "../../Block.h"
#include "../../Chunk.h"
#include "Interfaces/IEvaluable.h"

namespace webwork::expression {
    class Function final : public Token, public Block<Token>, public IEvaluable {
        std::string functionName;
        std::vector<Operations> params;

    public:
        Function(std::string_view text, const Chunk &chunk);

        void AddChild(const std::shared_ptr<Token> &child) override;
        void CloseBlock() override;

        std::shared_ptr<const Property> Evaluate(const std::shared_ptr<const properties::Scope> &scope) const override;
    };
}

#endif //FUNCTION_H
