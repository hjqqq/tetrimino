find_package(Doxygen)

if(DOXYGEN_FOUND)
  
  add_custom_target(doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${tetrimino_SOURCE_DIR}/doc/Doxyfile
    WORKING_DIRECTORY ${tetrimino_SOURCE_DIR}/doc
    COMMENT "building doc!!!")

  install(DIRECTORY html/
    DESTINATION doc)

endif(DOXYGEN_FOUND)
