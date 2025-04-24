#ifndef LOGICNEGATIONOPERATOR_H
#define LOGICNEGATIONOPERATOR_H
#include "../../Token.h"
#include "../Interfaces/IPrefixUnaryOperator.h"

namespace webwork::expression {
    class LogicNegationOperator final : public Token, public IPrefixUnaryOperator {
        static inline std::shared_ptr<LogicNegationOperator> instance;

    public:
        std::shared_ptr<const Property> CalculatePrefix(const std::shared_ptr<const Property> &prop, const std::shared_ptr<const properties::Scope> &) const override;

        static const std::shared_ptr<LogicNegationOperator> &GetInstance();
    };
}

#endif //LOGICNEGATIONOPERATOR_H
