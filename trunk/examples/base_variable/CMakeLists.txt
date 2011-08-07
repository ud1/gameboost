
project( base_variable_test )
cmake_minimum_required(VERSION 2.8)

#------ sources ------
set( base_variable_test_SOURCES
		main.cpp
		)

#------ target -----
add_executable( base_variable_test ${base_variable_test_SOURCES} )
target_link_libraries(base_variable_test gb-base)
