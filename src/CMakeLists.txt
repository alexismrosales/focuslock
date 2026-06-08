cmake_minimum_required(VERSION 3.10)

# CORE
add_library(core STATIC
    core/engine.cpp
    modules/pomodoro.cpp
)

target_include_directories(core PUBLIC ../include ../ext/)

# CLI
add_library(cli STATIC
    cli/cli.cpp
    cli/commands.cpp
    cli/actions.cpp
    cli/serialization.cpp
    cli/sessions.cpp
    cli/config.cpp
)

target_include_directories(cli PUBLIC ../include ../ext/)

target_link_libraries(cli PUBLIC core)
