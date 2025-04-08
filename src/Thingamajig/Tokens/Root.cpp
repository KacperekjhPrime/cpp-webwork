#include "Root.h"

namespace webwork::tokens {
    Root::Root() : Token(0), Block(TokenType::EndOfFile, "root") {}

    std::string Root::GetContent(const std::shared_ptr<Scope> &scope) const {
        std::string text = "";
        for (const auto &child : children) {
            text += child->GetContent(scope);
        }
        return text;
    }
}