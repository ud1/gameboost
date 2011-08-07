project( gb-resource )
cmake_minimum_required(VERSION 2.8)

set( gb-resource_SOURCES
		AsyncLoader.h
		CacheBase.h
		CacheNoGarbage.h
		LRUCache.h
		ResourceBase.h ResourceBase.cpp
)

applyPCH(gb-resource_SOURCES)

add_library( gb-resource STATIC ${gb-resource_SOURCES} )
