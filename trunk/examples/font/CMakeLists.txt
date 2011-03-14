

project( Font_Test )
cmake_minimum_required(VERSION 2.8)

#------ sources ------
set( Font_Test_SOURCES
		main.cpp
		)

#------ target -----
add_executable( Font_Test ${Font_Test_SOURCES} )
target_link_libraries(Font_Test gameboost ${FREETYPE_LIBRARIES})