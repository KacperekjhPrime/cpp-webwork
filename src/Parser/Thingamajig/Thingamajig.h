#ifndef THINGAMAJIG_H
#define THINGAMAJIG_H
#include <memory>

#include "Token.h"
#include "../Parser.h"
#include "../TokenTypeConstants.h"
#include "Tokens/Root.h"
#include "Tokens/Text.h"

namespace webwork::thingamajig {
    namespace TokenType {
        // TODO: Add separate values for merged tokens

        enum TokenType : unsigned int {
            Text = TokenText,
            Escape = TokenEscape,

            VariableOpening = TokensStart,
            VariableClosing,
            If,
            For,
            EndIf,
            EndFor,
            Component,

            Comma = TokenTextBit | TokenInescapableBit | TokensStart,
            In,
            Equals
        };
    }

    const std::shared_ptr<TokenTree> &GetThingamajigTokenTree();
    const std::shared_ptr<MergeRules> &GetThingamajigMergeRules();
    const std::map<TokenT, TokenCreator<Token>> &GetThingamajigTokenMap();

    std::shared_ptr<Root> ParseThingamajig(std::string_view text);
}

#endif //THINGAMAJIG_H
