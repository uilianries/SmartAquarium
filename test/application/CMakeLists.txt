cmake_minimum_required(VERSION 2.8)
project(test_application CXX)

add_executable(${PROJECT_NAME} dummy_application.cpp)
target_link_libraries(${PROJECT_NAME} application)

add_executable(test main.cpp ${PROJECT_NAME}.cpp)
target_link_libraries(test ${POCO_FOUNDATION} ${CPPUNIT_LIBRARY})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.xml DESTINATION ${CMAKE_BINARY_DIR})
