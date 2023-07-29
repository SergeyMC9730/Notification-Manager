#pragma once

#include "Module.hpp"

namespace NotificationAPI {
    class API {
    protected:
        std::vector<Module *> _modules;
    public:
        void init();
    };
}