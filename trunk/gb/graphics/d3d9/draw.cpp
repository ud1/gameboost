

#if ( defined(GB_D3D9) && defined(WIN32) )

#include <gb/graphics/d3d9/draw.h>



namespace gb       
{
namespace graphics 
{
namespace d3d9     
{
namespace draw     
{
	
//======================================================================
	
//======================================================================
GB_D3D9_API HRESULT drawMeshPrimitiveCube1x1Mem(IDirect3DDevice9* pdevice)
{
	if (!pdevice) return E_FAIL;
	HRESULT hr =0;

#define MESH_VERTEX_FVF  ( D3DFVF_XYZ | D3DFVF_TEX1 )
	struct CubeVertex
	{
		float x, y, z,     u, v;
	};

	// static Vert vert[];
	static CubeVertex Vertexes[]  = {
		{  -1.0f,    1.0f,   -1.0f,        0.0f, 0.0f,},
		{   1.0f,    1.0f,   -1.0f,        1.0f, 0.0f,},
		{   1.0f,   -1.0f,   -1.0f,        1.0f, 1.0f,},
		{  -1.0f,   -1.0f,   -1.0f,        0.0f, 1.0f,},

		{  -1.0f,    1.0f,    1.0f,        0.0f,   0.0f,},
		{  -1.0f,    1.0f,   -1.0f,        1.0f,   0.0f,},
		{  -1.0f,   -1.0f,   -1.0f,        1.0f,   1.0f,},
		{  -1.0f,   -1.0f,    1.0f,        0.0f,   1.0f,},

		{   1.0f,    1.0f,    1.0f,         0.0f,   0.0f,},
		{  -1.0f,    1.0f,    1.0f,         1.0f,   0.0f,},
		{  -1.0f,   -1.0f,    1.0f,         1.0f,   1.0f,},
		{   1.0f,   -1.0f,    1.0f,         0.0f,   1.0f,},

		{   1.0f,    1.0f,   -1.0f,         0.0f,   0.0f,},
		{   1.0f,    1.0f,    1.0f,         1.0f,   0.0f,},
		{   1.0f,   -1.0f,    1.0f,         1.0f,   1.0f,},
		{   1.0f,   -1.0f,   -1.0f,         0.0f,   1.0f,},

		{  -1.0f,    1.0f,    1.0f,         0.0f,   0.0f,},
		{   1.0f,    1.0f,    1.0f,         1.0f,   0.0f,},
		{   1.0f,    1.0f,   -1.0f,         1.0f,   1.0f,},
		{  -1.0f,    1.0f,   -1.0f,         0.0f,   1.0f,},

		{   1.0f,   -1.0f,   -1.0f,         0.0f,   0.0f,},
		{   1.0f,   -1.0f,    1.0f,         1.0f,   0.0f,},
		{  -1.0f,   -1.0f,    1.0f,         1.0f,   1.0f,},
		{  -1.0f,   -1.0f,   -1.0f,         0.0f,   1.0f,}
	};

	static WORD Indexes[]   = {
		0,  1,  2,  2,  3,  0,
		4,  5,  6,  6,  7,  4,
		8,  9, 10, 10, 11,  8,
		12, 13, 14, 14, 15, 12,
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20
	};

	// draw
	hr |= pdevice->SetFVF(MESH_VERTEX_FVF);

	hr |=  pdevice->DrawIndexedPrimitiveUP(
		D3DPT_TRIANGLELIST,
		0, //UINT MinVertexIndex,
		36,//36, //UINT NumVertices,
		12,//12, //UINT PrimitiveCount,
		(void*)Indexes, //CONST void * pIndexData,
		D3DFMT_INDEX16, //D3DFORMAT IndexDataFormat,
		(void*)Vertexes, // CONST void* pVertexStreamZeroData,
		sizeof(CubeVertex) // UINT VertexStreamZeroStride
		);
 

#undef MESH_VERTEX_FVF
	return hr;
};	

//=======================================================================
GB_D3D9_API HRESULT drawMeshPrimitiveQuadXyMem(IDirect3DDevice9* pdevice)
{
  HRESULT hr = S_OK;

  struct QuadVertex
  {
	  float x,  y,  z,  tu, tv ;
  };

  static   QuadVertex Vertexes[] =  
  {
	  {  -1.0f,    1.0f,   0.0f,    0.0f,  0.0f, },  
	  {  -1.0f,   -1.0f,   0.0f,    0.0f,  1.0f, },
	  {   1.0f,    1.0f,   0.0f,    1.0f,  0.0f, },
	  {   1.0f,   -1.0f,   0.0f,    1.0f,  1.0f, },
	  {   1.0f,    1.0f,   0.0f,    1.0f,  0.0f, },
	  {  -1.0f,   -1.0f,   0.0f,    0.0f,  1.0f, },

  };

  static WORD Indexes[] = { 0,  1,  2,  3,  4,  5 };

#define MESH_VERTEX_FVF (D3DFVF_XYZ | D3DFVF_TEX1)

  // draw
  hr |= pdevice->SetFVF(MESH_VERTEX_FVF);

  hr |=  pdevice->DrawIndexedPrimitiveUP(
	  D3DPT_TRIANGLELIST,
	  0, //UINT MinVertexIndex,
	  6,//36, //UINT NumVertices,
	  2,//12, //UINT PrimitiveCount,
	  (void*)Indexes, //CONST void * pIndexData,
	  D3DFMT_INDEX16, //D3DFORMAT IndexDataFormat,
	  (void*)Vertexes, // CONST void* pVertexStreamZeroData,
	  sizeof(QuadVertex) // UINT VertexStreamZeroStride
	  );
 
#undef MESH_VERTEX_FVF
  return hr;
};	
	
	
	
	
	
	
//=======================================================================
	
}		 
}
}
}

#endif
// end file