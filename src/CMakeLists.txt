cmake_minimum_required(VERSION 3.10)
project(Pref)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(/W0)

add_executable(Pref
    main.cpp
    typing.cpp
    player.cpp
    card.cpp
    table.cpp
)

get_filename_component(PARENT_DIR ${CMAKE_BINARY_DIR} DIRECTORY)

set_target_properties(Pref PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PARENT_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PARENT_DIR}
)

target_include_directories(Pref PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})