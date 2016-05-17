cmake_minimum_required(VERSION 2.8)
project(smartaquarium CXX)

set(${CMAKE_PROJECT_NAME}_VERSION_MAJOR 0)
set(${CMAKE_PROJECT_NAME}_VERSION_MINOR 1)

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_VERBOSE_MAKEFILE ON)
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage -std=c++14 -pedantic -Wall -Wextra -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Woverloaded-virtual -Wredundant-decls -Wsign-promo -Wstrict-overflow=5 -Wswitch-default -Werror -Wno-unused")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

configure_file(
    "${PROJECT_SOURCE_DIR}/src/version.hpp.in"
    "${PROJECT_BINARY_DIR}/src/version.hpp")

include_directories("${PROJECT_BINARY_DIR}")
include_directories(${PROJECT_SOURCE_DIR}/src)

find_library(POCO_FOUNDATION_LIB PocoFoundation)
find_library(POCO_UTIL_LIB PocoUtil)
find_library(POCO_JSON_LIB PocoJSON)
find_library(IOTMQTTCLIENT_LIB IoTMQTTClient)
find_library(PAHO_LIB Paho)
find_library(BBBGPIO_LIB bbbgpio)
find_library(MOCK_BBBGPIO_LIB mock_bbbgpio)

find_package(Boost
        COMPONENTS
        filesystem
        system
        regex
        REQUIRED)

set(POCO_LIBRARIES ${POCO_FOUNDATION_LIB} ${POCO_UTIL_LIB} ${POCO_JSON_LIB})
set(MQTT_CLIENT_LIBRARIES ${IOTMQTTCLIENT_LIB} ${PAHO_LIB} crypto ssl pthread)

option(TESTS "Generate tests" ON)

add_subdirectory(src)
if (TESTS)
    add_subdirectory(test)
endif()
add_subdirectory(config)
add_subdirectory(service)
