cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(server_executor VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/result/${PROJECT_NAME}/bin)
set(CPACK_OUTPUT_FILE_PREFIX ${CMAKE_BINARY_DIR}/packages)

set_property(GLOBAL
    PROPERTY CXX_STANDARD 20
    PROPERTY CXX_STANDARD_REQUIRED ON    
)

include_directories(
    "${PROJECT_SOURCE_DIR}"
)

add_compile_options(
    -Wall -Wextra -pedantic -Werror
)

add_subdirectory( server )
add_subdirectory( client )
add_subdirectory( cmn )

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
