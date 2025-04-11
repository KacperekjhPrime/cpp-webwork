#include "Variable.h"

#include <cassert>

namespace webwork::expression {
    Variable::Variable(std::string_view, const Chunk &chunk) : variable(chunk.tokens[0].text) {
        assert(chunk.tokens.size() == 1);
    }

    std::shared_ptr<const Property> Variable::Evaluate(const std::shared_ptr<const Scope> &scope) const {
        return scope->GetProperty(variable);
    }
}
