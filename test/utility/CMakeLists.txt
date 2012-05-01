cmake_minimum_required(VERSION 2.8)

project(utility)

find_package(SDL)

include_directories(${SDL_INCLUDE_DIR})

add_executable(utility main.cpp vector2.cpp rect.cpp)




