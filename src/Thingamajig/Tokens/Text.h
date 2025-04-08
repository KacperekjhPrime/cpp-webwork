#ifndef TEXT_H
#define TEXT_H
#include "../Token.h"

namespace webwork::tokens {
    class Text final : public Token {
    public:
        std::string text;

        Text(size_t startIndex, std::string_view text);

        std::string GetContent(const std::shared_ptr<Scope> &) const override;
    };
}

#endif //TEXT_H
