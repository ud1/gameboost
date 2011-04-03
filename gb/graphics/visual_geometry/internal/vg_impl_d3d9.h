#if ( defined(GB_D3D9) && defined(WIN32) )
#include <gb/graphics/visual_geometry/visual_geometry.h>

#pragma once

#ifndef GB_D3DX9
#error Пока d3dx9 нужна. Определить GB_D3DX9.
#endif

#include <d3dx9.h>
#include <d3dx9core.h>




#include <gb/graphics/visual_geometry/visual_geometry.h>
#include <assert.h>

// ks777: temp
#define MONPRINTB(m) 

namespace gb {
namespace graphics {
namespace visual_geometry {
namespace internal {

//------------------------------------------------------------------------------

 

//! Сохраняет и восстанавливает состояние девайса
class VGSaveRestoreDataD3D9 {
public:
 
	DWORD fvf;
	D3DMATERIAL9 material;
	D3DMATRIX wMatrix;
	IDirect3DBaseTexture9 *texture0;
	DWORD rsPointSize;
	DWORD rsZENABLE;
	DWORD rsZWRITEENABLE;
	DWORD rsALPHABLENDENABLE;
	DWORD rsFillMode;

	IDirect3DVertexShader9 *pIVSH;
	IDirect3DPixelShader9 *pIPSH;

	 VGSaveRestoreDataD3D9() {};

  //! сохранение состояния девайса
  HRESULT SaveDeviceData(IDirect3DDevice9* pdevice, 
						const VGCOLOR& newColor, 
						float pointSize=1.0f, 
						IDirect3DTexture9 *newTxtr=NULL );

  //! восстановление состояния девайса
  HRESULT RestoreDeviceData(IDirect3DDevice9* pdevice);

};
// end class
 
 


//-------------------------------------------------------------------------
//					VGDrawValuesImpl_D3D9	  
//-------------------------------------------------------------------------


enum VGDrawValuesFontSize_e 
{
	FS_NORMAL, FS_SMALL, FS_BIG
};

class VGDrawValuesImpl_D3D9 : public gb::graphics::visual_geometry::IDrawValues 
{
public:
	// members
	mutable VGDrawValuesFontSize_e   m_lastFontSize;
	mutable gb::color::Color4f m_color;
	mutable RECT m_Rec;

	mutable ID3DXFont*  pIFontNormal; 
	mutable ID3DXFont*  pIFontSmall; 
	mutable ID3DXFont*  pIFontBig;

	mutable IDirect3DDevice9* m_pdevice;
	mutable bool m_bChangePos;


VGDrawValuesImpl_D3D9(IDirect3DDevice9* pdevice) : m_pdevice(pdevice)  
{
  assert(pdevice);
 
  m_color.r = 1.0f; 
  m_color.g = 1.0f; 
  m_color.b = 1.0f; 
  m_color.a = 1.0f;

  m_lastFontSize  = FS_NORMAL; // dapl_fontsize_normal;


  pIFontSmall = NULL; 
  pIFontBig = NULL; 
  pIFontNormal = NULL;

  m_Rec.left =  0;
  m_Rec.top  =  0;
  m_Rec.right   =    1000;
  m_Rec.bottom  =    1000;  

  m_bChangePos = false;
 
}

virtual ~VGDrawValuesImpl_D3D9() 
{
  releaseInterfaces();
}
 
 

//*  check create font interfces
HRESULT  checkFontInterfaces() const;


void releaseInterfaces() 
{
	static const char  CSTR_ERROR [] = "EXCEPTION !\n";

	//__try  
	try
	{ 
		if(pIFontSmall) { pIFontSmall->Release() ; pIFontSmall = NULL;   }; 
	} 
	//__except(1) 
	catch(...)
	{ 

		MONPRINTB( CSTR_ERROR );   
	};

	//__try  
	try
	{ 
		if(pIFontBig) { pIFontBig->Release() ; pIFontBig = NULL;   }; 
	} 
	//__except(1) 
	catch(...)
	{ 
		MONPRINTB( CSTR_ERROR);   
	};

	//__try  
	try
	{ 
		if(pIFontNormal) { pIFontNormal->Release() ; pIFontNormal = NULL;   }; 
	} 
	//__except(1) 
	catch(...)
	{ 
		MONPRINTB ( CSTR_ERROR );   
	};

	pIFontSmall   = NULL;  
	pIFontBig     = NULL; 
	pIFontNormal  = NULL;

	m_pdevice = NULL;
};

void SetDevice(IDirect3DDevice9* pdevice) {  m_pdevice = pdevice; };


virtual ID3DXFont*  GetInterfaceFontSmall()  const 
{
	HRESULT hr = checkFontInterfaces();
	if FAILED(hr) return NULL;
	return pIFontSmall; 
};

virtual ID3DXFont*  GetInterfaceFontNormal() const 
{
	HRESULT hr = checkFontInterfaces();
	if FAILED(hr) return NULL;
	return pIFontNormal; 
};

virtual ID3DXFont*  GetInterfaceFontBig()    const 
{
	HRESULT hr = checkFontInterfaces();
	if FAILED(hr) return NULL;
	return pIFontBig; 
};


private:

