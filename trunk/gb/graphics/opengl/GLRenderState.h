#pragma once

#include <gb/graphics/RenderState.h>

#include <boost/function.hpp>

namespace gb
{
	namespace graphics
	{
		namespace gl
		{
			
			class GLRenderState : public RenderState
			{
			public:
				bool setSource(const char *code);
				void apply();
				
			private:
				typedef boost::function< void () > stateFunc;
				std::vector<stateFunc> stateFunctions;
			};
			
		}
	}
}
