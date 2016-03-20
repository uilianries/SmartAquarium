cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR}/src)

FIND_LIBRARY(CPPUNIT_LIBRARY cppunit)

add_subdirectory(application)
