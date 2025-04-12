#ifndef THINGAMAJIG_ROOT_H
#define THINGAMAJIG_ROOT_H
#include "BlockBase.h"
#include "../Token.h"

namespace webwork::tokens {
    class Root final : public Token, public BlockBase {
    public:
        Root();

        std::string GetContent(const std::shared_ptr<Scope> &scope) const override;
    };
}

#endif //ROOT_H
