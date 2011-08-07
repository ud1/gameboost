project( gb-base )
cmake_minimum_required(VERSION 2.8)

set( gb-base_SOURCES
		Atomic.h
		Guid.h
		Debug.h
		IRefCountable.h
		Timer.h  Timer.cpp
		Types.h
		Factory.h 
		Atlas.h Atlas.cpp
		alignedMalloc.h alignedMalloc.cpp
		Variable.h VariableUpdater.h
		VariableContainer.h VariableContainer.cpp
		OnDeleteSignalingObject.h
		TailedType.h
		
		t/clamp.h t/debug_cast.h
)

add_library( gb-base STATIC ${gb-base_SOURCES} )