	HRESULT drawStrEx(  const char* str ) const ;
	void ComputeNextPos( ) const;  

	// const

	static const int  CONST_DRWVAL_FONTS_COMM_BETWLINES_OFFSET  = 4;
	static const int  CONST_DRWVAL_NORMALFONT_NEWSTR_OFFSET  = 10; 
	static const int  CONST_DRWVAL_SMALLFONT_NEWSTR_OFFSET =  8; 
	static const int  CONST_DRWVAL_BIGFONT_NEWSTR_OFFSET  = 14; 



//===================  IMPLEMENTATION ABSTRACT METHODS ====================
public:

	virtual HRESULT setPos(int x, int y) const 
 	{ 
		HRESULT hr =0; 
	m_Rec.left=x;
	m_Rec.top=y;
	m_Rec.right = 2000;
	m_Rec.bottom = 2000;
	m_bChangePos=true; 
	return hr; 
	};

	virtual HRESULT setFontSmall() const         { HRESULT hr =0;  m_lastFontSize= FS_SMALL;    return hr;  };
	virtual HRESULT setFontNormal() const        { HRESULT hr =0;  m_lastFontSize= FS_NORMAL;   return hr;  };
	virtual HRESULT setFontBig() const           { HRESULT hr =0;  m_lastFontSize= FS_BIG;      return hr;  };

	virtual HRESULT setColor( const VGCOLOR& color) const  
	{ 
		HRESULT hr =0; 
		m_color.r = color.r;
		m_color.g = color.g;		
		m_color.b = color.b;
		m_color.a = color.a;
		return hr; 
	};

	virtual HRESULT setColorRed()    const   { HRESULT hr =0;  m_color=gb::color::COLOR4F_RED;     return hr; };
	virtual HRESULT setColorGreen()  const   { HRESULT hr =0;  m_color=gb::color::COLOR4F_GREEN;   return hr; };
	virtual HRESULT setColorBlue()   const   { HRESULT hr =0;  m_color=gb::color::COLOR4F_BLUE;    return hr; };
	virtual HRESULT setColorYellow() const   { HRESULT hr =0;  m_color=gb::color::COLOR4F_YELLOW;  return hr; };
	virtual HRESULT setColorWhite()  const   { HRESULT hr =0;  m_color=gb::color::COLOR4F_WHITE;   return hr; };
	virtual HRESULT setColorGray()   const   { HRESULT hr =0;  m_color=gb::color::COLOR4F_GRAY;    return hr; };

	virtual HRESULT drawS(const char* s) const ;
	virtual HRESULT drawF( const char* _Format, ... ) const ;

	virtual HRESULT drawBool  (bool  val, const char* promt=NULL) const ;
	virtual HRESULT drawInt   (int   val, const char* promt=NULL) const ;
	virtual HRESULT drawFloat (float val, const char* promt=NULL) const ;

	virtual HRESULT drawIntArray   (const int*   p, int num, const char* promt=NULL) const ;
	virtual HRESULT drawFloatArray (const float* p, int num, const char* promt=NULL) const ;

	virtual HRESULT drawVec2(const VGVEC2* v, const char* promt=NULL) const ;
	virtual HRESULT drawVec3(const VGVEC3* v, const char* promt=NULL) const ;
	virtual HRESULT drawVec4(const VGVEC4* v, const char* promt=NULL) const ; 

	//-----------------------------------

	virtual HRESULT drawMatrix(const VGMATRIX* m, const char* promt=NULL) const ;

