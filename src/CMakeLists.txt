set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${tetrimino_SOURCE_DIR}/src)

find_package(SDL)
find_package(SDL_image)
find_package(SDL_ttf)
find_package(SDL_draw)

if(SDL_FOUND         AND 
   SDLIMAGE_FOUND    AND 
   SDLTTF_FOUND      AND 
   SDLDRAW_FOUND)

  aux_source_directory(${tetrimino_SOURCE_DIR}/src tetrimino_SRC)

  include_directories(
    ${SDL_INCLUDE_DIR}
    ${SDLIMAGE_INCLUDE_DIR}
    ${SDLTTF_INCLUDE_DIR}
    ${SDLDRAW_INCLUDE_DIR}
    ${tetrimino_SOURCE_DIR}/header)

  add_executable(tetrimino ${tetrimino_SRC})

  target_link_libraries(tetrimino 
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${SDLTTF_LIBRARY}
    ${SDLDRAW_LIBRARY})

  install(TARGETS tetrimino
    DESTINATION bin)

endif(SDL_FOUND         AND 
      SDLIMAGE_FOUND    AND 
      SDLTTF_FOUND      AND
      SDLDRAW_FOUND)
