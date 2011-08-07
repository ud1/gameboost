project( terrain_builder )
cmake_minimum_required(VERSION 2.8)

#------ sources ------
set( terrain_builder_SOURCES
	main.cpp
)

find_package(Boost COMPONENTS program_options filesystem REQUIRED)
find_package(JPEG)
set(terrain_builder_EXTRA_LIBS ${Boost_LIBRARIES} ${JPEG_LIBRARY})
set(terrain_builder_GB_LIBS gb-fs gb-terrain gb-math gb-loaders gb-containers gb-logging)

#------ target -----
add_executable( terrain_builder ${terrain_builder_SOURCES} )
target_link_libraries(terrain_builder ${terrain_builder_GB_LIBS} ${terrain_builder_EXTRA_LIBS})
