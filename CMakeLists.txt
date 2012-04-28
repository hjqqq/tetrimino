cmake_minimum_required(VERSION 2.8.6)

project(tetrimino)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_INSTALL_PREFIX ${tetrimino_BINARY_DIR})

add_subdirectory(src)
add_subdirectory(doc)
add_subdirectory(res)

