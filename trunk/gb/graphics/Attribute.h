#pragma once

#include <string>

#include "Buffer.h"
#include "Layout.h"

namespace gb
{
	namespace graphics
	{
		
		class Attribute
		{
		public:
			const char *getName() const {return name.c_str();}
			
			virtual bool setVertexBuffer(Buffer *buf, const Layout *l) = 0;
			
		protected:
			std::string name;
		};
		
	}
}