	virtual HRESULT drawPoint(const POINT pnt, const char* promt=NULL) const 
	{
		HRESULT hr =0;
		if(promt)
		{
			 
			hr |=  drawF("%s %i  %i", promt, pnt.x, pnt.y  );
		}
		else
		{
			hr |=  drawF("%i  %i",  pnt.x, pnt.y  );
		};

		return hr;
	};

	virtual HRESULT drawPoint(int x, int y,    const char* promt=NULL) const 
	{
		POINT pnt = {x, y};
		return drawPoint(pnt, promt);	
	};

	virtual HRESULT drawPoint(const VGVEC2* pos, const char* promt=NULL) const 
	{
		return drawPoint(math::scalar::round(pos->x) , math::scalar::round(pos->y) , promt);
	};




};


//-------------------------------------------------------------------------
//					VGDraw2DGeometry_Impl_D3D9	  
//-------------------------------------------------------------------------

class VGDraw2DGeometry_Impl_D3D9 : public gb::graphics::visual_geometry::IDraw2DGeometry
{
public:

    struct TVgVert2D
    {
	     FLOAT x, y, z, rhw;
	     D3DCOLOR color;
    };

	static const DWORD  VG_FVF_2DLINES     = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

    IDirect3DDevice9* m_pdevice  ;

    mutable VGCOLOR  m_color;
	mutable VGSaveRestoreDataD3D9   m_DeviceData;
 

	VGDraw2DGeometry_Impl_D3D9(IDirect3DDevice9* pdevice) : m_pdevice(pdevice)  
	{ 
		assert(m_pdevice);
		m_color.setWhite(); 
	};
	virtual ~VGDraw2DGeometry_Impl_D3D9() 
	{   
	  releaseInterfaces();
	};

	void releaseInterfaces()
	{
	 // none
	}


#pragma region IMPLEM_COLOR_METHODS

  // --------------------  override  color ------------------------------
 
	 
	virtual HRESULT setColor(const VGCOLOR& color) const { m_color=color; return 0; }
	virtual HRESULT setColor(const D3DCOLORVALUE& color) const  { m_color=color; return 0; }
 

	virtual HRESULT setColor(const D3DXCOLOR* color) const 
	{
   	 m_color.r=color->r;
	 m_color.g=color->g;
	 m_color.b=color->b;
	 m_color.a=color->a;
	    return 0;	
	};

	virtual HRESULT setColor(float r, float g, float b, float a) const 
	{
	 m_color.r=r;
	 m_color.g=g;
	 m_color.b=b;
	 m_color.a=a;

	 return 0;
	};

  virtual HRESULT setColorRed    ()  const { m_color.setBlack(); m_color.r=1.0f;  return 0; }
  virtual HRESULT setColorGreen  ()  const { m_color.setBlack(); m_color.g=1.0f;  return 0; }
  virtual HRESULT setColorBlue   ()  const { m_color.setBlack(); m_color.b=1.0f;  return 0; }
  virtual HRESULT setColorYellow ()  const { m_color = gb::color::Color4f(  1.0f,   1.0f,   0.0f,  1.0f);  return 0; }
  virtual HRESULT setColorWhite  ()  const { m_color.setWhite();  return 0; }
  virtual HRESULT setColorGray   ()  const { m_color = gb::color::Color4f(0.752941f,  0.752941f,  0.752941f,  1.0f);  return 0; } 
  virtual HRESULT setColorPink   ()  const { m_color = gb::color::Color4f(1.0f,  0.0f,  1.0f,  1.0f);  return 0; }    
 
#pragma endregion IMPLEM_COLOR_METHODS


	//--------------------  override other  -------------------------------
 

  virtual HRESULT draw2dPoint(int x, int y,                float pointSize) const { return  draw2dPoint( (float)x, (float)y, pointSize ); };
  virtual HRESULT draw2dPoint(float x, float y,            float pointSize) const;
  virtual HRESULT draw2dPoint(const VGVEC2* pos,      float pointSize) const { return draw2dPoint(pos->x, pos->y, pointSize ); };
//  virtual HRESULT draw2dPoint(const VGVEC2* pos,  float pointSize) const { return draw2dPoint(pos->x, pos->y, pointSize );};
  virtual HRESULT draw2dPoint(const POINT p,  float pointSize) const              { return draw2dPoint( (float)p.x, (float)p.y   , pointSize );  };

