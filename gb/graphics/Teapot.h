/** \file
 
  \brief Сеть чайника.
 
 
*/

#include <gb/base/Types.h>

#pragma once

namespace gb
{
	namespace graphics
	{
	
	struct teapotVertex_s
	{
	   float x, y, z,    
		     nx, ny, nz,    
		     u, v;	
	};
	
	void getTeapotMeshData(
                teapotVertex_s**  ppOutVertex, 
				uint32_t*         pOutNumVertex,
				uint16_t**        ppOutIndexes,
				uint32_t          pOutNumIndexes
				);
	
	
	
	}
}

