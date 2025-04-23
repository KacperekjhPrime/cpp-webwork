#ifndef SUBTRACTIONOPERATOR_H
#define SUBTRACTIONOPERATOR_H

#include "../../Token.h"
#include "../Interfaces/IBinaryOperator.h"
#include "../Interfaces/IPrefixUnaryOperator.h"

namespace webwork::expression {
    class SubtractionOperator final : public Token, public IBinaryOperator, public IPrefixUnaryOperator {
        static inline std::shared_ptr<SubtractionOperator> instance;

    public:
        std::shared_ptr<const Property> CalculatePrefix(const std::shared_ptr<const Property> &prop) const override;
        std::shared_ptr<const Property> Calculate(const std::shared_ptr<const Property> &a, const std::shared_ptr<const Property> &b) const override;

        static std::shared_ptr<SubtractionOperator> GetInstance();
    };
}

#endif //SUBTRACTIONOPERATOR_H
