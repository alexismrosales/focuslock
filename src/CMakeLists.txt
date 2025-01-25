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

# SERIALIZATION
add_library(serialization serialization.cpp)
target_include_directories(serialization PUBLIC ../include ../ext/)

# SESSIONS
add_library(sessions sessions.cpp)
target_include_directories(sessions PUBLIC ../include ../ext/)

# CONFIG
add_library(config config.cpp)
target_include_directories(config PUBLIC ../include ../ext/)

# LIBRARIES LINKED TO CLI
target_link_libraries(cli PUBLIC commands actions)

# LIBRARIES LINKED TO ACTIONS
target_link_libraries(actions PUBLIC sessions)

# LIBRARIES LINKED TO SESSIONS
target_link_libraries(sessions PUBLIC config serialization)
