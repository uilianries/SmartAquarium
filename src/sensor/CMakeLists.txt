cmake_minimum_required(VERSION 2.8)
project(sensor CXX)

file(GLOB SOURCE_FILES
    *.cpp)

set(SENSOR_APP_LIST thermal_sensor light_sensor ph_sensor)

foreach(APP ${SENSOR_APP_LIST})
add_executable(${APP} ${SOURCE_FILES})
target_link_libraries(${APP} device ${BBBGPIO_LIB} ${Boost_LIBRARIES})

install(TARGETS ${APP}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
endforeach()