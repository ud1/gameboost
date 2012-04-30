project( LIBGAMEBOOST )
cmake_minimum_required(VERSION 2.8)

if (MSVC)
	# Параметры компиляции для MSVC
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS -D_WIN32_WINNT=0x0501 -D_USE_MATH_DEFINES -DGLEW_STATIC /MP )
else()
	# для прочих компиляторов
	add_definitions(-pedantic -Wall -std=c++0x)
endif()

# Исходники
set( GAMEBOOST_SOURCES
		Config.h
)

macro(applyPCH sources)
if (MSVC)
	set_source_files_properties( pch.cpp PROPERTIES COMPILE_FLAGS "/Ycpch.h" )
	foreach( src_file ${sources} )
		# Только для *.cpp файлов
		if (src_file MATCHES ".*[.]cpp$")
			set_source_files_properties( ${src_file} PROPERTIES COMPILE_FLAGS "/Yupch.h /FIpch.h" )
		endif (src_file MATCHES ".*[.]cpp$")
	endforeach( src_file ${sources} )
	list( APPEND sources pch.cpp pch.h )
endif()
endmacro(applyPCH)

add_subdirectory(base)
add_subdirectory(containers)
add_subdirectory(engineBlocks)
add_subdirectory(fs)
add_subdirectory(graphics)
add_subdirectory(loaders)
add_subdirectory(logging)
add_subdirectory(math)
add_subdirectory(mt)
add_subdirectory(resource)
add_subdirectory(str)
add_subdirectory(terrain)
add_subdirectory(windowSubsystem)
add_subdirectory(meta)
add_subdirectory(xml)

#------ target -----
add_custom_target( gameboost SOURCES ${GAMEBOOST_SOURCES} )
