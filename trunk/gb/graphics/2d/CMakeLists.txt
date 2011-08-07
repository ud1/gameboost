project( gb-graphics2d )
cmake_minimum_required(VERSION 2.8)

set( gb-graphics2d_SOURCES
		GlyphCache.h
		ImageBlock.h
		rects.h
		RectsBuffer.h RectsBuffer.cpp
		TextRenderer.h TextRenderer.cpp	
		TextureAtlas.h TextureAtlas.cpp
)

applyPCH(gb-graphics2d_SOURCES)

add_library( gb-graphics2d STATIC ${gb-graphics2d_SOURCES} )
