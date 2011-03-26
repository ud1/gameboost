project( StringFlyweight_Test )
cmake_minimum_required(VERSION 2.8)

#------ sources ------
set( StringFlyweight_Test_SOURCES
		main.cpp
		)

#------ target -----
add_executable( StringFlyweight_Test ${StringFlyweight_Test_SOURCES} )
target_link_libraries(StringFlyweight_Test gameboost)
