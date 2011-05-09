project( terrain_builder )
cmake_minimum_required(VERSION 2.8)

#------ sources ------
set( terrain_builder_SOURCES
	main.cpp
)

find_package(Boost COMPONENTS program_options filesystem REQUIRED)
set(terrain_builder_EXTRA_LIBS ${Boost_LIBRARIES})

#------ target -----
add_executable( terrain_builder ${terrain_builder_SOURCES} )
target_link_libraries(terrain_builder gameboost ${terrain_builder_EXTRA_LIBS})
