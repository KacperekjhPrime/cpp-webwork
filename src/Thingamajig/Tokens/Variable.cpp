#include "Variable.h"

#include <format>

#include "../../Logging.h"

namespace webwork::tokens {
    Variable::Variable(size_t startIndex, std::string_view variableName) : Token(startIndex), variableName(variableName) {}

    std::string Variable::GetContent(const std::shared_ptr<Scope> &scope) const {
        // TODO: Display variables here
        const auto property = scope->GetProperty(variableName);
        if (property) {
            return property->ToString();

        }
        return "undefined";
    }
}
