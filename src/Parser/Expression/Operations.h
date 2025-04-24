#ifndef OPERATIONS_H
#define OPERATIONS_H
#include <memory>
#include <vector>

#include "Token.h"
#include "Tokens/Interfaces/IBinaryOperator.h"
#include "Tokens/Interfaces/IEvaluable.h"
#include "Tokens/Interfaces/IPostfixUnaryOperator.h"
#include "Tokens/Interfaces/IPrefixUnaryOperator.h"

namespace webwork::expression {
    class Operations {
        struct Operation {
            std::shared_ptr<const IBinaryOperator> binaryOperator;
            std::vector<std::shared_ptr<const IPrefixUnaryOperator>> prefixOperators;
            std::vector<std::shared_ptr<const IPostfixUnaryOperator>> postfixOperators;
            std::shared_ptr<const IEvaluable> expression;
        };

        std::vector<Operation> operations;

    public:
        Operations();

        std::shared_ptr<const Property> Evaluate(const std::shared_ptr<const properties::Scope> &scope) const;
        void AddElement(const std::shared_ptr<Token> &child);
        void CloseExpression() const;
    };
}

#endif //OPERATIONS_H
