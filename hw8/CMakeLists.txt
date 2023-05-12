cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(hw8 VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

file(   GLOB_RECURSE SOURCES_MAIN 
        "crc/src/*.cpp"
        "main/src/*.cpp",
        "file/src/*.cpp",
    )

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/result/${PROJECT_NAME}/bin)
set(CPACK_OUTPUT_FILE_PREFIX ${CMAKE_BINARY_DIR}/packages)

add_executable(bayan ${SOURCES_MAIN})

set_target_properties(bayan PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON    
)

target_include_directories(bayan
    PRIVATE "${PROJECT_SOURCE_DIR}"
)

target_compile_options(bayan PRIVATE
    -Wall -Wextra -pedantic -Werror -g
)

install(TARGETS bayan RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
