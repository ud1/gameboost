

#pragma once
#include <gb/base/Types.h>

namespace gb
{

namespace graphics
{

  struct CubeVertex_s
  {
    float x,  y,  z;
	float nx, ny, nz;
    float u, v;
  
  };


  void GetCubeVertexes(const CubeVertex_s** ppOutVertxs, 
					   uint32_t* pOutNumVertex, 
					   const uint16_t** ppOutIndexes,
					   uint32_t* pOutNumIndexes	   
					   );

}

}

// end file