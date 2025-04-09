#include "Block.h"

namespace webwork {
    Block::Block(TokenT closingToken, std::string_view name) : closingToken(closingToken), name(name) {}
}