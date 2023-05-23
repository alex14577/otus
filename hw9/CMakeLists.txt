cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
option(WITH_GTEST "Whether to build Google test" ON)

project(hw9 VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

file(   GLOB_RECURSE SOURCES_MAIN 
    "parser/src/*.cpp",
    "async/src/*.cpp",
    "bulk/src/*.cpp",
    "manager/src/*.cpp",
    "sender/src/*.cpp",
    "main/src/*.cpp",
    )

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/result/${PROJECT_NAME}/bin)
set(CPACK_OUTPUT_FILE_PREFIX ${CMAKE_BINARY_DIR}/packages)

add_executable(async ${SOURCES_MAIN})

set_target_properties(async PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON    
)

target_include_directories(async
    PRIVATE "${PROJECT_SOURCE_DIR}"
)

target_compile_options(async PRIVATE
    -Wall -Wextra -pedantic -Werror -g
)

install(TARGETS async RUNTIME DESTINATION bin)

set (   SOURCES_GTEST 
        test/src/test_main.cpp 
        test/src/test_data.cpp 
        test/src/test_queue.cpp 
        async/src/queue.cpp
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