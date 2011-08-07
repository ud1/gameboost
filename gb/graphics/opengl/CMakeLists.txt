project( gb-opengl )
cmake_minimum_required(VERSION 2.8)

set( gb-opengl_SOURCES
		GLAttribute.h GLAttribute.cpp
		GLBuffer.h GLBuffer.cpp
		GLDevice.h GLDevice.cpp
		GLRenderState.h GLRenderState.cpp
		GLShader.h GLShader.cpp
		GLShaderProgram.h GLShaderProgram.cpp
		GLTexture.h GLTexture.cpp
		GLUniform.h GLUniform.cpp
		GLWindowRenderTarget.h GLWindowRenderTarget.cpp		
)

applyPCH(gb-opengl_SOURCES)

add_library( gb-opengl STATIC ${gb-opengl_SOURCES} )
