
project( utf8checker )
cmake_minimum_required(VERSION 2.8)

#------ sources ------
set( utf8checker_SOURCES
	main.cpp
)

find_package(Boost COMPONENTS filesystem REQUIRED)
set(utf8checker_EXTRA_LIBS ${Boost_LIBRARIES})
set(utf8checker_GB_LIBS gb-base gb-fs gb-logging)

#------ target -----
add_executable( utf8checker ${utf8checker_SOURCES} )
target_link_libraries(utf8checker ${utf8checker_GB_LIBS} ${utf8checker_EXTRA_LIBS})
