project( MT_Test )
cmake_minimum_required(VERSION 2.8)

#------ sources ------
set( MT_Test_SOURCES
		main.cpp
		)

find_package(Boost COMPONENTS thread date_time program_options system REQUIRED)

set(MT_Test_EXTRA_LIBS ${Boost_LIBRARIES})

#------ target -----
add_executable( MT_Test ${MT_Test_SOURCES} )
target_link_libraries(MT_Test gameboost ${MT_Test_EXTRA_LIBS})