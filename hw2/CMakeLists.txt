cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(hw2 VERSION ${PROJECT_VESRION})

option(WITH_GTEST "Whether to build Google test" ON)

configure_file(version.h.in version.h)

set (   SOURCES_MAIN 
        ${PROJECT_NAME}/main/src/ip_filter.cpp
    )
set (   SOURCES_GTEST 
        ${PROJECT_NAME}/test/src/ip_test.cpp
    )
set (   SOURCES_LIB 
        ${PROJECT_NAME}/lib/src/ip_filter.cpp
    )

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/result/${PROJECT_NAME}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/result/${PROJECT_NAME}/lib)
set(CPACK_OUTPUT_FILE_PREFIX ${CMAKE_BINARY_DIR}/packages)

add_executable(ip_filter ${SOURCES_MAIN})
add_library(ip_filter_lib ${SOURCES_LIB})

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    
)
set_target_properties(ip_filter_lib PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_include_directories(ip_filter_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(ip_filter PRIVATE
    ip_filter_lib
)

if(WITH_GTEST)
    include(GoogleTest)
    find_package(GTest REQUIRED)
    add_executable(test_ip_filter ${SOURCES_GTEST})

    set_target_properties(test_ip_filter PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )

    target_include_directories(test_ip_filter
        PRIVATE "${CMAKE_BINARY_DIR}"
    )

    target_link_libraries(test_ip_filter
        GTest::gtest_main
        ip_filter_lib
    )
    target_compile_options(test_ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(ip_filter_lib PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip_filter_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_GTEST)
    enable_testing()
    add_test(test_ip_filter ${EXECUTABLE_OUTPUT_PATH}/test_ip_filter)
endif()