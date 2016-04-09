cmake_minimum_required(VERSION 2.8)
project(test_device CXX)

add_executable(dummy_device dummy_device.cpp dummy_main.cpp)
target_link_libraries(dummy_device device)

add_executable(test_device test_device.cpp main.cpp)
target_link_libraries(test_device ${POCO_LIBRARIES} ${GOOGLE_TEST_LIB} ${MQTT_CLIENT_LIBRARIES} signal_handler)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dummy_device.xml DESTINATION ${CMAKE_BINARY_DIR})
