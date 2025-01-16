add_executable(focuslock cli_app.cpp)
target_link_libraries(focuslock PRIVATE cli)
target_include_directories(focuslock PUBLIC ../ext)

