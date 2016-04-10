cmake_minimum_required(VERSION 2.8)
project(actuator CXX)

file(GLOB SOURCE_FILES
    *.cpp)

set(ACTUATOR_APP_LIST feeder lighting heater)

foreach(APP ${ACTUATOR_APP_LIST})
add_executable(${APP} ${SOURCE_FILES})
target_link_libraries(${APP} device)

install(TARGETS ${APP}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
endforeach()
