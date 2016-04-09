cmake_minimum_required(VERSION 2.8)
project(test_application CXX)

add_executable(dummy_application dummy_application.cpp dummy_main.cpp)
target_link_libraries(dummy_application application)

add_executable(${PROJECT_NAME} main.cpp ${PROJECT_NAME}.cpp)
target_link_libraries(${PROJECT_NAME} ${POCO_LIBRARIES} ${GOOGLE_TEST_LIB} pthread signal_handler)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dummy_application.xml DESTINATION ${CMAKE_BINARY_DIR})
