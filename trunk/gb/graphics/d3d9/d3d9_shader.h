


#pragma once

#include "../Shader.h"

namespace gb
{

 namespace graphics
 {

  namespace d3d9
  {
  
  class d3d9_shader : Shader {
  public:
  
	virtual ~d3d9_shader() {}
	
	
			virtual void setSource(const char *str) 
			{
			assert(false);
			}
			
			virtual bool compile()
			{
			assert(false);
			}
  
  
  
  
  };
  
  
  
  
  
  
  
  
  
  
  }
 }
}
