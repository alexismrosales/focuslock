cmake_minimum_required(VERSION 3.10)

# Focuslock
add_library(flock flock.cpp)
target_include_directories(flock PUBLIC ../include)

# CLI
# Adding docopt
add_library(cli cli.cpp ../ext/docopt/docopt.cpp )
target_include_directories(cli PUBLIC ../include ../ext/)

