project( GBTEST )
cmake_minimum_required(VERSION 2.8)

if (MSVC)
	add_definitions( -D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS -D_WIN32_WINNT=0x0501 /MP )
endif()

#------ sources ------
set( GBTEST_SOURCES
		main.cpp
		test_Path.cpp
		test_String.cpp
		)

# source_group( tests REGULAR_EXPRESSION "test_" )

#------ additional includes ------
include_directories( ${GAMEBOOST_SOURCE_DIR} )
include_directories( ${GAMEBOOST_SOURCE_DIR}/gb/deplib/boost )
include_directories( ${GAMEBOOST_SOURCE_DIR}/gb/deplib/utfcpp.sourceforge.net )

include_directories( ${GBTEST_SOURCE_DIR}/deplib/gtest-1.5.0/include )

link_directories( ${GAMEBOOST_SOURCE_DIR}/linklib )
link_directories( ${GAMEBOOST_SOURCE_DIR}/gb/deplib/boost/stage/lib )

link_libraries( gtest gtest_main gameboost )

if (MSVC)
	set_source_files_properties( test_pch.cpp PROPERTIES COMPILE_FLAGS "/Yctest_pch.h" )
	foreach( src_file ${GBTEST_SOURCES} )
		set_source_files_properties( ${src_file} PROPERTIES COMPILE_FLAGS "/Yutest_pch.h" )
	endforeach( src_file ${GBTEST_SOURCES} )
	list( APPEND GBTEST_SOURCES test_pch.cpp test_pch.h )
endif()

#------ target -----
add_executable( gameboost_test ${GBTEST_SOURCES} )
add_dependencies( gameboost_test gameboost )
