#include "d3d9pch.h"
//#include "pch.h"

#if ( defined(GB_D3D9) && defined(WIN32) )

#include <gb/graphics/d3d9/draw.h>

#include <gb/fmath/fmath.h>
using namespace gb::fmath;;



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

	for(int c=0; c<6; c++)
	{
		screenQuadVertices[c].color = D3DCOLOR_COLORVALUE( color.r, color.g, color.b, color.a );
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
		const gb::fmath::vec2* pv = (gb::fmath::vec2*)vec2_arrayCoord;
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
		const vec2* pv = (vec2*)vec2_arrayCoord;
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
	 vec2 varr[SEGM + 4];  //   +1

	static const float FACT = 0.0f;
	float valfact = FACT;

	int valSEGM = SEGM;
	for (int c = 0; c < SEGM; c++)
	{
		  vec2 pos;
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

	vec2 varr[5];

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

 // 2011.05.09


struct MARK_BEGIN {};


#define D3DFVF_SCREENQUAD (D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE )

//! \brief   Экранный прямоугольник
struct QuadMesh {

	struct VERTEX  {
		float x, y, z,  rhw;   D3DCOLOR color; 
		float u, v;

		inline void set_xy(float _x, float _y) { x=_x; y=_y;}; // z=rhw=1.0f;  }
		inline void set_uv(float _u, float _v) { u=_u; v=_v; }
		inline void add_uv(float _u, float _v) { u+=_u; v+=_v; }
		inline void mul_uv(float _u, float _v) { u*=_u; v*=_v; }
	};

	VERTEX  vertex [6];


	inline void set_zrhw() 
	{

		vertex[0].z =   0.0f;
		vertex[1].z =   0.0f;
		vertex[2].z =   0.0f;
		vertex[3].z =   0.0f;
		vertex[4].z =   0.0f;
		vertex[5].z =   0.0f;

		vertex[0].rhw = 1.0f;
		vertex[1].rhw = 1.0f;
		vertex[2].rhw = 1.0f;
		vertex[3].rhw = 1.0f;
		vertex[4].rhw = 1.0f;
		vertex[5].rhw = 1.0f;




	}

	inline void set_color(D3DCOLOR col)
	{
		vertex[0].color = col;
		vertex[1].color = col;
		vertex[2].color = col;
		vertex[3].color = col;
		vertex[4].color = col;
		vertex[5].color = col;
	}


	inline void setTxCoord_default()
	{

		vertex[0].set_uv(  0.0f , 0.0f );
		vertex[1].set_uv(  1.0f , 0.0f ); 
		vertex[2].set_uv(  1.0f , 1.0f );
		vertex[3].set_uv(  0.0f , 0.0f ); 
		vertex[4].set_uv(  1.0f , 1.0f );
		vertex[5].set_uv(  0.0f , 1.0f );


	}
	inline void set_TxCoordRectTx(const RECT& rec, int nTextureW, int nTextureH)
	{
		setTxCoord_default();

		float mulx, muly;
		mulx = ( (float) (rec.right -  rec.left))  /  nTextureW  ;
		muly = ( (float) (rec.bottom - rec.top))   /  nTextureH  ;

		vertex[0].mul_uv( mulx , muly  );   //  0.0f,  0.0f, 
		vertex[1].mul_uv( mulx , muly  );   //  1.0f,  0.0f, 
		vertex[2].mul_uv( mulx , muly  );	//  1.0f,  1.0f, 
		vertex[3].mul_uv( mulx , muly  );	//  0.0f,  0.0f, 
		vertex[4].mul_uv( mulx , muly  );	//  1.0f,  1.0f, 
		vertex[5].mul_uv( mulx , muly  );	//  0.0f,  1.0f,

		float addx, addy;
		addx =    (float)rec.left /nTextureW   ;
		addy =    (float)rec.top / nTextureH   ;

		vertex[0].add_uv( addx , addy  );  //  0.0f ,  0.0f, 
		vertex[1].add_uv( addx , addy  ); 	//  1.0f ,  0.0f, 
		vertex[2].add_uv( addx , addy  );	//  1.0f ,  1.0f, 
		vertex[3].add_uv( addx , addy  );	//  0.0f ,  0.0f, 
		vertex[4].add_uv( addx , addy  );	//  1.0f ,  1.0f, 
		vertex[5].add_uv( addx , addy  );	//  0.0f ,  1.0f,



	}



	inline void setPositionRect(const RECT& rec)  
	{

		vertex[0].set_xy(  (float)rec.left , (float)rec.top  );        
		vertex[1].set_xy(  (float)rec.right , (float)rec.top  );   
		vertex[2].set_xy(  (float)rec.right , (float)rec.bottom  );    
		vertex[3].set_xy(  (float)rec.left , (float)rec.top  );    
		vertex[4].set_xy(  (float)rec.right , (float)rec.bottom  );    
		vertex[5].set_xy(  (float)rec.left , (float)rec.bottom  );    


	}

 
};


//=======================================================================
GB_D3D9_API  HRESULT  DrawTexturedMemQuad(  IDirect3DDevice9* pdevice, 
								  IDirect3DTexture9 *pTexture ,
								  const RECT& recScreen,
								  const RECT& recTexture,
								  const D3DCOLOR cLeftTop,
								  const D3DCOLOR cRightTop,
								  const D3DCOLOR cLeftBottom,
								  const D3DCOLOR cRightBottom)
{
	HRESULT hr = 0;
	if ( pdevice == NULL )
	{
		return E_FAIL;
	}

	if ( pTexture == NULL )
	{
		return E_FAIL;
	}


	D3DSURFACE_DESC  des;
	hr |= pTexture->GetLevelDesc(0, &des);
	if FAILED(hr)
	{
		return hr;
	}

	hr |= pdevice->SetTexture(0, pTexture );

	QuadMesh quad;
	quad.set_zrhw();
	quad.set_color(  0-1);






	//  left top   // const D3DCOLOR cLeftTop,
	quad.vertex[0].color = cLeftTop;  
	quad.vertex[3].color = cLeftTop;  

	//  right top	 // const D3DCOLOR cRightTop,
	quad.vertex[1].color = cRightTop;

	// left bottom	//  const D3DCOLOR cLeftBottom
	quad.vertex[5].color = cLeftBottom;

	// right bottom  //  const D3DCOLOR cRightBottom
	quad.vertex[2].color = cRightBottom;
	quad.vertex[4].color = cRightBottom;



	quad.setPositionRect(recScreen);
	//quad.setPosRect2(  (float)recScreen.left , (float)recScreen.top , (float)recScreen.right , (float)recScreen.bottom    );


	// quad.setTxCoord_default();
	quad.set_TxCoordRectTx(recTexture, des.Width , des.Height);


	DWORD dwOldState = 0;
	DWORD dwOldZEnable = 0;
	if(  1 )
	{
		hr |=  pdevice->GetRenderState(D3DRS_CULLMODE,  &dwOldState );
		hr |=  pdevice->GetRenderState(D3DRS_ZENABLE,  &dwOldZEnable );
	}

	hr |=  pdevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	hr |=  pdevice->SetRenderState( D3DRS_ZENABLE, 0 );


	hr |= pdevice->SetFVF( D3DFVF_SCREENQUAD );
	hr |= pdevice->DrawPrimitiveUP( 
		D3DPT_TRIANGLELIST, 2, ( void* )&quad.vertex[0] , sizeof( QuadMesh::VERTEX ) );

	if ( 1  )
	{
		hr |=  pdevice->SetRenderState(D3DRS_CULLMODE,  dwOldState );
		hr |=  pdevice->SetRenderState(D3DRS_ZENABLE,   dwOldZEnable );
	};



	return hr;
};

#undef D3DFVF_SCREENQUAD
 


//=======================================================================


//////////////////////////////////////////////////////////

#include <assert.h>

struct SCREENVERTEX2D
{
	float x, y, z, rhw;
	D3DCOLOR color;
};

#define  FVFSCREENVERTEX2D  (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

//==========================================================================================
GB_D3D9_API HRESULT DrawScreenMarkerObl(IDirect3DDevice9* pdevice, 
										float x, float y, 
										float size, D3DCOLOR color)
{
	HRESULT hr =S_OK;
 
	assert(pdevice);
	if(!pdevice)
	{
		return E_FAIL;
	}
 
	  SCREENVERTEX2D varr[2];
 

	  // fill array default data
	  varr[0].color = color;
	  varr[0].rhw = 1.0f;
	  varr[0].z = 0.0f;

	  varr[1].color = color;
	  varr[1].rhw = 2.0f;
	  varr[1].z = 0.0f;
 
	  // set states
	  hr |= pdevice->SetRenderState(D3DRS_ZENABLE, 0);
	  hr |=  pdevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	   	hr |= pdevice->SetFVF(FVFSCREENVERTEX2D);


	   // draw

	   // set data
 
	 varr[0].x = x-1; 
	 varr[0].y = y-1;

	 varr[1].x = x-size*0.707f;
	 varr[1].y = y-size*0.707f;
     hr |= pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof(SCREENVERTEX2D) );

 
	varr[0].x = x+1; 
	varr[0].y = y-1;

	varr[1].x = x+size*0.707f;
	varr[1].y = y-size*0.707f;
   hr |= pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof(SCREENVERTEX2D) );


   varr[0].x = x-1; 
   varr[0].y = y+1;

   varr[1].x = x-size*0.707f;
   varr[1].y = y+size*0.707f;
   hr |= pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof(SCREENVERTEX2D) );


   varr[0].x = x+1; 
   varr[0].y = y+1;

   varr[1].x = x+size*0.707f;
   varr[1].y = y+size*0.707f;
   hr |= pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof(SCREENVERTEX2D) );
 

	// restore data

