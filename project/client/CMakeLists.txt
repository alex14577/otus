cmake_minimum_required(VERSION 3.12)

find_package(Poco REQUIRED Foundation Util Net)

file(   GLOB_RECURSE SOURCES_MAIN 
    "main/src/*.cpp"
    "client/src/*.cpp"
    "app/src/*.cpp"
)

add_executable(client ${SOURCES_MAIN})

target_link_libraries(client Poco::Foundation Poco::Util Poco::Net cmn)

install(TARGETS client RUNTIME DESTINATION bin)