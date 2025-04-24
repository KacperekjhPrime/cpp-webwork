#ifndef DOTACCESSOPERATOR_H
#define DOTACCESSOPERATOR_H
#include <vector>
#include <string>

#include "../../Token.h"
#include "../../../Chunk.h"
#include "../Interfaces/IPostfixUnaryOperator.h"

namespace webwork::expression {
    class DotAccessOperator final : public Token, public IPostfixUnaryOperator {
        static std::vector<std::string> SplitChunk(const Chunk &chunk);

        void LogTypeWarning(size_t index) const;

    public:
        const std::vector<std::string> parts;

        DotAccessOperator(std::string_view text, const Chunk &chunk);

        std::shared_ptr<const Property> CalculatePostfix(const std::shared_ptr<const Property> &prop, const std::shared_ptr<const properties::Scope> &scope) const override;
    };
}

#endif //DOTACCESSOPERATOR_H
