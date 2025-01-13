cmake_minimum_required(VERSION 3.10)

# FOCUSLOCK
add_library(flock flock.cpp)
target_include_directories(flock PUBLIC ../include)

# CLI
add_library(cli cli.cpp)
target_include_directories(cli PUBLIC ../include ../ext/)

# COMMANDS
add_library(commands commands.cpp)
target_include_directories(commands PUBLIC ../include ../ext/)

target_link_libraries(cli PUBLIC commands)

