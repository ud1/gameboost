

project( Font_Test )
cmake_minimum_required(VERSION 2.8)

#------ sources ------
set( Font_Test_SOURCES
		main.cpp
		)

set(Font_Test_GB_LIBS gb-fs gb-loaders gb-containers gb-graphics gb-base gb-logging)

#------ target -----
add_executable( Font_Test ${Font_Test_SOURCES} )
target_link_libraries(Font_Test ${Font_Test_GB_LIBS} ${FREETYPE_LIBRARIES})