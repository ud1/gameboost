project( GBTEST )
cmake_minimum_required(VERSION 2.8)

if (MSVC)
	add_definitions( -D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS -D_WIN32_WINNT=0x0501 /MP )
endif()

#------ sources ------
set( GBTEST_SOURCES
		main.cpp
		#test_path.cpp
		#test_String.cpp
		test_Random.cpp
		)

find_package(Boost COMPONENTS system REQUIRED)
# source_group( tests REGULAR_EXPRESSION "test_" )

#------ additional includes ------
include_directories( ${GAMEBOOST_SOURCE_DIR}/gb/deplib/utfcpp.sourceforge.net )
include_directories( ${GBTEST_SOURCE_DIR}/deplib/gtest-1.5.0/include )

link_libraries( gtest gtest_main gameboost  )

if (MSVC)
	set_source_files_properties( pch_test.cpp PROPERTIES COMPILE_FLAGS "/Ycpch_test.h" )
	foreach( src_file ${GBTEST_SOURCES} )
		# Только для *.cpp файлов
		if (src_file MATCHES ".*[.]cpp$")
			set_source_files_properties( ${src_file} PROPERTIES COMPILE_FLAGS "/Yupch_test.h" )
		endif (src_file MATCHES ".*[.]cpp$")
	endforeach( src_file ${GBTEST_SOURCES} )
	list( APPEND GBTEST_SOURCES pch_test.cpp pch_test.h )
endif()

#------ target -----
add_executable( gameboost_test ${GBTEST_SOURCES} )
add_dependencies( gameboost_test gameboost )
