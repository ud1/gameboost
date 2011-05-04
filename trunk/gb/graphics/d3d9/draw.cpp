

#if ( defined(GB_D3D9) && defined(WIN32) )

#include <gb/graphics/d3d9/draw.h>

#include <gb/math/math.h>
using namespace gb::math::base;



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
//
//   04.05.2010
//
//=======================================================================


//=======================================================================
GB_D3D9_API HRESULT  DrawScreenQuad( IDirect3DDevice9* pdevice,  
						const RECT& rect, 
						const D3DCOLORVALUE& color )
{
	HRESULT hr = 0;

	if ( pdevice == NULL )
	{
		return E_FAIL;
	}

#define D3DFVF_SCREENQUAD (D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE )
	struct SCREENQUADVERT
	{
		FLOAT x, y, z, rhw;   D3DCOLOR color; FLOAT u, v;
	};

	static SCREENQUADVERT screenQuadVertices[] = 
	{
		{
			10.0f, 0.0f, 1.0f, 1.0f,  0xffffffff, 0.0f, 0.0f, 
		}

		, 
		{
			300.0f, 0.0f, 1.0f, 1.0f, 0xffffffff,  1.0f, 0.0f, 
		}

		, 
		{
			300.0f, 400.0f, 1.0f, 1.0f,  0xffffffff, 1.0f, 1.0f, 
		}

		, 

		{
			10.0f, 0.0f, 1.0f, 1.0f,  0xffffffff, 0.0f, 0.0f, 
		}

		, 
		{
			300.0f, 400.0f, 1.0f, 1.0f,  0xffffffff, 1.0f, 1.0f, 
		}

		, 
		{
			10.0f, 400.0f, 1.0f, 1.0f,  0xffffffff, 0.0f, 1.0f, 
		}

		, 

	};

	float fleft = ( float )rect.left; //  10.0f; // x
	float ftop = ( float )rect.top; //  10.0f; // y
	float fright = ( float )rect.right; //  1.0f;  // x
	float fbottom = ( float )rect.bottom; //  1.0f;  // y   

	screenQuadVertices[0].x = fleft;
	screenQuadVertices[0].y = ftop;
	screenQuadVertices[1].x = fright;
	screenQuadVertices[1].y = ftop;
	screenQuadVertices[2].x = fright;
	screenQuadVertices[2].y = fbottom;

	screenQuadVertices[3].x = fleft;
	screenQuadVertices[3].y = ftop;
	screenQuadVertices[4].x = fright;
	screenQuadVertices[4].y = fbottom;
	screenQuadVertices[5].x = fleft;
	screenQuadVertices[5].y = fbottom;

	D3DCOLORVALUE _color = color;
	for(int c=0; c<6; c++)
	{
		screenQuadVertices[c].color = D3DCOLOR_COLORVALUE( _color.r, _color.g, _color.b, _color.a );
	}

	DWORD dwOldFvf;
	hr |= pdevice->GetFVF(&dwOldFvf);
	hr |= pdevice->SetFVF( D3DFVF_SCREENQUAD );  
	hr |= pdevice->DrawPrimitiveUP( D3DPT_TRIANGLELIST, 2, ( void* )screenQuadVertices, sizeof( SCREENQUADVERT ) );


	hr |= pdevice->SetFVF( dwOldFvf );
  #undef D3DFVF_SCREENQUAD
	return hr;
};


//=======================================================================
GB_D3D9_API HRESULT  DrawFullScreenQuad( IDirect3DDevice9* pdevice, const D3DCOLORVALUE& color)
{
  HRESULT hr =0;

  IDirect3DSurface9 *  pSurfBB = NULL;
 hr |= pdevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO,  &pSurfBB);
 if FAILED(hr)
 {
	 return hr;
 }

 D3DSURFACE_DESC des;
   hr |= pSurfBB->GetDesc(&des);
   if FAILED(hr)
   {
	   return hr;
   }

   if(pSurfBB)
   {
	   pSurfBB->Release();
	   pSurfBB = NULL;
   }

   RECT rect;
   rect.top = 0;
   rect.left = 0;
   rect.bottom = des.Height;
   rect.right = des.Width;
 hr |= DrawScreenQuad(pdevice, rect, color );

 return hr;
}

struct ScreenVertex
{
	float x, y, z, rhw;
	D3DCOLOR color;
};

static const DWORD  FVF_SCREENVERTEX     = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE);



//=======================================================================
GB_D3D9_API HRESULT DrawScreenPoint(IDirect3DDevice9* pdevice, const D3DCOLORVALUE& color,
													float x, float y, int pointSize) 
{
	HRESULT hr = 0;
	assert(pdevice);
	if(!pdevice)
	{
		return E_FAIL;
	}

	DWORD dwOldFvf;
	hr |= pdevice->GetFVF(&dwOldFvf);
	hr |= pdevice->SetFVF(FVF_SCREENVERTEX);
 
	DWORD dwOldPointSize = 0;
	hr |= pdevice->GetRenderState(D3DRS_POINTSIZE, &dwOldPointSize);
	float fpsize = (float)pointSize;
	hr |= pdevice->SetRenderState(D3DRS_POINTSIZE, *((DWORD*) &fpsize) );

	ScreenVertex vert;
	vert.x = x;
	vert.y = y;
	vert.z = 0.0f;
	vert.rhw = 2.0f;
	vert.color  = D3DCOLOR_COLORVALUE(color.r, color.g, color.b, color.a);

	hr |= pdevice->DrawPrimitiveUP(D3DPT_POINTLIST, 1, (void*)&vert,  sizeof (ScreenVertex) );
 	hr |= pdevice->SetFVF(dwOldFvf);
	hr |= pdevice->SetRenderState(D3DRS_POINTSIZE, dwOldPointSize  );
	return hr;
};



