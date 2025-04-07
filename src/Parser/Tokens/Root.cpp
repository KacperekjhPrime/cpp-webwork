#include "Root.h"

namespace webwork {
    Root::Root() : Token(0), Block(TokenType::EndOfFile, "root") {}

    std::string Root::GetContent() const {
        std::string text = "";
        for (const auto &child : children) {
            text += child->GetContent();
        }
        return text;
    }
}