cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/test)

find_library(GOOGLE_TEST_LIB gtest)

add_subdirectory(application)
