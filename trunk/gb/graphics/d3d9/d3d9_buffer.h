


#pragma once

#include "d3d9_device.h"

namespace gb
{

 namespace graphics
 {

  namespace d3d9
  {
  
  
  
	class d3d9_buffer : Buffer {
	public:



		virtual void* map(size_t offset_bytes, size_t size_in_bytes) 
		{
		assert(false);  return NULL;
		}

		virtual void unmap()
		{
		assert(false);
		}

		virtual void subData(size_t offset_bytes, size_t size_in_bytes, void *data)
		{
		assert(false);
		}




	};
 
  
  }
 }
}
