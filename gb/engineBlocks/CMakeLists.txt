project( gb-engineBlocks )
cmake_minimum_required(VERSION 2.8)

set( gb-engineBlocks_SOURCES
		BaseApplication.h BaseApplication.cpp
		CameraInput.h CameraInput.cpp
		EventTranslator.h EventTranslator.cpp
		GameApplication.h GameApplication.cpp
		InputBase.h InputBase.cpp 
		InputHandlerContainer.h InputHandlerMap.h
		SkyBox.h SkyBox.cpp
		StringFlyweight.h
)

applyPCH(gb-engineBlocks_SOURCES)

add_library( gb-engineBlocks STATIC ${gb-engineBlocks_SOURCES} )
