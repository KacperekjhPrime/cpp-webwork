#ifndef INDEXING_H
#define INDEXING_H
#include "../Operations.h"
#include "../Token.h"
#include "../../Block.h"
#include "../../Chunk.h"
#include "Interfaces/IEvaluable.h"
#include "Interfaces/IPostfixUnaryOperator.h"

namespace webwork::expression {
    class Indexing final : public Token, public Block<Token>, public IPostfixUnaryOperator {
        Operations operations;

    public:
        Indexing(std::string_view, const Chunk &chunk);

        void AddChild(const std::shared_ptr<Token> &child) override;
        void CloseBlock() override;

        std::shared_ptr<const Property> CalculatePostfix(const std::shared_ptr<const Property> &prop, const std::shared_ptr<const properties::Scope> &scope) const override;
    };
}

#endif //INDEXING_H
