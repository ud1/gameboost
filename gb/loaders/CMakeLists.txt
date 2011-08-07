project( gb-loaders )
cmake_minimum_required(VERSION 2.8)

set( gb-loaders_SOURCES
		images/ImageLoader.h
		images/BmpLoader.h images/BmpLoader.cpp
		images/JpegLoader.h images/JpegLoader.cpp
		models/Obj.h models/Obj.cpp
)

applyPCH(gb-loaders_SOURCES)

source_group( images REGULAR_EXPRESSION "images/" )
source_group( models REGULAR_EXPRESSION "models/" )

add_library( gb-loaders STATIC ${gb-loaders_SOURCES} )
