project( MT_Test )
cmake_minimum_required(VERSION 2.8)

#------ sources ------
set( MT_Test_SOURCES
		main.cpp
		)

set(Boost_USE_MULTITHREADED ON)
include_directories(${Boost_INCLUDE_DIR})
include_directories( C:/Boost )
find_package(Boost COMPONENTS thread date_time program_options system REQUIRED)

include_directories( ${GAMEBOOST_SOURCE_DIR} )
include_directories( ${GAMEBOOST_SOURCE_DIR}/gb/deplib/boost )
set(MT_Test_EXTRA_LIBS ${Boost_LIBRARIES})

link_directories( ${GAMEBOOST_SOURCE_DIR}/linklib )

# Библиотеки буста ожидаются либо в gb/deplib/boost/stage/lib либо в C:/Boost/lib/vs2010_32(или _64)
link_directories( ${GAMEBOOST_SOURCE_DIR}/gb/deplib/boost/stage/lib )
link_directories( C:/Boost/lib/vs2010_32 C:/Boost/lib/vs2010_64 )

#------ target -----
add_executable( MT_Test ${MT_Test_SOURCES} )
target_link_libraries(MT_Test gameboost ${MT_Test_EXTRA_LIBS})