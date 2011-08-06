project( GAMEBOOST )
cmake_minimum_required(VERSION 2.8)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GAMEBOOST_SOURCE_DIR}/bin CACHE PATH "Single Directory for all Executables." )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${GAMEBOOST_SOURCE_DIR}/bin CACHE PATH "Single Directory for all Executables." )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${GAMEBOOST_SOURCE_DIR}/linklib CACHE PATH "Single Directory for all static libraries." )

set(CMAKE_FIND_LIBRARY_PREFIXES "lib")
if (MSVC)
	include(windows_settings.cmake)
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
endif()

set(Boost_USE_MULTITHREADED ON)
find_package(Boost)
find_package(Freetype)
find_package(JPEG)
find_package(OpenGL)

include_directories( ${GAMEBOOST_SOURCE_DIR} )
include_directories( ${Boost_INCLUDE_DIRS} )
include_directories( ${FREETYPE_INCLUDE_DIRS} )
include_directories( ${JPEG_INCLUDE_DIR} )
include_directories( ${GAMEBOOST_SOURCE_DIR}/gb/deplib/NvTriStrip )

link_directories( ${GAMEBOOST_SOURCE_DIR}/linklib )
link_directories( ${Boost_LIBRARY_DIRS} )

add_subdirectory( gb )
add_subdirectory( test )
add_subdirectory( examples )

add_subdirectory( gb/deplib/NvTriStrip )
add_subdirectory( utils )