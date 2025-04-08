#include "Logging.h"
#include "Loading/Loader.h"
#include "Thingamajig/Tokenizer.h"
#include "Thingamajig/Parser/Parser.h"
#include "Thingamajig/Properties/Array.h"
#include "Thingamajig/Properties/Boolean.h"
#include "Thingamajig/Properties/Number.h"
#include "Thingamajig/Properties/String.h"

const std::string test =
    "\nHello {sus}\n"
    "{for value, index in array}\n"
    "\t{index} = {value} \\{endfor} <- fake endfor :3\n"
    "\t{if condition1}\n"
    "\t\t:3\n"
    "\t{endif}\n"
    "{endfor}\n"
    "{if condition2}\n"
    "\tconditional value\n"
    "{endif}";

using namespace webwork;

int main() {
    LoadModules();
    const auto tokens = TokenizeText(test, GetDefaultTokenTree());
    const auto root = AssembleTokenTree(tokens, GetDefaultMergeRules());

    const auto data = std::make_shared<properties::Object>();
    data->GetProperty("condition1") = std::make_shared<properties::Boolean>(false);
    data->GetProperty("condition2") = std::make_shared<properties::Number>(0);

    const auto &array = std::make_shared<properties::Array>();
    data->GetProperty("array") = array;

    array->array.push_back(std::make_shared<properties::Number>(28));
    array->array.push_back(std::make_shared<properties::Number>(9.28));
    array->array.push_back(std::make_shared<properties::String>(":3"));
    array->array.push_back(std::make_shared<properties::Boolean>(false));

    Log(LogLevel::Info, root->GetContent(std::make_shared<webwork::Scope>(data, nullptr)));

    return 0;
}
