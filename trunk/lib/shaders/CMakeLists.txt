project( ShaderPreprocessor_Test )
cmake_minimum_required(VERSION 2.8)

#------ sources ------
set( ShaderPreprocessor_Test_SOURCES
		main.cpp
		)

set(Boost_USE_MULTITHREADED ON)
include_directories(${Boost_INCLUDE_DIRS})
find_package(Boost COMPONENTS thread date_time program_options system filesystem wave REQUIRED)

include_directories( ${GAMEBOOST_SOURCE_DIR} )
include_directories( ${GAMEBOOST_SOURCE_DIR}/gb/deplib/boost )
set(ShaderPreprocessor_Test_EXTRA_LIBS ${Boost_LIBRARIES})

link_directories( ${GAMEBOOST_SOURCE_DIR}/linklib )

#------ target -----
add_executable( ShaderPreprocessor_Test ${ShaderPreprocessor_Test_SOURCES} )
target_link_libraries(ShaderPreprocessor_Test gameboost ${ShaderPreprocessor_Test_EXTRA_LIBS})
