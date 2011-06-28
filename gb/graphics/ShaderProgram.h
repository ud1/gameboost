#pragma once
#include <gb/base/IRefCountable.h>

#include "Attribute.h"
#include "Shader.h"
#include "Uniform.h"

namespace gb
{
	namespace graphics
	{
		
		class ShaderProgram : public base::IRefCountable
		{
		public:
			virtual void attachShader(Shader *shd) = 0;
			virtual void detachShader(Shader *shd) = 0;
			virtual bool link() = 0;
			virtual size_t getUniformsNumber() = 0;
			virtual Uniform *getUniform(size_t i) = 0;
			virtual size_t getAttributesNumber() = 0;
			virtual Attribute *getAttribute(size_t i) = 0;
		};
		
		typedef base::RefCntHolder<ShaderProgram> PShaderProgram;
		
	}
}