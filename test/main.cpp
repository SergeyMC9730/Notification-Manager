#include <iostream>

#include "API.hpp"

#include <chrono>
#include <thread>

int main () {
    NotificationAPI::API *api = new NotificationAPI::API();
    api->init();

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}