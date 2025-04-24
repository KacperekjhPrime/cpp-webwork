#include "Noop.h"

namespace webwork::expression {
    std::shared_ptr<const Property> Noop::Calculate(const std::shared_ptr<const Property> &a,
            const std::shared_ptr<const Property> &b,
            const std::shared_ptr<const properties::Scope> &scope) const {
        return b;
    }

    const std::shared_ptr<const Noop> &Noop::GetInstance() {
        if (!instance) {
            instance = std::make_shared<Noop>();
        }
        return instance;
    }
}