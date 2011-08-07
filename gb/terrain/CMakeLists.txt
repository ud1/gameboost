project( gb-terrain )
cmake_minimum_required(VERSION 2.8)

set( gb-terrain_SOURCES
		ElevationData.h 
		IndexBuffer.h IndexBuffer.cpp
)

applyPCH(gb-terrain_SOURCES)

add_library( gb-terrain STATIC ${gb-terrain_SOURCES} )
