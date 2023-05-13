cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(hw7 VERSION ${PROJECT_VESRION})
option(WITH_GTEST "Whether to build Google test" ON)

configure_file(version.h.in version.h)

file(   GLOB_RECURSE SOURCES_MAIN 
        "main/src/*.cpp",
        "receiver/src/*.cpp",
        "worker/src/*.cpp",
        "parser/src/*cpp",
        "bulk/src/*cpp",
        "manager/src/*.cpp"
        "sender/src/*.cpp"
    )

set (   SOURCES_GTEST 
        test/src/test_main.cpp 
        test/src/test.cpp 
    )

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/result/${PROJECT_NAME}/bin)
set(CPACK_OUTPUT_FILE_PREFIX ${CMAKE_BINARY_DIR}/packages)

add_executable(bulk ${SOURCES_MAIN})

set_target_properties(bulk PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON    
)

target_include_directories(bulk
    PRIVATE "${PROJECT_SOURCE_DIR}"
)

target_compile_options(bulk PRIVATE
    -Wall -Wextra -pedantic -Werror -g
)

if(WITH_GTEST)
    include(GoogleTest)
    find_package(GTest REQUIRED)
    add_executable(gtest ${SOURCES_GTEST})

    set_target_properties(gtest PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
    )

    target_include_directories(gtest
        PRIVATE "${PROJECT_SOURCE_DIR}"
    )

    target_link_libraries(gtest
        GTest::gtest_main
    )
endif()

install(TARGETS bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_GTEST)
    enable_testing()
    add_test(gtest ${EXECUTABLE_OUTPUT_PATH}/gtest)
endif()