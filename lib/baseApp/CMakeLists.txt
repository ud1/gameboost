
project( BaseApp_Test )
cmake_minimum_required(VERSION 2.8)

#------ sources ------
set( BaseApp_Test_SOURCES
		main.cpp
		)

find_package(Boost COMPONENTS program_options REQUIRED)
set(BaseApp_EXTRA_LIBS ${Boost_LIBRARIES} GL X11 GLEW)

#------ target -----
add_executable( BaseApp_Test ${BaseApp_Test_SOURCES} )
target_link_libraries(BaseApp_Test gameboost yaml-cpp ${BaseApp_EXTRA_LIBS})