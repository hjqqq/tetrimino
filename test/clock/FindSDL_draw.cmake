# Locate SDL_draw library
# This module defines
# SDLDRAW_LIBRARY, the name of the library to link against
# SDLDRAW_FOUND, if false, do not try to link to SDL
# SDLDRAW_INCLUDE_DIR, where to find SDL/SDL_drawPrimitives.h
#
# $SDLDIR is an environment variable that would
# correspond to the ./configure --prefix=$SDLDIR
# used in building SDL.

FIND_PATH(SDLDRAW_INCLUDE_DIR SDL_draw.h
  HINTS
  $ENV{SDLIMAGEDIR}
  $ENV{SDLDIR}
  PATH_SUFFIXES include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include/SDL
  /usr/include/SDL
  /usr/local/include/SDL12
  /usr/local/include/SDL11 # FreeBSD ports
  /usr/include/SDL12
  /usr/include/SDL11
  /usr/local/include
  /usr/include
  /sw/include/SDL # Fink
  /sw/include
  /opt/local/include/SDL # DarwinPorts
  /opt/local/include
  /opt/csw/include/SDL # Blastwave
  /opt/csw/include 
  /opt/include/SDL
  /opt/include
)

FIND_LIBRARY(SDLDRAW_LIBRARY 
  NAMES SDL_draw
  HINTS
  $ENV{SDLIMAGEDIR}
  $ENV{SDLDIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
)

SET(SDLDRAW_FOUND FALSE)
IF(SDLDRAW_LIBRARY AND SDLDRAW_INCLUDE_DIR)
  SET(SDLDRAW_FOUND TRUE)
ENDIF(SDLDRAW_LIBRARY AND SDLDRAW_INCLUDE_DIR)

