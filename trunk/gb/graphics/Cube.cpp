
#include "Cube.h"

#pragma  message("!!! НАДО  ПРОВЕРИТЬ"  __FILE__)

namespace gb
{

namespace graphics
{
 
	static const CubeVertex_s    g_vertexes[]  = 
	{
		{  -1.0f,    1.0f,   -1.0f,       0.0f,   0.0f, },
		{   1.0f,    1.0f,   -1.0f,       1.0f,   0.0f, },
		{   1.0f,   -1.0f,   -1.0f,       1.0f,   1.0f, },
		{  -1.0f,   -1.0f,   -1.0f,       0.0f,   1.0f, },

		{  -1.0f,    1.0f,    1.0f,       0.0f,   0.0f, },
		{  -1.0f,    1.0f,   -1.0f,       1.0f,   0.0f, },
		{  -1.0f,   -1.0f,   -1.0f,       1.0f,   1.0f, },
		{  -1.0f,   -1.0f,    1.0f,       0.0f,   1.0f, },

		{   1.0f,    1.0f,    1.0f,       0.0f,   0.0f, },
		{  -1.0f,    1.0f,    1.0f,       1.0f,   0.0f, },
		{  -1.0f,   -1.0f,    1.0f,       1.0f,   1.0f, },
		{   1.0f,   -1.0f,    1.0f,       0.0f,   1.0f, },

		{   1.0f,    1.0f,   -1.0f,       0.0f,   0.0f, },
		{   1.0f,    1.0f,    1.0f,       1.0f,   0.0f, },
		{   1.0f,   -1.0f,    1.0f,       1.0f,   1.0f, },
		{   1.0f,   -1.0f,   -1.0f,       0.0f,   1.0f, },

		{  -1.0f,    1.0f,    1.0f,       0.0f,   0.0f, },
		{   1.0f,    1.0f,    1.0f,       1.0f,   0.0f, },
		{   1.0f,    1.0f,   -1.0f,       1.0f,   1.0f, },
		{  -1.0f,    1.0f,   -1.0f,       0.0f,   1.0f, },

		{   1.0f,   -1.0f,   -1.0f,       0.0f,   0.0f, },
		{   1.0f,   -1.0f,    1.0f,       1.0f,   0.0f, },
		{  -1.0f,   -1.0f,    1.0f,       1.0f,   1.0f, },
		{  -1.0f,   -1.0f,   -1.0f,       0.0f,   1.0f, }
	};

	static const uint16_t      g_indexes[]   = 
	{
		0,  1,  2,  
		2,  3,  0,
		4,  5,  6,  
		6,  7,  4,
		8,  9, 10, 
		10, 11,  8,
		12, 13, 14, 
		14, 15, 12,
		16, 17, 18, 
		18, 19, 16,
		20, 21, 22, 
		22, 23, 20
	};



void GetCubeVertexes(const CubeVertex_s** ppOutVertxs, 
					   uint32_t* pOutNumVertex, 
					  const uint16_t** ppOutIndexes,
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