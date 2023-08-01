#pragma once

#include <string>

#include "../global/json/include/nlohmann/json.hpp"
#include "json_fwd.hpp"

enum ModuleType {
    ModSource = 0,
    ModDestination = 1,
    ModMixed = 2
};

class Module {
protected:
    nlohmann::json _config;

    virtual nlohmann::json _loadDefaultConfig() {
        return nlohmann::json::object();
    }
public:
    Module(nlohmann::json config) {
        _config = config;
    }

    std::vector<Module *> _loadedModules;

    std::string _name = "";

    ModuleType _type = ModMixed;

    virtual void init() {}
};