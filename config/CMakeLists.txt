cmake_minimum_required(VERSION 2.8)

file(GLOB CONFIG_FILES
    *.xml)

install(FILES ${CONFIG_FILES} 
    DESTINATION /etc/smartaquarium)
