project( gb-fs )
cmake_minimum_required(VERSION 2.8)

set( gb-fs_SOURCES
		FileSystem.h
		Helpers.cpp Helpers.h
		LocalFS.h LocalFS.cpp
		SeekType.h 
		Stream.h
)

applyPCH(gb-fs_SOURCES)

add_library( gb-fs STATIC ${gb-fs_SOURCES} )
