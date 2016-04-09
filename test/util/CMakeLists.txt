cmake_minimum_required(VERSION 2.8)
project(util CXX)

add_library(signal_handler STATIC signal_handler.cpp)
target_link_libraries(signal_handler ${POCO_FOUNDATION_LIB})


