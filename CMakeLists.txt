cmake_minimum_required(VERSION 3.11)
project(node_native_buffer)

set(CMAKE_CXX_STANDARD 11)

add_executable(node_native_buffer cpptest/app.cpp src/datasource.hpp src/data.hpp src/daemon.cpp src/daemon.hpp src/udpclient.cpp src/udpclient.h src/nodebridge.cpp src/nodebridge.h src/terminable.hpp src/main.h)

if (CMAKE_SYSTEM_NAME MATCHES Darwin)
    if(CMAKE_GENERATOR STREQUAL Xcode)
        SET(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -undefined dynamic_lookup")
        message("Dynamic lookup fix for macOS")
    else(CMAKE_GENERATOR STREQUAL Xcode)
        SET(CMAKE_SHARED_MODULE_CREATE_C_FLAGS "${CMAKE_SHARED_MODULE_CREATE_C_FLAGS} -Wl,-undefined,dynamic_lookup")
        message("Dynamic lookup fix for macOS ")
    endif(CMAKE_GENERATOR STREQUAL Xcode)
endif (CMAKE_SYSTEM_NAME MATCHES Darwin)


target_include_directories(node_native_buffer PRIVATE /Users/olegchir/git/node-native-buffer/node_modules/nan)
target_include_directories(node_native_buffer PRIVATE /usr/local/Cellar/node/10.1.0/include/node)
target_include_directories(node_native_buffer PRIVATE /usr/local/Cellar/icu4c/61.1/include)


