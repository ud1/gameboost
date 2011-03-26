project( NvTriStrip )
cmake_minimum_required(VERSION 2.8)

set( NvTriStrip_SOURCES
	NvTriStrip.h
	NvTriStrip.cpp
	NvTriStripObjects.h
	NvTriStripObjects.cpp
	VertexCache.h
)

add_library( NvTriStrip STATIC ${NvTriStrip_SOURCES} )