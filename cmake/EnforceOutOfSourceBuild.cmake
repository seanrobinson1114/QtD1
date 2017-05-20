# This macro will ensure that in-source build will fail.
# NOTE: The CMAKE_SOURCE_DIR variable stores the location of the project root
#       directory. The CMAKE_BINARY_DIR variable stores the location of the
#       build directory. When these two variables are equal a fatal error is
#       passed to cmake.
MACRO(ENFORCE_OUT_OF_SOURCE_BUILD)
  IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    MESSAGE(FATAL_ERROR "This project requires an out-of-source build!")
  ELSEIF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_INSTALL_PREFIX})
    MESSAGE(FATAL_ERROR "This project cannot be installed in the source directory!")
  ENDIF()
ENDMACRO()
