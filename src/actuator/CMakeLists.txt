cmake_minimum_required(VERSION 2.8)
project(actuator CXX)

file(GLOB SOURCE_FILES *.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} device ${MOCK_BBBGPIO_LIB} ${Boost_LIBRARIES})