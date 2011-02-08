project( GAMEBOOST )
cmake_minimum_required(VERSION 2.8)

#------ sources ------
set( GAMEBOOST_SOURCES base/Atomic.h
                       base/IRefCountable.h
                       base/SimpleLog.cpp
                       base/SimpleLog.h
                       base/singleton.h

                       io/FileHD.cpp
                       io/FileHD.h
                       io/FileRAM.cpp
                       io/FileRAM.h
                       io/IFile.h

                       math/vector.h

                       Config.h
                       )

source_group( base REGULAR_EXPRESSION "base/" )
source_group( io REGULAR_EXPRESSION "io/" )
source_group( math REGULAR_EXPRESSION "math/" )

#------ additional includes ------
include_directories( ${GAMEBOOST_SOURCE_DIR} )

if (MSVC)
    set_source_files_properties( precompiled_headers.cpp PROPERTIES COMPILE_FLAGS "/Ycprecompiled_headers.h" )
    foreach( src_file ${GAMEBOOST_SOURCES} )
        set_source_files_properties( ${src_file} PROPERTIES COMPILE_FLAGS "/Yuprecompiled_headers.h" )
    endforeach( src_file ${GAMEBOOST_SOURCES} )
    list( APPEND GAMEBOOST_SOURCES precompiled_headers.cpp precompiled_headers.h )
endif (MSVC)

#------ target -----
add_library( gameboost STATIC ${GAMEBOOST_SOURCES} )
