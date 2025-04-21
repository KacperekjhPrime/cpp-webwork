#ifndef INDEXING_H
#define INDEXING_H
#include "../Token.h"
#include "../../Block.h"
#include "../../Chunk.h"
#include "Interfaces/IEvaluable.h"

namespace webwork::expression {
    class Indexing final : public Token, public Block<Token>, public IEvaluable {
        const std::string arrayName;
        std::shared_ptr<const IEvaluable> indexExpression;

    public:
        Indexing(std::string_view, const Chunk &chunk);

        void AddChild(const std::shared_ptr<Token> &child) override;
        void CloseBlock() override;

        std::shared_ptr<const Property> Evaluate(const std::shared_ptr<const properties::Scope> &scope) const override;
    };
}

#endif //INDEXING_H
