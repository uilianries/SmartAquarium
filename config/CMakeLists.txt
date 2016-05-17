cmake_minimum_required(VERSION 2.8)

file(GLOB CONFIG_FILES
    *.xml)

install(FILES ${CONFIG_FILES} 
        DESTINATION /etc/smartaquarium
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ GROUP_WRITE WORLD_READ)