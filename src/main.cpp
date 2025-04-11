#include "Logging.h"
#include "Loading/Loader.h"
#include "Parser/Thingamajig/Thingamajig.h"
#include "Parser/Thingamajig/Properties/Array.h"
#include "Parser/Thingamajig/Properties/Boolean.h"
#include "Parser/Thingamajig/Properties/Number.h"
#include "Parser/Thingamajig/Properties/String.h"

const std::string test =
    "\nHello {sus}\n"
    "{for value, index in array}\n"
    "\t{index} = {value} \\{endfor} <- fake endfor :3\n"
    "\t{if condition1}\n"
    "\t\t:3 in my ass\n"
    "\t{endif}\n"
    "{endfor}\n"
    "{if condition2}\n"
    "\tconditional value\n"
    "{endif}";

const std::string expression = "amongus + 29.291267 / (7 % 3) * 29";

using namespace webwork;

int main() {
    // const auto tokens2 = TokenizeText(expression, GetExpressionTokenTree());
    // return 0;

    LoadModules();
    const auto root = thingamajig::ParseThingamajig(test);
    // const auto root = AssembleTree(tokens, GetDefaultMergeRules());

    const auto data = std::make_shared<properties::Object>();
    data->GetProperty("sus") = std::make_shared<properties::String>("World");
    data->GetProperty("condition1") = std::make_shared<properties::Boolean>(true);
    data->GetProperty("condition2") = std::make_shared<properties::Number>(3);

    const auto &array = std::make_shared<properties::Array>();
    data->GetProperty("array") = array;

    array->array.push_back(std::make_shared<properties::Number>(28));
    array->array.push_back(std::make_shared<properties::Number>(9.28));
    array->array.push_back(std::make_shared<properties::String>(":3"));
    array->array.push_back(std::make_shared<properties::Boolean>(false));

    Log(LogLevel::Info, root->GetContent(std::make_shared<Scope>(data, nullptr)));

    return 0;
}
