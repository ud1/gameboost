project( ShaderPreprocessor_Test )
cmake_minimum_required(VERSION 2.8)

#------ sources ------
set( ShaderPreprocessor_Test_SOURCES
		main.cpp
		)

find_package(Boost COMPONENTS thread date_time program_options system filesystem wave REQUIRED)

set(ShaderPreprocessor_Test_EXTRA_LIBS ${Boost_LIBRARIES})
set(ShaderPreprocessor_Test_GB_LIBS gb-graphics gb-fs gb-logging)

#------ target -----
add_executable( ShaderPreprocessor_Test ${ShaderPreprocessor_Test_SOURCES} )
target_link_libraries(ShaderPreprocessor_Test ${ShaderPreprocessor_Test_GB_LIBS} ${ShaderPreprocessor_Test_EXTRA_LIBS})
