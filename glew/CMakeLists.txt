project( glew )
cmake_minimum_required(VERSION 2.8)

set(glew_dir glew-1.6.0)
include_directories( ${glew_dir}/include )

add_definitions(-D_CRT_SECURE_NO_WARNINGS -DGLEW_STATIC)
#------ sources ------
set( glew_SOURCES
	${glew_dir}/include/GL/glew.h
	${glew_dir}/include/GL/glxew.h
	${glew_dir}/include/GL/wglew.h
	${glew_dir}/src/glew.c
)

add_library( glew ${glew_SOURCES} )

set_target_properties(glew PROPERTIES
	DEBUG_POSTFIX "${LIB_TARGET_SUFFIX}_d"
)

install( TARGETS glew DESTINATION ${STATIC_DEP_LIBS_DIR} )