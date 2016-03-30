cmake_minimum_required(VERSION 2.8)
project(application CXX)

file(GLOB SOURCE_FILES
    *.cpp)

find_library(IOTMQTTCLIENT_LIB IoTMQTTClient)
find_library(PAHO_LIB Paho)
set(MQTT_CLIENT_LIBRARIES ${IOTMQTTCLIENT_LIB} ${PAHO_LIB} pthread ssl crypto)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${POCO_LIBRARIES} ${MQTT_CLIENT_LIBRARIES})
