cmake_minimum_required(VERSION 3.12)

file(GLOB httpserver_src
    "libhttpserver/src/*.hpp"
    "libhttpserver/src/*.h"
    "libhttpserver/src/*.cpp"

    "libhttpserver/src/details/*.cpp"

    "libhttpserver/src/httpserver/*.hpp"
    "libhttpserver/src/httpserver/details/*.hpp"
)

include_directories(httpserver
    libhttpserver/src
    libhttpserver/src/details
    libhttpserver/src/httpserver
    libhttpserver/src/httpserver/details
)

include_directories(internalapi 
    include/
    ../global/json/include
    ../global/json/include/nlohmann
)

file(GLOB libinternalapisrc CONFIGURE_DEPENDS "*.cpp" "requests/*.cpp")

add_compile_definitions(_HTTPSERVER_HPP_INSIDE_)
add_library(httpserver ${httpserver_src})
link_libraries(httpserver microhttpd)

add_library(internalapi SHARED ${libinternalapisrc})

target_link_libraries(internalapi httpserver)