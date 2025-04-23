#ifndef EXPRESSION_PARENTHESIS_H
#define EXPRESSION_PARENTHESIS_H
#include "Interfaces/IEvaluable.h"
#include "../Token.h"
#include "../../Chunk.h"
#include "../../Block.h"
#include "Interfaces/IBinaryOperator.h"
#include "Interfaces/IPostfixUnaryOperator.h"
#include "Interfaces/IPrefixUnaryOperator.h"

namespace webwork::expression {
    class Parenthesis final : public Token, public Block<Token>, public IEvaluable {
        struct Operation {
            std::shared_ptr<const IBinaryOperator> binaryOperator;
            std::shared_ptr<const IPrefixUnaryOperator> prefixOperator;
            std::shared_ptr<const IPostfixUnaryOperator> postfixOperator;
            std::shared_ptr<const IEvaluable> expression;
        };

        std::vector<Operation> operations = {{}};

        std::shared_ptr<const Property> Evaluate(const Operation &op, const std::shared_ptr<const properties::Scope> &scope);

    public:
        const size_t startIndex;

        Parenthesis();
        Parenthesis(std::string_view text, const Chunk &chunk);

        std::shared_ptr<const Property> Evaluate(const std::shared_ptr<const properties::Scope> &scope) const override;
        void AddChild(const std::shared_ptr<Token> &child) override;
        void CloseBlock() override;
    };
}

#endif //EXPRESSION_PARENTHESIS_H
