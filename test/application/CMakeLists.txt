cmake_minimum_required(VERSION 2.8)
project(test_application CXX)

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)
target_link_libraries(${PROJECT_NAME} application)

add_executable(test main.cpp)
target_link_libraries(test ${POCO_FOUNDATION})
