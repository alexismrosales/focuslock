add_executable(focuslock.out cli_app.cpp)
target_link_libraries(focuslock.out PRIVATE cli)
target_include_directories(focuslock.out PUBLIC ../ext)

add_executable(daemon.out daemon_app.cpp)
target_link_libraries(daemon.out PRIVATE core/engine)
target_include_directories(daemon.out PUBLIC ../ext)
