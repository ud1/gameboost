#pragma once
#include <gb/base/IRefCountable.h>

namespace gb
{
	namespace graphics
	{
		
		class Shader : public base::IRefCountable
		{
		public:
			virtual void setSource(const char *str) = 0;
			virtual bool compile() = 0;
		};
		
		typedef base::RefCntHolder<Shader> PShader;
		
	}
}
