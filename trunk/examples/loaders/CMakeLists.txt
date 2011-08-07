
project( Loaders_Test )
cmake_minimum_required(VERSION 2.8)

#------ sources ------
set( Loaders_Test_SOURCES
		main.cpp
		)

find_package(JPEG)
set(Loaders_Test_EXTRA_LIBS ${JPEG_LIBRARY})
set(Loaders_Test_GB_LIBS gb-fs gb-loaders gb-containers gb-logging)

#------ target -----
add_executable( Loaders_Test ${Loaders_Test_SOURCES} )
target_link_libraries(Loaders_Test ${Loaders_Test_GB_LIBS} ${Loaders_Test_EXTRA_LIBS})