//=======================================================================
GB_D3D9_API HRESULT DrawScreenPoints(IDirect3DDevice9* pdevice, const D3DCOLORVALUE& color,
						  const float* vec2_arrayCoord, int num, int pointSize)  
{
	HRESULT hr = 0;
	assert(pdevice);
	if(!pdevice) 
	{ 
		return  E_FAIL;
	}

	static const int NARRLEN = 1024; // < max 1024 points
	static ScreenVertex varr [NARRLEN];

	for (int c = 0; (c < num) && (c < NARRLEN); c++)
	{
		const gb::math::base::vec2_s* pv = (gb::math::base::vec2_s*)vec2_arrayCoord;
		varr[c].x = (pv + c)->x;
		varr[c].y = (pv + c)->y;
		varr[c].z = 0.0f;
		varr[c].rhw = 2.0;
		varr[c].color = D3DCOLOR_COLORVALUE(color.r, color.g, color.b, color.a);

	}

	DWORD dwOldPointSize = 0;
	hr |= pdevice->GetRenderState(D3DRS_POINTSIZE, &dwOldPointSize);
	   float fpsize = (float)pointSize;
	hr |= pdevice->SetRenderState(D3DRS_POINTSIZE, *((DWORD*) &fpsize) );

	DWORD dwOldFvf;
	hr |= pdevice->GetFVF(&dwOldFvf);
	hr |= pdevice->SetFVF(FVF_SCREENVERTEX);
 
	int numpoints = num;
	if (numpoints < num)
	{
		numpoints = NARRLEN;
		hr |= S_FALSE; // check max
	}

	hr |= pdevice->DrawPrimitiveUP(D3DPT_POINTLIST, numpoints, (void*)varr, sizeof(ScreenVertex));
 
	hr |= pdevice->SetRenderState(D3DRS_POINTSIZE, dwOldPointSize  );
	hr |= pdevice->SetFVF(dwOldFvf);

	return hr;
};



//=======================================================================
GB_D3D9_API HRESULT DrawScreenLines(IDirect3DDevice9* pdevice, const D3DCOLORVALUE& color, 
						 const float* vec2_arrayCoord, int num) 
{
	HRESULT hr = 0;
	assert(pdevice);
	if(!pdevice)
	{
	 return E_FAIL;
	}


	if (num < 2)
	{
		// invalid params
		return S_FALSE;
	}

	static const int NARRLEN = 256; // max lines
	static ScreenVertex varr[NARRLEN];

	for (int c = 0; (c < NARRLEN) && (c < num); c++)
	{
		const vec2_s* pv = (vec2_s*)vec2_arrayCoord;
		varr[c].x = (pv + c)->x;
		varr[c].y = (pv + c)->y;
		varr[c].z = 0.0f;
		varr[c].rhw = 2.0f;
		varr[c].color = D3DCOLOR_COLORVALUE(color.r, color.g, color.b, color.a);

	}

	DWORD dwOldFvf;
	hr |= pdevice->GetFVF(&dwOldFvf);
	hr |= pdevice->SetFVF(FVF_SCREENVERTEX);
 
	int numpoints = num - 1;
	if (numpoints > NARRLEN)
	{
		numpoints = NARRLEN;
		hr |= S_FALSE; // check max
	}
 
	hr |= pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, numpoints, (void*)varr, sizeof(ScreenVertex) );
 
		hr |= pdevice->SetFVF( dwOldFvf );
	return hr;
};


//=======================================================================
GB_D3D9_API HRESULT DrawScreenCircle(IDirect3DDevice9* pdevice, const D3DCOLORVALUE& color,
						  float x, float y, float radius)  
{
	HRESULT hr = S_OK;
	assert(pdevice);
	if(!pdevice)
	{
		return E_FAIL;
	}

	static const int SEGM = 32; // lines
	 vec2_s varr[SEGM + 4];  //   +1

	static const float FACT = 0.0f;
	float valfact = FACT;

	int valSEGM = SEGM;
	for (int c = 0; c < SEGM; c++)
	{
		  vec2_s pos;
		pos.x = x;
		pos.y = y;
		valfact = (float)c / SEGM;
		  static const float _C_PI   = 3.141592654f;
		varr[c].x = sin( _C_PI * 2.0f *valfact) *radius;
		varr[c].y = cos( _C_PI * 2.0f *valfact) *radius;

		varr[c].x += pos.x;
		varr[c].y += pos.y;

	};

	varr[SEGM] = varr[0];
	varr[SEGM + 1] = varr[0];

	DWORD num = (DWORD)SEGM + 1;
	hr |= DrawScreenLines(pdevice, color, varr[0], num);
 
	return hr;
};


//=======================================================================
GB_D3D9_API HRESULT DrawScreenRect(IDirect3DDevice9* pdevice, const D3DCOLORVALUE& color,
						float x1, float y1, float x2, float y2 )  
{
	HRESULT hr = S_OK;
	assert(pdevice);
	if(!pdevice)
	{
		return E_FAIL;
	}

	vec2_s varr[5];

	varr[0].x = (float)x1;
	varr[0].y = (float)y1;

	varr[1].x = (float)x2;
	varr[1].y = (float)y1;

	varr[2].x = (float)x2; 
	varr[2].y = (float)y2; 

	varr[3].x = (float)x1;
	varr[3].y = (float)y2;

	varr[4] = varr[0];

	hr |=  DrawScreenLines(  pdevice, color, varr[0], 5  );
	return hr;
};



 

	
	
	
	
	
//=======================================================================
	
}		 
}
}
}

#endif
// end file