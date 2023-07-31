cmake_minimum_required(VERSION 3.12)

set(LIBS)

# MODULES
set(ENABLE_MODULE_INTERNALAPI 1)
set(ENABLE_MODULE_TELEGRAM 1)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0042 NEW)

project(notifapi VERSION 0.1.0 LANGUAGES C CXX)

if (ENABLE_MODULE_INTERNALAPI)
    add_compile_definitions(_MODULE_INTERNALAPI_)
    add_subdirectory(modules/internal_api)
    set(LIBS ${LIBS} internalapi)
    include_directories(modules/internal_api/include)
    include_directories(modules/internal_api/libhttpserver/src)
endif()

if (ENABLE_MODULE_TELEGRAM)
    add_compile_definitions(_MODULE_TELEGRAM_)
    add_subdirectory(modules/telegram)
    set(LIBS ${LIBS} telegram-mod)
    include_directories(modules/telegram/include)
    include_directories(modules/telegram/tgbot-cpp/include)
endif()

include_directories(include)
include_directories(modules/simple_module/)
include_directories(modules/global/json/include)
include_directories(modules/global/json/include/nlohmann)

file(GLOB libnotifsrc CONFIGURE_DEPENDS "libnotifapi/*.cpp" "libnotifapi/*.c")

file(GLOB libnotiftestsrc CONFIGURE_DEPENDS "test/*.cpp" "test/*.c")

set(FILES ${libnotifsrc})

add_library(notifapi SHARED ${FILES})

add_executable(notifapi-test ${libnotiftestsrc})

target_link_libraries(notifapi ${LIBS})
target_link_libraries(notifapi-test notifapi)