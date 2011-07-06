
#pragma once
#include <gb/base/Types.h>

namespace gb
{

namespace graphics
{

  struct QuadVertex_s
  {
	  float x, y, z,
	        u, v;
  };

  
    void GetQuadVertexes(
			const QuadVertex_s** ppOutVertxs, 
			uint32_t* pOutNumVertex, 
			const uint16_t** ppOutIndexes,
			uint32_t* pOutNumIndexes	   
					   );


}
// end namespace
}
// end namespace


// end file