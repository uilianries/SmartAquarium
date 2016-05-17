cmake_minimum_required(VERSION 2.8)
project(actuator CXX)

file(GLOB SOURCE_FILES
    *.cpp)

set(ACTUATOR_APP_LIST lighting heater)

foreach(APP ${ACTUATOR_APP_LIST})
    add_executable(${APP} ${SOURCE_FILES})
    target_link_libraries(${APP} device ${MOCK_BBBGPIO_LIB} ${Boost_LIBRARIES})

    install(TARGETS ${APP}
            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
endforeach()
