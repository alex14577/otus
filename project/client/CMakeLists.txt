cmake_minimum_required(VERSION 3.12)

find_package(Poco REQUIRED Foundation Util Net)

file(   GLOB_RECURSE SOURCES_MAIN 
    "main/src/*.cpp"
    "client/src/*.cpp"
    "app/src/*.cpp"
)

add_executable(client ${SOURCES_MAIN})

target_link_libraries(client Poco::Foundation Poco::Util Poco::Net cmn)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

install(TARGETS client RUNTIME DESTINATION bin)