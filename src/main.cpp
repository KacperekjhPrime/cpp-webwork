#include <chrono>
#include <fstream>

#include "Logging.h"
#include "ModuleConfig.h"
#include "Loading/Loader.h"
#include "Properties/Array.h"
#include "Properties/Function.h"
#include "Server/Server.h"

using namespace webwork;

bool IsMarcin(const std::string &name) {
    return name == "Marcin";
}

std::string GetRank(const std::string &name, const std::string &surname) {
    if (name == "Błażej") return "a kimty pspspspsp";
    if (surname == "Reinfus") return "a good boy :3";
    return "a boy";
}

std::shared_ptr<properties::Object> CreatePerson(std::string_view name, std::string_view surname) {
    const auto person = std::make_shared<properties::Object>();
    person->SetProperty("name", properties::CreateProperty(name));
    person->SetProperty("surname", properties::CreateProperty(surname));
    return person;
}

int main() {
    const auto moduleConfig = std::make_shared<ModuleConfig>("components");
    SetCurrentModuleConfig(moduleConfig);

    const auto object = std::make_shared<properties::Object>();
    object->SetProperty("people", std::make_shared<properties::Array>(CreatePerson("Marcin", "Reinfus"), CreatePerson("Błażej", "Burek"), CreatePerson("Kacper", "Puto"), CreatePerson("Marcin", "Stanisz")));
    object->SetProperty("IsMarcin", std::make_shared<properties::Function>(IsMarcin));
    object->SetProperty("GetRank", std::make_shared<properties::Function>(GetRank));

    const std::string page = moduleConfig->components.GetComponent("MainPage.html")->GetContent(nullptr, object);
    std::ofstream out{"test.html"};
    out << page;
    return 0;

    const ServerConfig config{};
    RunServer(config);
    return 0;
}
