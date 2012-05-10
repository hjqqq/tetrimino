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
  aux_source_directory(${tetrimino_SOURCE_DIR}/src/utility tetrimino_SRC)
  aux_source_directory(${tetrimino_SOURCE_DIR}/src/globaldata tetrimino_SRC)
#  aux_source_directory(${tetrimino_SOURCE_DIR}/src/menu tetrimino_SRC)
  aux_source_directory(${tetrimino_SOURCE_DIR}/src/game tetrimino_SRC)

  include_directories(
    ${SDL_INCLUDE_DIR}
    ${SDLIMAGE_INCLUDE_DIR}
    ${SDLTTF_INCLUDE_DIR}
    ${SDLDRAW_INCLUDE_DIR}
    ${tetrimino_SOURCE_DIR}/header
    ${tetrimino_SOURCE_DIR}/header/utility
    ${tetrimino_SOURCE_DIR}/header/globaldata
    ${tetrimino_SOURCE_DIR}/header/menu
    ${tetrimino_SOURCE_DIR}/header/game)

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
