add_executable(flock_app flock_app.cpp)
target_link_libraries(flock_app PRIVATE cli)
target_include_directories(flock_app PUBLIC ../ext)

