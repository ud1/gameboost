

#pragma once
#include <string>

namespace gb
{
	namespace graphics
	{
		//! \brief graphic API decl
		namespace e_graph_api
		{

			enum e
			{

				 SOFTWARE,
				 
				 #ifdef WIN32
				 DIRECTX,
				 #endif
				 
				 OPENGL,
			};
			
			std::string tostr(const e);
			bool fromstr(e&, const std::string&);
			
		}

		
		#ifdef WIN32
		
		namespace e_directx
		{
			enum e
			{
				UNDEFINED = 0,
			
				DIRECTX9,
				DIRECTX10,
				DIRECTX11
			
			};
		}
		
		#endif
	 


	}
}
