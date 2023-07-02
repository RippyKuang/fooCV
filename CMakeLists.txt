cmake_minimum_required(VERSION 3.10)

project(fooCV VERSION 1.0)


add_subdirectory(lib)

add_executable(fooCV main.c)
target_link_libraries(fooCV PUBLIC foo m)
target_include_directories(fooCV PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/inc"
                          )


