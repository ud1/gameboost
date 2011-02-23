project( GAMEBOOST )
cmake_minimum_required(VERSION 2.8)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GAMEBOOST_SOURCE_DIR}/bin CACHE PATH "Single Directory for all Executables." )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${GAMEBOOST_SOURCE_DIR}/bin CACHE PATH "Single Directory for all Executables." )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${GAMEBOOST_SOURCE_DIR}/linklib CACHE PATH "Single Directory for all static libraries." )

set(CMAKE_FIND_LIBRARY_PREFIXES "lib")
if (MSVC)
	set(BOOST_ROOT "C:/boost")
	set(BOOST_LIBRARYDIR "C:/boost/stage/lib")
endif()
set(Boost_USE_MULTITHREADED ON)
find_package(Boost)

include_directories( ${GAMEBOOST_SOURCE_DIR} )
include_directories( ${Boost_INCLUDE_DIRS} )

link_directories( ${GAMEBOOST_SOURCE_DIR}/linklib )
link_directories( ${Boost_LIBRARY_DIRS} )

add_subdirectory( test/deplib/gtest-1.5.0 )
add_subdirectory( gb )
add_subdirectory( test )
add_subdirectory( lib )