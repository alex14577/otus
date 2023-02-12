cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(hw3 VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

set (   SOURCES_MAIN 
        main/src/main.cpp
    )
set (   SOURCES_LIB 
        my_allocator/src/allocator.cpp
    )

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/result/${PROJECT_NAME}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/result/${PROJECT_NAME}/lib)
set(CPACK_OUTPUT_FILE_PREFIX ${CMAKE_BINARY_DIR}/packages)

add_executable(allocator ${SOURCES_MAIN})

set_target_properties(allocator PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON    
)

target_include_directories(allocator
    PRIVATE "${CMAKE_BINARY_DIR}/hw3"
)

target_compile_options(allocator PRIVATE
    -Wall -Wextra -pedantic -Werror
)

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
