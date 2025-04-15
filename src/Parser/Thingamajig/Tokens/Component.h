#ifndef COMPONENT_H
#define COMPONENT_H
#include "../Token.h"
#include "../../Expression/Tokens/Parenthesis.h"

namespace webwork::thingamajig {
    class Component final : public Token {
    public:
        struct Value {
            std::string name;
            std::shared_ptr<const expression::Parenthesis> expression;
        };

        const std::string componentName;
        const std::vector<Value> values;

        Component(size_t startIndex, std::string_view componentName, const std::vector<Value> &values);
        std::string GetContent(const std::shared_ptr<properties::Scope> &scope) const override;
    };
}

#endif //COMPONENT_H
