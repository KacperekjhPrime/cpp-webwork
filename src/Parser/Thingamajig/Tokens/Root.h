#ifndef THINGAMAJIG_ROOT_H
#define THINGAMAJIG_ROOT_H
#include "BlockBase.h"
#include "../Token.h"

namespace webwork::thingamajig {
    class Root final : public Token, public BlockBase {
    public:
        Root();

        std::string GetContent(const std::shared_ptr<properties::Scope> &scope) const override;
    };
}

#endif //ROOT_H
