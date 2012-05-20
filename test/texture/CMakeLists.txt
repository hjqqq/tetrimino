cmake_minimum_required(VERSION 2.8)

project(texture)

find_package(SDL)
find_package(SDL_image)

if(SDL_FOUND         AND 
   SDLIMAGE_FOUND)

  aux_source_directory(${texture_SOURCE_DIR} texture_SRC)

  include_directories(
    ${SDL_INCLUDE_DIR}
    ${SDLIMAGE_INCLUDE_DIR})

  add_executable(texture ${texture_SRC})

  target_link_libraries(texture 
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY})

endif(SDL_FOUND         AND 
      SDLIMAGE_FOUND)

