
#include "Quad.h"

#pragma  message("!!! НАДО  ПРОВЕРИТЬ"  __FILE__)

namespace gb
{

namespace graghics
{


  static  const  QuadVertex_s  g_vertexes[] =  
  {
	  {  -1.0f,    1.0f,   0.0f,    0.0f,  0.0f, },  
	  {  -1.0f,   -1.0f,   0.0f,    0.0f,  1.0f, },
	  {   1.0f,    1.0f,   0.0f,    1.0f,  0.0f, },
	  {   1.0f,   -1.0f,   0.0f,    1.0f,  1.0f, },
	  {   1.0f,    1.0f,   0.0f,    1.0f,  0.0f, },
	  {  -1.0f,   -1.0f,   0.0f,    0.0f,  1.0f, },

  };

  static const uint16_t  g_indexes[] = { 0,  1,  2,  3,  4,  5 };


void GetQuadVertexes(const CubeVertex_s** ppOutVertxs, 
					   uint32_t* pOutNumVertex, 
					 const  uint16_t** ppOutIndexes,
					   uint32_t* pOutNumIndexes)
{

    *ppOutVertxs = g_vertexes;
	*pOutNumVertex =   sizeof(g_vertexes)  /  sizeof(CubeVertex_s) ;

	*ppOutIndexes = g_indexes;
	*pOutNumIndexes =  sizeof(g_indexes) / sizeof(uint16_t);

}


}
// end namespace
}
// end namespace

// end file