# Created by Manuel Blum on 2011-05-25.
# Copyright 2013 University of Freiburg.

cmake_minimum_required(VERSION 2.8)

project(libgp CXX C)

# if no option is given, standard is release
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS_RELEASE "-DCLSQUARE -Wall -O2 -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "-DCLSQUARE -Wall -g -fPIC")

OPTION(BUILD_TESTS "Build tests" ON)
OPTION(BUILD_EXAMPLES "Build examples" ON)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})

find_package(Eigen3 3.0.1 REQUIRED)

# ----- Add include directories -----
include_directories(
      SYSTEM
      ${EIGEN3_INCLUDE_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ----- Add sources -----
include("Sources.cmake")

# ----- Add library target -----
add_library(gp ${LIBGP_SRC} ${LIBGP_INTERFACES})

# ----- Generate PKgconfig file ----
get_property(LIB64 GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS)
if ("${LIB64}" STREQUAL "TRUE")
    set(LIBSUFFIX 64)
else()
    set(LIBSUFFIX "")
endif()
set(INSTALL_LIB_DIR lib${LIBSUFFIX} CACHE PATH
    "Installation directory for libraries")
mark_as_advanced(INSTALL_LIB_DIR)
configure_file(${CMAKE_SOURCE_DIR}/contrib/libgp.pc.in 
	${CMAKE_BINARY_DIR}/libgp.pc @ONLY)

# ----- Add example targets -----
if(BUILD_EXAMPLES)
  ADD_SUBDIRECTORY(examples)
endif()

# ----- Testing -----
if(BUILD_TESTS)
  ADD_SUBDIRECTORY(tests)
endif()

# ----- Install -----
install(FILES ${LIBGP_INTERFACES} DESTINATION include/gp)
install(TARGETS gp
  EXPORT gpConfig
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION ${INSTALL_LIB_DIR}
  ARCHIVE DESTINATION ${INSTALL_LIB_DIR}
)
install(FILES ${CMAKE_BINARY_DIR}/libgp.pc DESTINATION ${INSTALL_LIB_DIR}/pkgconfig)

export(TARGETS gp
    NAMESPACE gp::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/gpConfig.cmake"
)
install(EXPORT gpConfig
    DESTINATION "${INSTALL_LIB_DIR}/gp/cmake"
    NAMESPACE gp::
)