

#pragma once

#include "d3d9_device.h"
#include "d3d9_buffer.h"

namespace gb
{

 namespace graphics
 {

  namespace d3d9
  {
   
  
	  class d3d9_attribute : Attribute {
	  public:
	  
		virtual ~d3d9_attribute() {}
	  
		virtual bool setVertexBuffer(Buffer *buf, const Layout *l) = 0;
		
		
	  };
  
 
  }
 }
}
