project( gb-windowSubsystem )
cmake_minimum_required(VERSION 2.8)

set( gb-windowSubsystem_SOURCES
		Input.h
		KeyCodes.h
		Window.h
		WindowManager.h
		linux/WindowManager.cpp win32/WindowManager.cpp
)

source_group( linux REGULAR_EXPRESSION "linux/" )
source_group( win32 REGULAR_EXPRESSION "win32/" )

add_library( gb-windowSubsystem STATIC ${gb-windowSubsystem_SOURCES} )
