#pragma once

#include "../../simple_module/Module.hpp"

#include <vector>

class TelegramModule : public Module {
public:
    TelegramModule(nlohmann::json config);

    TelegramModule();

    void init() override;
};