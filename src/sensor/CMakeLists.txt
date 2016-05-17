cmake_minimum_required(VERSION 2.8)
project(sensor CXX)

file(GLOB SOURCE_FILES
    *.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} device ${BBBGPIO_LIB} ${Boost_LIBRARIES})

set(SENSOR_APP_LIST light_sensor ph_sensor)
foreach(APP ${SENSOR_APP_LIST})
    install(TARGETS ${PROJECT_NAME}
            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
            PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_EXECUTE
            RENAME ${APP})
endforeach()