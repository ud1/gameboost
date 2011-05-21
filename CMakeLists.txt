project( GAMEBOOST_DEPS )
cmake_minimum_required(VERSION 2.8)

set( STATIC_DEP_LIBS_DIR ${GAMEBOOST_DEPS_SOURCE_DIR}/lib )
set( CMAKE_INSTALL_PREFIX ${GAMEBOOST_DEPS_SOURCE_DIR} )
set( CMAKE_DEBUF_POSTFIX "_d" )

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: Debug, Release" FORCE)
endif ()

add_subdirectory( jpeglib )
add_subdirectory( freetype )
add_subdirectory( yaml-cpp )
add_subdirectory( glew )
add_subdirectory( gtest )
