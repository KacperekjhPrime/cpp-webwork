#ifndef EXPRESSION_PARENTHESIS_H
#define EXPRESSION_PARENTHESIS_H
#include "Interfaces/IEvaluable.h"
#include "../Token.h"
#include "../../Chunk.h"
#include "../../Block.h"
#include "Interfaces/IBinaryOperator.h"
#include "Interfaces/IUnaryOperator.h"

namespace webwork::expression {
    class Parenthesis final : public Token, public Block<Token>, public IEvaluable {
        struct Operation {
            std::shared_ptr<const IBinaryOperator> binaryOperator;
            std::shared_ptr<const IUnaryOperator> unaryOperator;
            std::shared_ptr<const IEvaluable> expression;
        };

        std::shared_ptr<const IUnaryOperator> initialUnary;
        std::shared_ptr<const IEvaluable> initialExpression;
        std::vector<Operation> operations = {};

    public:
        const size_t startIndex;

        Parenthesis();
        Parenthesis(std::string_view text, const Chunk &chunk);

        std::shared_ptr<const Property> Evaluate(const std::shared_ptr<const Scope> &scope) const override;
        void AddChild(const std::shared_ptr<Token> &child) override;
        void CloseBlock() override;
    };
}

#endif //EXPRESSION_PARENTHESIS_H
