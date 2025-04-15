#include "For.h"

#include <cassert>

#include "../Properties/Array.h"
#include "../Thingamajig.h"
#include "../Properties/Number.h"
#include "../../Chunk.h"
#include "../../../Logging.h"

namespace webwork::thingamajig {
    For::For(size_t textIndex, std::string_view variable, const std::optional<std::string_view> &index, const std::shared_ptr<expression::Parenthesis> &expression)
        : Token(textIndex), BlockBase(TokenType::EndFor, "for"), variable(TrimSpaces(variable)), index(index.has_value() ? TrimSpaces(*index) : ""), expression(expression) {}

    std::string For::GetContent(const std::shared_ptr<Scope> &scope) const {
        const auto array = std::dynamic_pointer_cast<const properties::Array>(expression->Evaluate(scope));
        if (!array) return "";

        const auto object = std::make_shared<properties::Object>();
        std::shared_ptr<properties::Number> index = nullptr;
        if (this->index.has_value()) {
            index = std::make_shared<properties::Number>(0);
            object->GetProperty(*this->index) = index;
        }

        std::string text = "";
        const auto innerScope = std::make_shared<Scope>(object, scope);
        for (size_t i = 0; i < array->value.size(); i++) {
            object->GetProperty(variable) = array->value[i];
            if (index) {
                index->value = i;
            }

            for (const auto &child : children) {
                text += child->GetContent(innerScope);
            }
        }
        return text;
    }
}
