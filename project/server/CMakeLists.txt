cmake_minimum_required(VERSION 3.12)

find_package(Poco REQUIRED Foundation Util Net)

file(   GLOB_RECURSE SOURCES_MAIN 
    "main/src/*.cpp"
    "room/src/*.cpp"
    "client/src/*.cpp"
    "connection/src/*.cpp"
    "message/src/*.cpp"
)

add_executable(server ${SOURCES_MAIN})

target_include_directories( server PUBLIC
     $(CMAKE_SOURCE_DIR)  
)

target_link_libraries(server Poco::Foundation Poco::Util Poco::Net cmn)

install(TARGETS server RUNTIME DESTINATION bin)