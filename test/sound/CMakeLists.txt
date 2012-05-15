cmake_minimum_required(VERSION 2.8)

project(sound)

find_package(SDL)
find_package(SDL_image)
find_package(SDL_ttf)
find_package(SDL_mixer)

if(SDL_FOUND         AND 
    SDLIMAGE_FOUND    AND 
    SDLTTF_FOUND      AND 
    SDLMIXER_FOUND)

  aux_source_directory(${sound_SOURCE_DIR} sound_SRC)

  include_directories(
    ${SDL_INCLUDE_DIR}
    ${SDLIMAGE_INCLUDE_DIR}
    ${SDLTTF_INCLUDE_DIR}
    ${SDLMIXER_INCLUDE_DIR})

  add_executable(sound ${sound_SRC})

  target_link_libraries(sound 
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${SDLTTF_LIBRARY}
    ${SDLMIXER_LIBRARY})

endif(SDL_FOUND         AND 
  SDLIMAGE_FOUND    AND 
  SDLTTF_FOUND      AND
  SDLMIXER_FOUND)

