#ifndef BLOCKBASE_H
#define BLOCKBASE_H
#include "../../Block.h"

namespace webwork {
    class Token;
}

namespace webwork::tokens {
    class BlockBase : public Block<Token> {
    protected:
        std::vector<std::shared_ptr<Token>> children;

        using Block::Block;

    public:
        void AddChild(const std::shared_ptr<Token> &child) override;
    };
}

#endif //BLOCKBASE_H