#pragma message("ks777:  NEED restore " __FILE__ )



	return hr;
}





//==============================================================================
GB_D3D9_API HRESULT DrawScreenMarker(IDirect3DDevice9* pdevice,  float x, float y,  float size, D3DCOLOR color)
{
   HRESULT hr =S_OK;


   assert(pdevice);
   if(!pdevice)
   {
	   return E_FAIL;
   }

   SCREENVERTEX2D varr[2];


   // fill array default data
   varr[0].color = color;
   varr[0].rhw = 1.0f;
   varr[0].z = 0.0f;

   varr[1].color = color;
   varr[1].rhw = 2.0f;
   varr[1].z = 0.0f;


   hr |= pdevice->SetRenderState(D3DRS_ZENABLE, 0);
   hr |=  pdevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
   hr |= pdevice->SetFVF(FVFSCREENVERTEX2D);

   const int noffset = 2;  // отступ от центра до начала линии

	  // up
   varr[0].x = x; 
   varr[0].y = y-noffset;
   varr[1].x = x;
   varr[1].y = y-size;
   hr |= pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof(SCREENVERTEX2D) );

	   // right
   varr[0].x = x+noffset; 
   varr[0].y = y;
   varr[1].x = x+size;
   varr[1].y = y;
   hr |= pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof(SCREENVERTEX2D) );

	  // down
   varr[0].x = x; 
   varr[0].y = y+noffset;

   varr[1].x = x;
   varr[1].y = y+size;
   hr |= pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof(SCREENVERTEX2D) );

	 //left
   varr[0].x = x-noffset; 
   varr[0].y = y;

   varr[1].x = x-size;
   varr[1].y = y;
   hr |= pdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, (void*)varr, sizeof(SCREENVERTEX2D) );




				 

#pragma message("ks777:    NEED restore  " __FILE__ )

	return hr;
}



#undef FVFSCREENVERTEX2D
struct MARKER_BEGIN_END {};





	
	
	
//=======================================================================
	
} // end namespace		 
} // end namespace
} // end namespace
} // end namespace

#endif
// end file