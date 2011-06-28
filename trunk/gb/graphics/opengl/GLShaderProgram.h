#pragma once

#include "GLDevice.h"
#include "GLAttribute.h"
#include "GLUniform.h"

namespace gb
{
	namespace graphics
	{
		namespace gl
		{

			class GLShaderProgram : public ShaderProgram
			{
			public:
				GL_SAFE_OBJECT_DELETION

				GLShaderProgram(GLDevice *device_);
				~GLShaderProgram();
				
				void attachShader(Shader *shd);
				void detachShader(Shader *shd);
				bool link();
				size_t getUniformsNumber();
				Uniform *getUniform(size_t i);
				size_t getAttributesNumber();
				Attribute *getAttribute(size_t i);
				
				bool activate_();
				void deactivate_();
				
			private:
				void clear();
				
				GLDevice *device;
				GLuint gl_program;
				std::vector<GLUniform *> uniforms;
				std::vector<GLAttribute *> attributes;
				bool is_linked;
			};
			
		}
	}
}
