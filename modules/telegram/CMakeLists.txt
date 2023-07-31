cmake_minimum_required(VERSION 3.12)

# file(GLOB httpserver_src
#     "libhttpserver/src/*.hpp"
#     "libhttpserver/src/*.h"
#     "libhttpserver/src/*.cpp"

#     "libhttpserver/src/details/*.cpp"

#     "libhttpserver/src/httpserver/*.hpp"
#     "libhttpserver/src/httpserver/details/*.hpp"
# )

# include_directories(httpserver
#     libhttpserver/src
#     libhttpserver/src/details
#     libhttpserver/src/httpserver
#     libhttpserver/src/httpserver/details
# )

include_directories(internalapi 
    include/
    ../global/json/include
    ../global/json/include/nlohmann
    tgbot-cpp/include/
    tgbot-cpp/include/tgbot
)

add_subdirectory(tgbot-cpp)

file(GLOB libtelegramsrc CONFIGURE_DEPENDS "*.cpp")

add_library(telegram-mod SHARED ${libtelegramsrc})

target_link_libraries(telegram-mod TgBot)