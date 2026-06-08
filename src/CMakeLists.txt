cmake_minimum_required(VERSION 3.10)

# CLI
add_library(cli cli/cli.cpp)
target_include_directories(cli PUBLIC ../include ../ext/)

# CORE
add_library(core core/engine.cpp)
target_include_directories(core PUBLIC ../include ../ext/)

# COMMANDS
add_library(commands cli/commands.cpp)
target_include_directories(commands PUBLIC ../include ../ext/)

# ACTIONS
add_library(actions cli/actions.cpp)
target_include_directories(actions PUBLIC ../include ../ext/)

# SERIALIZATION
add_library(serialization cli/serialization.cpp)
target_include_directories(serialization PUBLIC ../include ../ext/)

# SESSIONS
add_library(sessions cli/sessions.cpp)
target_include_directories(sessions PUBLIC ../include ../ext/)

# CONFIG
add_library(config cli/config.cpp)
target_include_directories(config PUBLIC ../include ../ext/)

# POMODORO
add_library(pomodoro modules/pomodoro.cpp)
target_include_directories(pomodoro PUBLIC ../include ../ext/)

# LIBRARIES LINKED TO CLI
target_link_libraries(cli PUBLIC commands actions)

# LIBRARIES LINKED TO ACTIONS
target_link_libraries(actions PUBLIC sessions pomodoro)

# LIBRARIES LINKED TO SESSIONS
target_link_libraries(sessions PUBLIC config serialization)
