
project( Loaders_Test )
cmake_minimum_required(VERSION 2.8)

#------ sources ------
set( Loaders_Test_SOURCES
		main.cpp
		)

#find_package(JPEG)
#set(Loaders_Test_EXTRA_LIBS ${JPEG_LIBRARY})

#------ target -----
add_executable( Loaders_Test ${Loaders_Test_SOURCES} )
target_link_libraries(Loaders_Test gameboost ${Loaders_Test_EXTRA_LIBS})