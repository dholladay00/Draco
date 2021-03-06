#--------------------------------------------*-cmake-*---------------------------------------------#
# file   src/compton_interface/CMakeLists.txt
# author Kendra Keady
# date   2017 February 28
# brief  Instructions for building CSK_Interface and its tests
# note   Copyright (C) 2017-2021 Triad National Security, LLC., All rights reserved.
#--------------------------------------------------------------------------------------------------#
cmake_minimum_required(VERSION 3.9.0)
project(compton_interface CXX)

# This packages requires libcompton.  See draco/config/vendor_libraries.cmake and
# draco/config/FindCOMPTON.cmake to manage how the build system discovers this TPL.  If not found,
# only a stub header file will be installed.

# ------------------------------------------------------------------------------------------------ #
# Source files
# ------------------------------------------------------------------------------------------------ #
configure_file(config.h.in ${PROJECT_BINARY_DIR}/compton_interface/config.h)

set(sources "${PROJECT_SOURCE_DIR}/CSK_Interface.cc")
set(headers ${PROJECT_BINARY_DIR}/compton_interface/config.h ${PROJECT_SOURCE_DIR}/CSK_Interface.hh)

if(TARGET COMPTON::compton)

  # Build library
  add_component_library(
    TARGET Lib_compton_interface
    TARGET_DEPS "Lib_c4;COMPTON::compton"
    INCLUDE_DIRS "PUBLIC;$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>"
    LIBRARY_NAME compton_interface
    SOURCES "${sources}"
    HEADERS "${headers}")

  # Copy necessary dll files to the build directory
  if(MSVC AND DRACO_LIBRARY_TYPE STREQUAL SHARED)
    add_custom_command(
      TARGET Lib_compton_interface
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:COMPTON::compton>
              $<TARGET_FILE_DIR:Lib_compton_interface>)
  endif()

  # Install
  install(FILES ${headers} DESTINATION ${DBSCFGDIR}include/compton_interface)

  # Unit tests
  if(BUILD_TESTING)
    add_subdirectory(test)
  endif()

  # Autodoc
  process_autodoc_pages()

else()

  # If no CSK_Interface library, only install headers (stubs).
  install(FILES ${headers} DESTINATION ${DBSCFGDIR}include/compton_interface)

endif()

# ------------------------------------------------------------------------------------------------ #
# End compton_interface/CMakeLists.txt
# ------------------------------------------------------------------------------------------------ #
