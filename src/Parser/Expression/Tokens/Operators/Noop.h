#ifndef NOOP_H
#define NOOP_H
#include "../Interfaces/IBinaryOperator.h"

namespace webwork::expression {
    class Noop : public IBinaryOperator {
        static inline std::shared_ptr<const Noop> instance;

    public:
        std::shared_ptr<const Property> Calculate(const std::shared_ptr<const Property> &a,
            const std::shared_ptr<const Property> &b,
            const std::shared_ptr<const properties::Scope> &scope) const override;

        static const std::shared_ptr<const Noop> &GetInstance();
    };
}

#endif //NOOP_H
