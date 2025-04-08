#include "For.h"

namespace webwork::tokens {
    For::For(size_t startIndex, std::string_view variable, std::string_view collection, const std::optional<std::string_view> &index) : Token(startIndex),
        Block(TokenType::EndFor, "for"), variable(variable), collection(collection), index(index) {}

    std::string For::GetContent(const std::shared_ptr<Scope> &scope) const {
        // TODO: Display loops here
        std::string text = std::format("[for({} : {})]", variable, collection);
        for (const auto &child : children) {
            text += child->GetContent(scope);
        }
        text += "[end loop]";
        return text;
    }
}