cmake_minimum_required(VERSION 3.10)

# CLI
add_library(cli cli.cpp)
target_include_directories(cli PUBLIC ../include ../ext/)

# COMMANDS
add_library(commands commands.cpp)
target_include_directories(commands PUBLIC ../include ../ext/)

# ACTIONS
add_library(actions actions.cpp)
target_include_directories(actions PUBLIC ../include ../ext/)

# LIBRARIES LINKED TO CLI
target_link_libraries(cli PUBLIC commands actions)

