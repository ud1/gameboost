project( gb-graphics )
cmake_minimum_required(VERSION 2.8)

set( gb-graphics_SOURCES
		Attribute.h
		Buffer.h
		Device.h Device.cpp
		Font.h
		FontFreeType.h FontFreeType.cpp
		Layout.h
		RenderState.h
		Shader.h
		ShaderPreprocessor.h ShaderPreprocessor.cpp
		ShaderProgram.h
		Texture.h
		Uniform.h
		UniformServer.h UniformServer.cpp
)

applyPCH(gb-graphics_SOURCES)

add_subdirectory(opengl)
add_subdirectory(2d)

add_library( gb-graphics STATIC ${gb-graphics_SOURCES} )
