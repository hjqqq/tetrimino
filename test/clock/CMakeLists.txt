cmake_minimum_required(VERSION 2.8)

project(clock)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_MODULE_PATH ${clock_SOURCE_DIR})

find_package(SDL)
find_package(SDL_draw)

add_executable(main main.cpp clock.cpp timer.cpp)

include_directories(
  ${clock_SOURCE_DIR}
  ${SDL_INCLUDE_DIR}
  ${SDLDRAW_INCLUDE_DIR})

target_link_libraries(main 
  ${SDL_LIBRARY}
  ${SDLDRAW_LIBRARY})
