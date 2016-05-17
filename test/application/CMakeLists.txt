cmake_minimum_required(VERSION 2.8)
project(test_application CXX)

add_executable(dummy_application dummy_application.cpp dummy_main.cpp)
target_link_libraries(dummy_application application)

add_executable(${PROJECT_NAME} main.cpp ${PROJECT_NAME}.cpp)
target_link_libraries(${PROJECT_NAME} ${POCO_LIBRARIES} ${GOOGLE_TEST_LIB} pthread signal_handler)

install(FILES dummy_application.xml
        DESTINATION /etc/smartaquarium
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ GROUP_WRITE WORLD_READ WORLD_WRITE)