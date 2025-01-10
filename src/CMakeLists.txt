cmake_minimum_required(VERSION 3.10)
add_library(flock flock.cpp)
target_include_directories(flock PUBLIC ../include)
