#include "Logging.h"
#include "Loading/Loader.h"
#include "Parser/Thingamajig/Thingamajig.h"
#include "Properties/Array.h"
#include "Properties/Function.h"
#include "Server/Server.h"

const std::string text = "\n{for value, index in array}{Foo(index, value)}\n{endfor}";

using namespace webwork;

std::string Foo(unsigned index, int value) {
    return std::format("{}: {:#6x}", index, value);
}

int main() {
    const auto root = thingamajig::ParseThingamajig(text);

    const auto object = std::make_shared<properties::Object>();
    object->GetProperty("array") = std::make_shared<properties::Array>(12, 2, 9);
    object->GetProperty("Foo") = std::make_shared<properties::Function>(Foo);

    Log(LogLevel::Info, root->GetContent(std::make_shared<properties::Scope>(object)));
    LoadModules();

    const ServerConfig config{};
    RunServer(config);
    return 0;
}
