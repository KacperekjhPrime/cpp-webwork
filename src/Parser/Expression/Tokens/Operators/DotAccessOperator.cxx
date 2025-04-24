#include "DotAccessOperator.h"

#include <cassert>

namespace webwork::expression {
    std::vector<std::string> DotAccessOperator::SplitChunk(const Chunk &chunk) {
        assert(chunk.tokens.size() >= 2 && chunk.tokens.size() % 2 == 0);
        std::vector<std::string> parts;
        parts.reserve(chunk.tokens.size() / 2);
        for (size_t i = 1; i < chunk.tokens.size(); i += 2) {
            parts.emplace_back(chunk.tokens[i].text);
        }
        return parts;
    }

    void DotAccessOperator::LogTypeWarning(size_t index) const {
        std::string name;
        if (index > 0) {
            name = "(operand of unary dot access operator)";
            for (size_t i = 0; i < index; i++) {
                name += parts[i];
            }
        } else {
            name = "Operand of unary dot access operator";
        }
        Log(LogLevel::Warning, "{} is not IAccessible.", name);
    }

    DotAccessOperator::DotAccessOperator(std::string_view, const Chunk &chunk) : parts(SplitChunk(chunk)) {}

    std::shared_ptr<const Property> DotAccessOperator::CalculatePostfix(const std::shared_ptr<const Property> &prop, const std::shared_ptr<const properties::Scope> &scope) const {
        auto result = prop;
        for (size_t i = 0; i < parts.size(); i++) {
            const auto dotAccessible = std::dynamic_pointer_cast<const properties::IDotAccessible>(result);
            if (!dotAccessible) {
                LogTypeWarning(i);
                return nullptr;
            }
            result = dotAccessible->GetProperty(parts[i]);
        }
        return result;
    }
}
