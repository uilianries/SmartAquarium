cmake_minimum_required(VERSION 2.8)
project(task CXX)

add_library(${PROJECT_NAME} STATIC ${PROJECT_NAME}.cpp)
target_link_libraries(${PROJECT_NAME} ${POCO_FOUNDATION_LIB})
