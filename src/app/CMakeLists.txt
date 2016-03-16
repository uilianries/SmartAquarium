cmake_minimum_required(VERSION 2.8)
project(app CXX)

file(GLOB SOURCE_FILES
    *.cpp)

file(GLOB HEADER_FILES
    *.hpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

