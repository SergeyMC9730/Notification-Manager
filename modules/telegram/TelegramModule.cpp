#include "TelegramModule.hpp"

#include <iostream>

TelegramModule::TelegramModule(nlohmann::json config) : Module(config) {
    _name = "Telegram";
}

void TelegramModule::init() {

    std::cout << "[MOD Telegram] loading telegram bot" << std::endl;

    std::cout << "[MOD Telegram] loading complete" << std::endl;
}