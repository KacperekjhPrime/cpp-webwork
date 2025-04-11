#include "Variable.h"

#include <cassert>

#include "../../../Logging.h"

namespace webwork::tokens {
    Variable::Variable(std::string_view text, const Chunk &chunk) : Token(chunk.GetTextIndex(text)), variableName(chunk.tokens[1].text) {
        assert(chunk.tokens.size() == 3);
    }

    std::string Variable::GetContent(const std::shared_ptr<Scope> &scope) const {
        // TODO: Display variables here
        const auto property = scope->GetProperty(variableName);
        if (property) {
            return property->ToString();

        }
        return "undefined";
    }
}
