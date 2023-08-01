#include "API.hpp"
#include "json_fwd.hpp"
#include <stdexcept>

#ifdef _MODULE_INTERNALAPI_
#include "InternalAPIModule.hpp"
#endif

#ifdef _MODULE_TELEGRAM_
#include "TelegramModule.hpp"
#endif

#include <filesystem>
#include <iostream>
#include <fstream>

using namespace NotificationAPI;

nlohmann::json API::_loadDefaultConfig() {
    nlohmann::json conf;

    conf["modules"] = nlohmann::json();
    conf["modules"]["source"] = nlohmann::json::array();
    conf["modules"]["destination"] = nlohmann::json::array();

    conf["source_config"] = nlohmann::json::object();
    conf["destination_config"] = nlohmann::json::object();

    return conf;
}

bool API::_verifyConfigIntegrity(nlohmann::json config, bool throw_error) {
    if (!config.contains("modules")) {
        if (throw_error) throw std::runtime_error("modules list doesn't exist in the config");
    
        return false;
    }

    if (!config["modules"].contains("source")) {
        if (throw_error) throw std::runtime_error("source module list doesn't exist in the config");
    
        return false;
    }

    if (!config["modules"].contains("destination")) {
        if (throw_error) throw std::runtime_error("destination module list doesn't exist in the config");
    
        return false;
    }

    if (!config.contains("source_config")) {
        if (throw_error) throw std::runtime_error("source modules config doesn't exist in the config");
    
        return false;
    }

    if (!config.contains("destination_config")) {
        if (throw_error) throw std::runtime_error("destination modules config doesn't exist in the config");
    
        return false;
    }

    for (auto module : config["modules"]["source"]) {
        if (!module.is_string()) {
            if (throw_error) throw std::runtime_error("module's internal name should be a string");

            return false;
        }

        if (!config["source_config"].contains(module.get<std::string>())) {
            if (throw_error) throw std::runtime_error("module " + module.get<std::string>() + " doesn't have a configuration attached");

            return false;
        }
    }

    for (auto module : config["modules"]["destination"]) {
        if (!module.is_string()) {
            if (throw_error) throw std::runtime_error("module's internal name should be a string");

            return false;
        }

        if (!config["destination_config"].contains(module.get<std::string>())) {
            if (throw_error) throw std::runtime_error("module " + module.get<std::string>() + " doesn't have a configuration attached");

            return false;
        }
    }
    
    return true;
}

void API::init() {
    std::string path = "config.json";

    nlohmann::json j;

    if (!std::filesystem::exists(path)) {
        j = _loadDefaultConfig();
    } else {
        std::ifstream f(path);
        j = nlohmann::json::parse(f);
        f.close();
    }

    std::ofstream conf(path);
    conf << j.dump();
    conf.close();

    _verifyConfigIntegrity(j, true);

    // std::filesystem::

    #ifdef _MODULE_INTERNALAPI_
    if (j["destination_config"].contains("internal_api")) {
        _modules.push_back(new InternalAPIModule(j["destination_config"]["telegram"]));
    } else {
        std::cout << "module internal_api doesn't exist in the config so it is not going to be loaded" << std::endl;
    }
    #endif

    #ifdef _MODULE_TELEGRAM_
    if (j["destination_config"].contains("telegram")) {
        _modules.push_back(new TelegramModule(j["destination_config"]["telegram"]));
    } else {
        std::cout << "module telegram doesn't exist in the config so it is not going to be loaded" << std::endl;
    }
    #endif

    for (auto mod : _modules) {
        mod->_loadedModules = _modules;
        mod->init();
    }

    return;
}