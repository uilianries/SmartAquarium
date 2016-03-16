cmake_minimum_required(VERSION 2.8)
project(app CXX)

file(GLOB SOURCE_FILES
    *.cpp)

file(GLOB HEADER_FILES
    *.hpp)

  add_library(${CMAKE_PROJECT_NAME} STATIC ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})

install(TARGETS ${CMAKE_PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

