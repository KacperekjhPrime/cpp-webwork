#include "For.h"

#include "../Properties/Array.h"
#include "../../Logging.h"
#include "../Properties/Number.h"

namespace webwork::tokens {
    For::For(size_t startIndex, std::string_view variable, std::string_view collection, const std::optional<std::string_view> &index) : Token(startIndex),
        Block(TokenType::EndFor, "for"), variable(variable), collection(collection), index(index) {}

    std::string For::GetContent(const std::shared_ptr<Scope> &scope) const {
        const auto array = std::dynamic_pointer_cast<properties::Array>(scope->GetProperty(collection));
        if (array == nullptr) {
            Log(LogLevel::Warning, "Property {} is not an Array.", collection);
            return "";
        }

        const auto object = std::make_shared<properties::Object>();
        std::shared_ptr<properties::Number> index = nullptr;
        if (this->index.has_value()) {
            index = std::make_shared<properties::Number>(0);
            object->GetProperty("index") = index;
        }

        std::string text = "";
        const auto innerScope = std::make_shared<Scope>(object, scope);
        for (size_t i = 0; i < array->array.size(); i++) {
            object->GetProperty(variable) = array->array[i];
            if (index) {
                index->data = i;
            }

            for (const auto &child : children) {
                text += child->GetContent(innerScope);
            }
        }
        return text;
    }
}
