#ifndef THINGAMAJIG_H
#define THINGAMAJIG_H
#include <memory>
#include <filesystem>

#include "Token.h"
#include "../Parser.h"
#include "../TokenTypeConstants.h"
#include "Tokens/Root.h"

namespace webwork::thingamajig {
    namespace TokenType {
        enum TokenType : TokenT {
            Text = TokenText,
            Escape = TokenEscape,

            IfOpening = TokensStart,
            ForOpening,
            EndIf,
            EndFor,
            ComponentOpening,

            Comma = TokenTextBit | TokenInescapableBit | TokensStart,
            In,
            Equals,
            ExpressionOpening,
            ExpressionClosing,

            NewLine = TokenAllowStrayBit | TokenInescapableBit
        };
    }

    namespace MergedToken {
        enum MergedToken : TokenT {
            Text = TokenText,

            Expression = 999,
            If,
            For,
            Component
        };
    }

    const std::shared_ptr<TokenTree> &GetThingamajigTokenTree();
    const std::shared_ptr<MergeRules> &GetThingamajigMergeRules();
    const std::map<TokenT, TokenCreator<Token>> &GetThingamajigTokenMap();

    std::shared_ptr<Root> ParseThingamajig(std::string_view text);

    std::shared_ptr<Root> ParseThingamajigFromFile(const std::filesystem::path &path);
}

#endif //THINGAMAJIG_H
