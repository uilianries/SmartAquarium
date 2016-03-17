cmake_minimum_required(VERSION 2.8)
project(application CXX)

file(GLOB SOURCE_FILES
    *.cpp)

file(GLOB HEADER_FILES
    *.hpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${POCO_FOUNDATION} ${POCO_UTIL})

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

