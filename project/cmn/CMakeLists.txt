cmake_minimum_required(VERSION 3.12)

find_package(Poco REQUIRED Foundation Util Net)

file(   GLOB_RECURSE SOURCES_MAIN 
    "message/src/*.cpp"
    "cipher_engine/src/*.cpp"
)

add_library(cmn ${SOURCES_MAIN})


add_executable(cmn_main 
    ${SOURCES_MAIN}
    main.cpp
    )

target_compile_options(cmn PRIVATE
    -Wall -Wextra -pedantic -Werror
)

target_link_libraries(cmn_main cmn)

target_include_directories( cmn PUBLIC
     $(CMAKE_SOURCE_DIR)  
)

target_link_libraries(cmn Poco::Foundation Poco::Util PocoNet PocoCrypto ssl crypto)

# install(TARGETS server RUNTIME DESTINATION bin)