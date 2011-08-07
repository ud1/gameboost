project( gb-containers )
cmake_minimum_required(VERSION 2.8)

set( gb-containers_SOURCES
		alphaConvertion.h
		colorConvert.h
		Image.h Image.cpp
		Mesh.h Mesh.cpp
		PixelFormat.h PixelFormat.cpp
)

applyPCH(gb-containers_SOURCES)

add_library( gb-containers STATIC ${gb-containers_SOURCES} )
