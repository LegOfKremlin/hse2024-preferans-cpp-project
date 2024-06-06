cmake_minimum_required(VERSION 3.10)
project(Pref)

set(CMAKE_CXX_STANDARD 17)

add_executable(Pref
    main.cpp
    typing.cpp
    player.cpp
    card.cpp
    table.cpp
)

target_include_directories(Pref PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})