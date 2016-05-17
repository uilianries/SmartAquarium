cmake_minimum_required(VERSION 2.8)
project(temperature_sensor CXX)

file(GLOB SOURCE_FILES
    *.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} device ${BBBGPIO_LIB} ${Boost_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
