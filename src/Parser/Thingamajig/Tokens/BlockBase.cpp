#include "BlockBase.h"

namespace webwork::tokens {
    void BlockBase::AddChild(const std::shared_ptr<Token> &child) {
        children.push_back(child);
    }
}