project( GAMEBOOST )
cmake_minimum_required(VERSION 2.8)

if (MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS -D_WIN32_WINNT=0x0501 /MP )
endif()

#------ sources ------
set( GAMEBOOST_SOURCES
		base/Atomic.h
		base/IRefCountable.h
		base/SimpleLog.cpp  base/SimpleLog.h
		base/Timer.h  base/Timer.cpp
		base/String.cpp  base/String.h
		base/Types.h

		io/FileHD.cpp  io/FileHD.h
		io/FileRAM.cpp  io/FileRAM.h
		io/IFile.h

		mt/Job.h mt/Job.cpp mt/JobScheduler.h mt/JobScheduler.cpp mt/ThreadPolicy.h mt/ThreadPolicy.cpp

		math/vector.h

		system/path.h  system/path.cpp  system/path_linux.cpp  system/path_win32.cpp  system/path_macosx.cpp

		Config.h )

source_group( base REGULAR_EXPRESSION "base/" )
source_group( io REGULAR_EXPRESSION "io/" )
source_group( math REGULAR_EXPRESSION "math/" )
source_group( system REGULAR_EXPRESSION "system/" )

#------ additional includes ------
include_directories( ${GAMEBOOST_SOURCE_DIR} )
include_directories( ${GAMEBOOST_SOURCE_DIR}/deplib/boost )
include_directories( ${GAMEBOOST_SOURCE_DIR}/deplib/utfcpp.sourceforge.net )

if (MSVC)
	set_source_files_properties( pch.cpp PROPERTIES COMPILE_FLAGS "/Ycpch.h" )
	foreach( src_file ${GAMEBOOST_SOURCES} )
		set_source_files_properties( ${src_file} PROPERTIES COMPILE_FLAGS "/Yupch.h" )
	endforeach( src_file ${GAMEBOOST_SOURCES} )
	list( APPEND GAMEBOOST_SOURCES pch.cpp pch.h )
endif()

#------ target -----
add_library( gameboost STATIC ${GAMEBOOST_SOURCES} )
