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
        enum TokenType : TokenT {
            Text = TokenText,
            Escape = TokenEscape,

            ExpressionOpening = TokensStart,
            ExpressionClosing,
            IfOpening,
            ForOpening,
            EndIf,
            EndFor,
            ComponentOpening,

            Comma = TokenTextBit | TokenInescapableBit | TokensStart,
            In,
            Equals
        };
    }

    namespace MergedToken {
        enum MergedToken : TokenT {
            Text = TokenText,

            Expression = TokensStart,
            If,
            For,
            Component
        };
    }

    const std::shared_ptr<TokenTree> &GetThingamajigTokenTree();
    const std::shared_ptr<MergeRules> &GetThingamajigMergeRules();
    const std::map<TokenT, TokenCreator<Token>> &GetThingamajigTokenMap();

    std::shared_ptr<Root> ParseThingamajig(std::string_view text);
}

#endif //THINGAMAJIG_H
