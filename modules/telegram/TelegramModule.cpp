#include "TelegramModule.hpp"

#include <iostream>
#include <thread>

#include "tgbot/tgbot.h"

TelegramModule::TelegramModule(nlohmann::json config) : Module(config) {
    _name = "Telegram";
    _type = ModuleType::ModDestination;
}

void TelegramModule::init() {
    std::cout << "[MOD Telegram] loading telegram bot" << std::endl;

    std::thread thr([this]() {
        TgBot::Bot bot(_config["token"].get<std::string>());
        bot.getEvents().onCommand("start", [&bot, this](TgBot::Message::Ptr message) {
            bot.getApi().sendMessage(message->chat->id, "Hi!");
        });
        bot.getEvents().onAnyMessage([&bot, this](TgBot::Message::Ptr message) {
            printf("User wrote %s\n", message->text.c_str());
            if (StringTools::startsWith(message->text, "/start")) {
                return;
            }
            bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
        });

        try {
            printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
            TgBot::TgLongPoll longPoll(bot);
            while (true) {
                printf("Long poll started\n");
                longPoll.start();
            }
        } catch (TgBot::TgException& e) {
            printf("error: %s\n", e.what());
        }
    });

    thr.detach();

    std::cout << "[MOD Telegram] loading complete" << std::endl;
}