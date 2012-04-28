cmake_minimum_required(VERSION 2.8)

project(cmakeaux)

aux_source_directory(${cmakeaux_SOURCE_DIR} cmakeaux_SOURCES)
aux_source_directory(${cmakeaux_SOURCE_DIR}/foo cmakeaux_SOURCES)
aux_source_directory(${cmakeaux_SOURCE_DIR}/bar cmakeaux_SOURCES)

include_directories(
  ${cmakeaux_SOURCE_DIR}/foo
  ${cmakeaux_SOURCE_DIR}/bar)

message(${cmakeaux_SOURCES})

add_executable(main ${cmakeaux_SOURCES})


