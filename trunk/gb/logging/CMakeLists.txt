project( gb-logging )
cmake_minimum_required(VERSION 2.8)

set( gb-logging_SOURCES
		Logger.h Logger.cpp
)

applyPCH(gb-logging_SOURCES)

add_library( gb-logging STATIC ${gb-logging_SOURCES} )
