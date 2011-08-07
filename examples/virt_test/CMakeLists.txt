project( Virt_Test )
cmake_minimum_required(VERSION 2.8)

#------ sources ------
set( Virt_Test_SOURCES
	main.cpp
	test.cpp
	virt_test.h
	virt_test.cpp
)

#------ target -----
add_executable( Virt_Test ${Virt_Test_SOURCES} )
target_link_libraries(Virt_Test gb-base )
