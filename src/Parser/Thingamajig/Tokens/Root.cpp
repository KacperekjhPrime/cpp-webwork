#include "Root.h"

#include "../../TokenTypeConstants.h"

namespace webwork::thingamajig {
    Root::Root() : Token(0), BlockBase(TokenEmpty, "root") {}

    std::string Root::GetContent(const std::shared_ptr<Scope> &scope) const {
        std::string text = "";
        for (const auto &child : children) {
            text += child->GetContent(scope);
        }
        return text;
    }
}
