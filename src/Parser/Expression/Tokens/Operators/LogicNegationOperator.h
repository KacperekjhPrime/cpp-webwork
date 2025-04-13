#ifndef LOGICNEGATIONOPERATOR_H
#define LOGICNEGATIONOPERATOR_H
#include "../../Token.h"
#include "../Interfaces/IUnaryOperator.h"

namespace webwork::expression {
    class LogicNegationOperator final : public Token, public IUnaryOperator {
        static inline std::shared_ptr<LogicNegationOperator> instance;

    public:
        std::shared_ptr<const Property> Calculate(const std::shared_ptr<const Property> &prop) const override;

        static const std::shared_ptr<LogicNegationOperator> &GetInstance();
    };
}

#endif //LOGICNEGATIONOPERATOR_H
