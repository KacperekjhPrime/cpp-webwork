#include "Variable.h"

#include <format>

namespace webwork::tokens {
    Variable::Variable(size_t startIndex, std::string_view variableName) : Token(startIndex), variableName(variableName) {}

    std::string Variable::GetContent() const {
        // TODO: Display variables here
        return std::format("[{}]", variableName);
    }
}
