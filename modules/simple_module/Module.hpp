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
public:
    Module(nlohmann::json config) {
        _config = config;
    }

    std::string _name = "";

    ModuleType _type = ModMixed;

    virtual void init() {}
};