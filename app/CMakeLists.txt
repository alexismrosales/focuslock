add_executable(focuslock.out cli_app.cpp)
target_link_libraries(focuslock.out PRIVATE cli)
target_include_directories(focuslock.out PUBLIC ../ext)

