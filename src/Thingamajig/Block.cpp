#include "Block.h"

namespace webwork {
    Block::Block(TokenType closingToken, std::string_view name) : closingToken(closingToken), name(name) {}
}