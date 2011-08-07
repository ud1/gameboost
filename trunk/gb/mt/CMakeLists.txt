project( gb-multithread )
cmake_minimum_required(VERSION 2.8)

set( gb-multithread_SOURCES
		Job.h Job.cpp
		JobScheduler.h JobScheduler.cpp
		syncPrimitives.h
		ThreadPolicy.h ThreadPolicy.cpp
)

applyPCH(gb-multithread_SOURCES)

add_library( gb-multithread STATIC ${gb-multithread_SOURCES} )