  virtual HRESULT draw2dPoints(const VGVEC2* pv, int num, float pointSize) const ;

  //-----------------------------------------------------------

 virtual HRESULT draw2dLine(const VGVEC2* p1, const VGVEC2* p2) const;
 virtual HRESULT draw2dLine(const POINT p1, const POINT p2) const 
 {
   //return Draw2dLine( &VGVEC2(),  &VGVEC2() );
   return draw2dLine( &VGVEC2( (float)p1.x, (float)p1.y ), &VGVEC2( (float)p2.x, (float)p2.y ) );
 };

 //virtual HRESULT draw2dLine(const VGVEC2* p1, const VGVEC2* p2) const 
 //{
 //  return draw2dLine( &VGVEC2(p1->x, p1->y),  &VGVEC2(p2->x, p2->y) );
 //};

 virtual HRESULT draw2dLine(const gb::math::geom2d::Line* line) const
 {
   return draw2dLine( &VGVEC2(line->src.x, line->src.y),  &VGVEC2(line->dest.x, line->dest.y) );
 };

 virtual HRESULT draw2dLine(int x1, int y1, int x2, int y2) const 
 {
    return draw2dLine( &VGVEC2( (float)x1, (float)y1 ),  &VGVEC2( (float)x2, (float)y2 ) );
 };

 virtual HRESULT draw2dLine(float x1, float y1, float x2, float y2) const 
 {
   return draw2dLine( &VGVEC2(x1, y1),  &VGVEC2(x2, y2) );
 };

  virtual HRESULT draw2dLines(const VGVEC2* pv, int num) const ;

 //---------------------------------------------------------------------


  virtual HRESULT draw2dRect(const D3DRECT* rect) const ;
  virtual HRESULT draw2dRect(int x1,   int y1,     int x2,   int y2) const 
  {
	  D3DRECT rect = { x1, y1, x2, y2 };
	  return draw2dRect(&rect);
  };


 virtual HRESULT draw2dRect(float x1, float y1,   float x2, float y2) const 
 {
 	  D3DRECT rect = { (int)x1, (int)y1, (int)x2, (int)y2 };
	  return draw2dRect(&rect); 
 };

 virtual HRESULT draw2dRect(const POINT p1, POINT p2) const 
 {
   	  D3DRECT rect = { p1.x, p1.y,   p2.x, p2.y };
	  return draw2dRect(&rect); 
 };

 virtual HRESULT draw2dRect(const RECT rect) const 
 {
      D3DRECT nrect = { rect.left, rect.top, rect.right, rect.bottom   };
	  return draw2dRect(&nrect); 
 };

 
 virtual HRESULT draw2dRect(gb::math::geom2d::Rect* rect) const 
 {
	  return draw2dRect( rect->x1, rect->y1,   rect->x2, rect->y2 ); 
 };


 //--------------------------------------------------------------------

#pragma message("ks777: Сделать базовый метод просто по точкам "  __FILE__ )
 virtual HRESULT draw2dSolidRect(int x1, int y1,   int x2, int y2) const ; //const D3DRECT* rect) const ;
 virtual HRESULT draw2dSolidRect(const POINT p1, const POINT p2) const 
 {
	 return draw2dSolidRect( p1.x,   p1.y,     p2.x,   p2.y  );
 };

 virtual HRESULT draw2dSolidRect(const D3DRECT& rect) const
 {
	 return draw2dSolidRect(rect.x1, rect.y1, rect.x2, rect.y2  );
 };

 virtual HRESULT draw2dSolidRect(const RECT rect) const 
 {
	 return draw2dSolidRect( rect.left, rect.top, rect.right, rect.bottom  );
 };

 virtual HRESULT draw2dSolidRect(const gb::math::geom2d::Rect* rect) const 
 {
	 return draw2dSolidRect( (int)rect->x1, (int)rect->y1, (int)rect->x2,  (int)rect->y2 );
 };

 //------------------------------------------------------------

 virtual HRESULT draw2dCircle(const VGVEC2* pos, float radius) const ;

 virtual HRESULT draw2dCircle(float x, float y,       float radius) const 
 {
   return draw2dCircle( &VGVEC2(x, y) , radius );
 };

