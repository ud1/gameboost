project( GBTEST )
cmake_minimum_required(VERSION 2.8)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GBTEST_SOURCE_DIR}/bin CACHE PATH "Single Directory for all Executables." )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${GBTEST_SOURCE_DIR}/bin CACHE PATH "Single Directory for all Executables." )

# включим GameBoost в зависимости
add_subdirectory( deplib/gtest-1.5.0 )
add_subdirectory( ../src ${GBTEST_SOURCE_DIR}/.build_gameboost )

if (MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS -D_WIN32_WINNT=0x0501 /MP )
endif()

#------ sources ------
set( GBTEST_SOURCES
		main.cpp
		test_path.cpp
		)

source_group( tests REGULAR_EXPRESSION "test_" )

#------ additional includes ------
include_directories( ${GAMEBOOST_SOURCE_DIR} )
include_directories( ${GAMEBOOST_SOURCE_DIR}/deplib/boost )
include_directories( ${GAMEBOOST_SOURCE_DIR}/deplib/utfcpp.sourceforge.net )

include_directories( ${GBTEST_SOURCE_DIR}/deplib/gtest-1.5.0/include )

if (MSVC)
	set_source_files_properties( precompiled_headers.cpp PROPERTIES COMPILE_FLAGS "/Ycprecompiled_headers.h" )
	foreach( src_file ${GBTEST_SOURCES} )
		set_source_files_properties( ${src_file} PROPERTIES COMPILE_FLAGS "/Yuprecompiled_headers.h" )
	endforeach( src_file ${GBTEST_SOURCES} )
	list( APPEND GBTEST_SOURCES precompiled_headers.cpp precompiled_headers.h )
endif()

#------ target -----
add_library( gbUnitTest STATIC ${GBTEST_SOURCES} )
add_dependencies( gbUnitTest gtest )
