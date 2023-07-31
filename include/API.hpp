#pragma once

#include "Module.hpp"

#include "../modules/global/json/single_include/nlohmann/json.hpp"
#include "json_fwd.hpp"

namespace NotificationAPI {
    class API {
    protected:
        std::vector<Module *> _modules;

        nlohmann::json _loadDefaultConfig();
        bool _verifyConfigIntegrity(nlohmann::json config, bool throw_error);
    public:
        void init();
    };
}