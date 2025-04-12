#include "BlockBase.h"

namespace webwork::thingamajig {
    void BlockBase::AddChild(const std::shared_ptr<Token> &child) {
        children.push_back(child);
    }
}