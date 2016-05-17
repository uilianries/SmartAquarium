cmake_minimum_required(VERSION 2.8)
project(test_device CXX)

add_executable(dummy_device dummy_device.cpp dummy_main.cpp)
target_link_libraries(dummy_device device)

add_executable(test_device test_device.cpp main.cpp)
target_link_libraries(test_device ${POCO_LIBRARIES} ${GOOGLE_TEST_LIB} ${MQTT_CLIENT_LIBRARIES} signal_handler)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/dummy_device.xml
        DESTINATION /etc/smartaquarium
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ GROUP_WRITE WORLD_READ WORLD_WRITE)