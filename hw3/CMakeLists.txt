cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(hw3 VERSION ${PROJECT_VESRION})
option(WITH_GTEST "Whether to build Google test" ON)

configure_file(version.h.in version.h)

set (   SOURCES_MAIN 
        main/src/main.cpp
    )
set (   SOURCES_LIB 
        my_allocator/src/allocator.cpp
    )
set (   SOURCES_GTEST 
    ${PROJECT_NAME}/test/src/test_main.cpp 
    ${PROJECT_NAME}/test/src/test_container.cpp 
    ${PROJECT_NAME}/test/src/test_allocator.cpp 
    )

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/result/${PROJECT_NAME}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/result/${PROJECT_NAME}/lib)
set(CPACK_OUTPUT_FILE_PREFIX ${CMAKE_BINARY_DIR}/packages)

add_executable(allocator ${SOURCES_MAIN})

set_target_properties(allocator PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON    
)

target_include_directories(allocator
    PRIVATE "${CMAKE_BINARY_DIR}/hw3"
)

target_compile_options(allocator PRIVATE
    -Wall -Wextra -pedantic -Werror
)

if(WITH_GTEST)
    include(GoogleTest)
    find_package(GTest REQUIRED)
    add_executable(test ${SOURCES_GTEST})

    set_target_properties(test PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
    )

    target_include_directories(test
        PRIVATE "${CMAKE_BINARY_DIR}/hw3"
    )

    target_link_libraries(test
        GTest::gtest_main
    )
endif()

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(test ${EXECUTABLE_OUTPUT_PATH}/test)
endif()