cmake_minimum_required(VERSION 2.8)
project(device CXX)

find_library(IOTMQTTCLIENT_LIB IoTMQTTClient)
find_library(PAHO_LIB Paho)
set(MQTT_CLIENT_LIBRARIES ${IOTMQTTCLIENT_LIB} ${PAHO_LIB} pthread ssl crypto)

add_library(device STATIC device.cpp)
target_link_libraries(device
                    application
                    ${MQTT_CLIENT_LIBRARIES}
                    ${POCO_FOUNDATION_LIB}
                    task
                    dl)
