cmake_minimum_required(VERSION 2.8)

project(random)

set(CMAKE_CXX_FLAGS -std=c++0x)
set(CMAKE_BUILD_TYPE debug)
add_executable(random main.cpp randomizer.cpp randomqueue.cpp)
