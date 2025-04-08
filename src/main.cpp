#include "Logging.h"
#include "Loading/Loader.h"
#include "Thingamajig/Parser/Parser.h"

// const std::string test = "{for asd in a}{asd}\\\\{endfor}\\iosajiaos{variable}\\ {if sus}conditional{endif} :3 asui{for thingamajig, index in thingamajigs}asasas{index}{endfor}\\";

const std::string test =
    "\nHello world\n"
    "{for value, index in array}\n"
    "\t{index}={value} \\{endfor} <- fake endfor :3\n"
    "\t{if condition}\n"
    "\t\t:3\n"
    "\t{endif}\n"
    "{endfor}\n"
    "{if condition}\n"
    "\tconditional value\n"
    "{endif}";

int main() {
    webwork::LoadModules();
    const auto tokens = ParseTokens(test, webwork::GetDefaultTokenTree());
    const auto root = AssembleTokenTree(tokens, webwork::GetDefaultMergeRules());
    Log(webwork::LogLevel::Info, root->GetContent());

    return 0;
}