 virtual HRESULT draw2dCircle(int x, int y,           float radius) const 
 {
   return draw2dCircle( &VGVEC2( (float)x, (float)y) , radius );
 };

 virtual HRESULT draw2dCircle(const POINT pos,        float radius) const 
 {
   return draw2dCircle( &VGVEC2((float)pos.x, (float)pos.y) , radius );
 };

 virtual HRESULT draw2dCircle(const gb::math::geom2d::Circle*   c) const 
 {
   return draw2dCircle( &VGVEC2( c->center.x, c->center.y ) , c->radius );
 };

 //-----------------------------------------------------------

 virtual HRESULT draw2dAxies(const VGVEC2 coord) const ;
 virtual HRESULT draw2dAxies(float x, float y) const 
 {
   return draw2dAxies( VGVEC2( x   ,  y )  );
 };

 virtual HRESULT draw2dAxies(int x, int y) const 
 {
   return draw2dAxies( VGVEC2( (float)x   ,  (float)y )  ); 
 };

 virtual HRESULT draw2dAxies(const POINT p) const 
 {
    return draw2dAxies( VGVEC2( (float)p.x   ,  (float)p.y )  ); 
 };

 //virtual HRESULT draw2dAxies(const VGVEC2 coord) const 
 //{
 //    return draw2dAxies( VGVEC2( coord.x   ,  coord.y )  ); 
 //};


 //------------------------------------------------------------

 virtual HRESULT draw2dTriangle(const VGVEC2* p1, const VGVEC2* p2,const VGVEC2* p3) const ;
 virtual HRESULT draw2dTriangle(const POINT p1, const POINT p2, const POINT p3) const 
 {
  return draw2dTriangle( &VGVEC2((float)p1.x , (float)p1.x), &VGVEC2((float)p2.x , (float)p2.x), &VGVEC2((float)p3.x , (float)p3.x)  );
 };

 //-----------------------------------------------------------

 virtual HRESULT draw2dSolidTriangle(const VGVEC2* p1, const VGVEC2* p2,const VGVEC2* p3) const ;

 //-------------------------------------------------------

 virtual HRESULT draw2dPromtString(const VGVEC2 coord, const char* s) const;
 virtual HRESULT draw2dPromtString(const   POINT p,         const char* s) const 
 {
   return draw2dPromtString( VGVEC2( (float)p.x, (float)p.y ), s );
 };

 virtual HRESULT draw2dPromtString(int x,   int y,          const char* s) const 
 {
   return draw2dPromtString( VGVEC2( (float) x, (float)y ), s );
 };

 virtual HRESULT draw2dPromtString(float x, float y,        const char* s) const 
 {
  return draw2dPromtString( VGVEC2(x, y), s );
 };

 //--------------------------------------------------------------

 virtual HRESULT draw2dRay(const VGVEC2* orig, const VGVEC2* nrml) const ;

 
 
 


};
// end class

 
//-------------------------------------------------------------------------
//				 VGDraw3DGeometry_Impl_D3D9
//-------------------------------------------------------------------------

static const DWORD  VG_FVF_3DLINES     =  D3DFVF_XYZ ;
static const DWORD  VG_FVF_HEOSPHERE   = (D3DFVF_XYZ  | D3DFVF_PSIZE);

class VGDraw3DGeometry_Impl_D3D9  : public gb::graphics::visual_geometry::IDraw3DGeometry 
{
public:
	mutable  VGCOLOR m_color;
	IDirect3DDevice9* m_pdevice; // conts ???
	mutable VGSaveRestoreDataD3D9 m_DeviceData;

	//const IDAPLIB_RenderContext* m_pcontext;


	VGDraw3DGeometry_Impl_D3D9(IDirect3DDevice9* pdevice) 
		 : m_pdevice(pdevice)  
	{ 
		assert(pdevice);
		m_color.setWhite();  
	}

	virtual ~VGDraw3DGeometry_Impl_D3D9() 
	{
      releaseInterfaces();
	}

	void releaseInterfaces()
	{
       // none 
	};

#pragma region COLOR_METHODS

	//-----------------------------------------------------------

	virtual HRESULT setColor(const VGCOLOR* color) const { m_color=*color; return 0; };
	virtual HRESULT setColor(const D3DCOLORVALUE* color) const 
	{   
		m_color.r=color->r;
		m_color.g=color->g;
		m_color.b=color->b;
		m_color.a=color->a;
		return 0;
	};

