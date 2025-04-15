#include "Variable.h"

#include <cassert>

namespace webwork::expression {
    Variable::Variable(std::string_view, const Chunk &chunk) : variable(TrimSpaces(chunk.GetText())) {}

    std::shared_ptr<const Property> Variable::Evaluate(const std::shared_ptr<const properties::Scope> &scope) const {
        return scope->GetProperty(variable);
    }
}
