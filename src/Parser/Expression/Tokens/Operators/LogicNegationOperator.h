#ifndef LOGICNEGATIONOPERATOR_H
#define LOGICNEGATIONOPERATOR_H
#include "../../Token.h"
#include "../Interfaces/IUnaryOperator.h"

namespace webwork::expression {
    class LogicNegationOperator final : public Token, public IUnaryOperator {
    public:
        std::shared_ptr<const Property> Calculate(const std::shared_ptr<const Property> &prop) const override;
    };
}

#endif //LOGICNEGATIONOPERATOR_H
