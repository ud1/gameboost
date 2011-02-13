project( MT_Test )
cmake_minimum_required(VERSION 2.8)

#------ sources ------
set( MT_Test_SOURCES
		main.cpp
		)

set(Boost_USE_MULTITHREADED ON)
include_directories(${Boost_INCLUDE_DIRS})
find_package(Boost COMPONENTS thread date_time program_options system REQUIRED)

include_directories( ${GAMEBOOST_SOURCE_DIR} )
include_directories( ${GAMEBOOST_SOURCE_DIR}/gb/deplib/boost )
set(MT_Test_EXTRA_LIBS ${Boost_LIBRARIES})

link_directories( ${GAMEBOOST_SOURCE_DIR}/linklib )

#------ target -----
add_executable( MT_Test ${MT_Test_SOURCES} )
target_link_libraries(MT_Test gameboost ${MT_Test_EXTRA_LIBS})