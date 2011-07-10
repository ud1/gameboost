
#include "graph_api.h"
#include <gb/str/String.h>

namespace gb
{
	namespace graphics
	{

		namespace e_graph_api
		{	
	
	
		std::string tostr(const e value)
		{
		
		
		
		}
		
		bool fromstr(e& value, const std::string& str_arg)
		{
		   std::string str = str_arg;
		   gb::str::toUper(str);
		   
		   if(str == "SOFTWARE")
		   {
		   value = SOFTWARE;
		   return true;
		   }
		   
		   if(str == "DIRECTX")
		   {
		   value = DIRECTX;
		   return true;
		   }
		   
		   if(str == "OPENGL")
		   {
		   value = OPENGL;
		   return true;
		   }		   
		
		
			return false;
		}
	
	
		}
	}
}
