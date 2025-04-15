#include "Number.h"

#include <cassert>

namespace webwork::expression {
    Number::Number(std::string_view, const Chunk &chunk) : value(std::make_shared<properties::Number>(stod(std::string(chunk.tokens[0].text)))) {
        assert(chunk.tokens.size() == 1);
    }

    std::shared_ptr<const Property> Number::Evaluate(const std::shared_ptr<const properties::Scope> &) const {
        return value;
    }
}
