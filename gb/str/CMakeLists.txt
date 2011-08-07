project( gb-str )
cmake_minimum_required(VERSION 2.8)

set( gb-str_SOURCES
		UnicodeHelpers.h
)

applyPCH(gb-str_SOURCES)

add_custom_target( gb-str SOURCES ${gb-str_SOURCES} )
