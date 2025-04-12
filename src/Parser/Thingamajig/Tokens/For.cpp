#include "For.h"

#include <cassert>

#include "../Properties/Array.h"
#include "../Thingamajig.h"
#include "../Properties/Number.h"
#include "../../Chunk.h"
#include "../../../Logging.h"

namespace webwork::thingamajig {
    For::For(std::string_view text, const Chunk &chunk) : Token(chunk.GetTextIndex(text)), BlockBase(thingamajig::TokenType::EndFor, "for"),
        variable(chunk.tokens[1].text), collection(chunk.tokens[chunk.tokens.size() == 5 ? 3 : 5].text),
        index(chunk.tokens.size() == 5 ? std::nullopt : std::optional<std::string>(chunk.tokens[5].text)) {
        assert(chunk.tokens.size() == 5 || chunk.tokens.size() == 7);
    }

    std::string For::GetContent(const std::shared_ptr<Scope> &scope) const {
        const auto array = scope->GetProperty<properties::Array>(collection);
        if (!array) return "";

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
