
#include "Quad.h"

#pragma  message("!!! НАДО  ПРОВЕРИТЬ"  __FILE__)

namespace gb
{

namespace graphics
{


     const  QuadVertex_s  g_st_quad_vertexes[] =  
  {
	  {  -1.0f,    1.0f,   0.0f,    0.0f,  0.0f, },  
	  {  -1.0f,   -1.0f,   0.0f,    0.0f,  1.0f, },
	  {   1.0f,    1.0f,   0.0f,    1.0f,  0.0f, },
	  {   1.0f,   -1.0f,   0.0f,    1.0f,  1.0f, },
	  {   1.0f,    1.0f,   0.0f,    1.0f,  0.0f, },
	  {  -1.0f,   -1.0f,   0.0f,    0.0f,  1.0f, },

  };

    const uint16_t  g_st_quad_indexes[] = { 0,  1,  2,  3,  4,  5 };


void GetQuadVertexes(
					const QuadVertex_s** ppOutVertxs, 
					uint32_t* pOutNumVertex, 
					const  uint16_t** ppOutIndexes,
					uint32_t* pOutNumIndexes)
{

    *ppOutVertxs = g_st_quad_vertexes;
	*pOutNumVertex =   sizeof(g_st_quad_vertexes)  /  sizeof(CubeVertex_s) ;

	*ppOutIndexes = g_st_quad_indexes;
	*pOutNumIndexes =  sizeof(g_st_quad_indexes) / sizeof(uint16_t);

}


}
// end namespace
}
// end namespace

// end file