	/*
	virtual HRESULT SetColor(const D3DXCOLOR* color) const 
	{
		m_color.r=color->r;
		m_color.g=color->g;
		m_color.b=color->b;
		m_color.a=color->a;
		return 0;	
	};
	*/

	virtual HRESULT setColor(float r, float g, float b, float a) const 
	{
		m_color.r=r;
		m_color.g=g;
		m_color.b=b;
		m_color.a=a;

		return 0;
	};

	virtual HRESULT setColorRed    ()  const { m_color.setBlack(); m_color.r=1.0f;  return 0; }
	virtual HRESULT setColorGreen  ()  const { m_color.setBlack(); m_color.g=1.0f;  return 0; }
	virtual HRESULT setColorBlue   ()  const { m_color.setBlack(); m_color.b=1.0f;  return 0; }
	virtual HRESULT setColorYellow ()  const { m_color = VGCOLOR(  1.0f,   1.0f,   0.0f,  1.0f);  return 0; }
	virtual HRESULT setColorWhite  ()  const { m_color.setWhite();  return 0; }
	virtual HRESULT setColorGray   ()  const { m_color = VGCOLOR(0.752941f,  0.752941f,  0.752941f,  1.0f);  return 0; } 
	virtual HRESULT setColorPink   ()  const { m_color = VGCOLOR(1.0f,  0.0f,  1.0f,  1.0f);  return 0; }    


#pragma endregion COLOR_METHODS

	//-----------------------------------------------------------------------

	virtual HRESULT draw3dPoint  (const VGVEC3* pos,          float pointSize,  _in_opt  VGMATRIX* pTransf) const ;
	virtual HRESULT draw3dPoint  (float _x, float _y, float _z,    float pointSize,  _in_opt  VGMATRIX* pTransf) const ;
//	virtual HRESULT draw3dPoint  (const VGVEC3*,          float pointSize,  _in_opt  VGMATRIX* pTransf) const ;
	virtual HRESULT draw3dPoints (const VGVEC3* pv, int num, float pointSize,  _in_opt  VGMATRIX* pTransf) const ;

	virtual HRESULT draw3dLine(const VGVEC3* p1, const VGVEC3* p2,_in_opt VGMATRIX* mTransf) const;
	virtual HRESULT draw3dLine(float x1, float y1, float z1,   float x2, float y2, float z2,_in_opt VGMATRIX* mTransf) const;
	virtual HRESULT draw3dLines( const VGVEC3* pv, int num ) const;


	virtual HRESULT draw3dAABB(const VGVEC3* min, const VGVEC3* max,_in_opt VGMATRIX* mTransf) const ;
	virtual HRESULT draw3dAABB(const math::geom3d::AABB* aabb) const 
	{
       return draw3dAABB(&aabb->min, &aabb->max, NULL );
	};

	virtual HRESULT draw3dRay(const VGVEC3* orig, const VGVEC3* normal ,_in_opt VGMATRIX* mTransf) const ;
	virtual HRESULT draw3dRay(float orgX, float orgY, float orgZ, float nrmlX, float nrmlY, float nrmlZ, _in_opt VGMATRIX* mTransf) const ;
	virtual HRESULT draw3dRay(const gb::math::geom3d::Ray* ray, _in_opt VGMATRIX* mTransf ) const ;

	virtual HRESULT draw3dTraingle(const VGVEC3* v1, const VGVEC3* v2, const VGVEC3* v3, 
		_in_opt VGMATRIX* mTransf ) const ;

	virtual HRESULT draw3dTraingle(const gb::math::geom3d::Triangle* tri, 
		_in_opt VGMATRIX* mTransf ) const ;

	virtual HRESULT draw3dArrow(const VGVEC3* src, const VGVEC3* dest, _in_opt VGMATRIX* mTransf ) const ;  

	virtual HRESULT draw3dAxies(const VGVEC3* coord, float axiesLen) const ;

	virtual HRESULT draw3dSolidSphere(const VGVEC3* center, float radius) const ;
 
};
//end class




//------------------------------------------------------------------------------

}// end ns
}// end ns
}// end ns
}// end ns


#endif // #if ( defined(GB_D3D9) && defined(WIN32) )
// end file