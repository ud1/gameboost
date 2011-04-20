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

// ks777: temp   УБРАТЬ !!!
#define MONPRINTB(m) 

//\brief вставить код 
#define anone  assert(false && "NEED INSERT CODE");

namespace gb {
namespace graphics {
namespace visual_geometry {
namespace internal {


	//! \brief цвет для реализаторов визуальной геометрии
	class VGCOLOR  {
	public:
		float r, g, b, a;

		VGCOLOR () { r=g=b=a=1.0f; }
		inline void set(float _r, float _g, float _b, float _a)	{ r=_r; g=_g; b=_b; a=_a; }
		inline void set_rgb(float _r, float _g, float _b)	{ r=_r; g=_g; b=_b;   a=1.0f;  }

  #ifdef GB_COLOR 
		inline void set(const gb::color::Color4f& c) {r=c.r; g=c.g; b=c.b; a=c.a; }
  #endif

#ifdef GB_D3D9
		inline void operator = (const D3DCOLORVALUE& c) { r=c.r; g=c.g; b=c.b; a=c.a; }
#endif

		inline void setWhite() {r=g=b=a=1.0f; }
		inline void setBlack() {r=g=b=0.0f; a=1.0f; }


	  inline void setRed()        {  set_rgb( 1.0f, 0.0f , 0.0f );    }
	  inline void setGreen()      {  set_rgb( 0.0f, 1.0f , 0.0f );  }
	  inline void setBlue()       {  set_rgb( 0.0f, 0.0f , 1.0f );    }
	  inline void setYellow()     {  set_rgb( 1.0f, 1.0f , 0.0f );   }

	  inline void setPink()    { set_rgb(0.737255f,  0.560784f,  0.560784f); }

	  inline void setGray() { set_rgb(0.0f, 0.5f, 0.0f ); }



	};
	// end class VGCOLOR


	class VGVEC2 {
	public:
		float x, y;

		VGVEC2() {x=y=0.0f; }
		VGVEC2(const VGVEC2& v) {x=v.x; y=v.y;}
		VGVEC2(float _x, float _y) {x=_x; y=_y;}
		VGVEC2(const float* pf) {*this = pf; }
		VGVEC2(const POINT& p) { *this = p; }

		inline void operator = (const float* pf) { x=pf[0]; y=pf[1]; }

		inline void operator = (const POINT& p) { x=(float)p.x; y=(float)p.y; }

		inline operator const float*() const {return &x;}
	};


	class VGVEC3 {
	public:
		float x, y, z;

		VGVEC3() {x=y=z=0.0f; }
		VGVEC3(const VGVEC3& v) {x=v.x; y=v.y; z=v.z;}
		VGVEC3(float _x, float _y, float _z) {x=_x; y=_y;z=_z;}
		VGVEC3(const float* pf) {*this = pf; }

		inline void operator = (const float* pf) { x=pf[0]; y=pf[1]; z=pf[2]; }

		inline operator const float*() const {return &x;}
	};

	class VGVEC4 {
	public:
		float x, y, z, w ;

		VGVEC4() {x=y=z=w=0.0f; }
		VGVEC4(const VGVEC4& v) {x=v.x; y=v.y; z=v.z; w=v.w; }
		VGVEC4(float _x, float _y, float _z, float _w) {x=_x; y=_y;z=_z; w=_w;}
		VGVEC4(const float* pf) {*this = pf; }

		inline void operator = (const float* pf) { x=pf[0]; y=pf[1]; z=pf[2]; w=pf[3]; }

		inline operator const float*() const {return &x;}
	};


	class VGMAT4 {
	public:
		union {
			float  _11,_12,_13,_14,   _21,_22,_23,_24,   _31,_32,_33,_34,   _41,_42,_43,_44;
		    float array[16];
		    float m[4][4];
		};

		VGMAT4() {}
		VGMAT4(const float* pf) { *this = pf; }



		inline void operator  = (const float* pf)
		{
			for(int c=0; c<16; c++)
			{
				array[c] = pf[c];
			}
		}

		inline operator const float* () const { return array; }
	};



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
						const VGCOLOR* newColor, 
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
	mutable VGCOLOR m_color;
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


	void ComputeNextPos( ) const;  

	// const

	static const int  CONST_DRWVAL_FONTS_COMM_BETWLINES_OFFSET  = 4;
	static const int  CONST_DRWVAL_NORMALFONT_NEWSTR_OFFSET  = 10; 
	static const int  CONST_DRWVAL_SMALLFONT_NEWSTR_OFFSET =  8; 
	static const int  CONST_DRWVAL_BIGFONT_NEWSTR_OFFSET  = 14; 


HRESULT drawStrEx(  const char* str ) const ;

//===================  IMPLEMENTATION ABSTRACT METHODS ====================
public:

	virtual void setPos(int x, int y) const 
 	{ 
		HRESULT hr =0; 
	m_Rec.left=x;
	m_Rec.top=y;
	m_Rec.right = 2000;
	m_Rec.bottom = 2000;
	m_bChangePos=true;  
	};

	virtual HRESULT setFontSmall() const         { HRESULT hr =0;  m_lastFontSize= FS_SMALL;    return hr;  };
	virtual HRESULT setFontNormal() const        { HRESULT hr =0;  m_lastFontSize= FS_NORMAL;   return hr;  };
	virtual HRESULT setFontBig() const           { HRESULT hr =0;  m_lastFontSize= FS_BIG;      return hr;  };

   //======================================================================

	virtual void setColor( float r, float g, float b, float a ) const 
	//virtual HRESULT setColor( const VGCOLOR& color) const  
	{ 
		m_color.r =  r;
		m_color.g =  g;		
		m_color.b =  b;
		m_color.a =  a;
	};

	virtual void setColorRed()    const   { m_color.setRed();   }
	virtual void setColorGreen()  const   { m_color.setGreen();}
	virtual void setColorBlue()   const   { m_color.setBlue();  }
	virtual void setColorYellow() const   { m_color.setYellow(); }
	virtual void setColorWhite()  const   { m_color.setWhite();  }
	virtual void setColorGray()   const   { m_color.setGray();   }

	virtual void drawS(const char* s) const ;
	virtual void drawF( const char* _Format, ... ) const ;

	virtual void drawBool  (bool  val, const char* promt=NULL) const ;
	virtual void drawInt   (int   val, const char* promt=NULL) const ;
	virtual void drawFloat (float val, const char* promt=NULL) const ;

	virtual void drawIntArray   (const int*   p, int num, const char* promt=NULL) const ;
	virtual void drawFloatArray (const float* p, int num, const char* promt=NULL) const ;

	virtual void drawVec2(const float* vect2, const char* promt=NULL) const ;
	virtual void drawVec3(const float* vect3, const char* promt=NULL) const ;
	virtual void drawVec4(const float* vect4, const char* promt=NULL) const ; 

	//-----------------------------------

	virtual void drawMatrix4x4(const float* matrix4x4, const char* promt=NULL) const ;

	virtual void drawPoint(const POINT pnt, const char* promt=NULL) const 
	{
		if(promt)
		{
			 
			  drawF("%s %i  %i", promt, pnt.x, pnt.y  );
		}
		else
		{
			  drawF("%i  %i",  pnt.x, pnt.y  );
		};

	}

	virtual void drawPoint(int x, int y,   const char* promt=NULL) const 
	{
		POINT pnt = {x, y};
		  drawPoint(pnt, promt);	
	}

	virtual void drawPoint(const float* vec2_pointcoord, const char* promt=NULL) const;





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
 
#ifdef GB_COLOR 
	virtual HRESULT setColor(const gb::color::Color4f& color) const { m_color=color;  }
#endif

	virtual void setColor(const D3DCOLORVALUE& color) const  { m_color=color;   }
 
#ifdef GB_D3DX9
	virtual void setColor(const D3DXCOLOR* color) const 
	{
   	 m_color.r=color->r;
	 m_color.g=color->g;
	 m_color.b=color->b;
	 m_color.a=color->a;
 	
	}
#endif


	virtual void setColor(float r, float g, float b, float a) const 
	{
	 m_color.r=r; m_color.g=g;  m_color.b=b; m_color.a=a; 
	}

  virtual void setColorRed    ()  const { m_color.setBlack();   }
  virtual void setColorGreen  ()  const { m_color.setBlack();   }
  virtual void setColorBlue   ()  const { m_color.setBlack();   }
  virtual void setColorYellow ()  const { m_color.setYellow();  }
  virtual void setColorWhite  ()  const { m_color.setWhite();   }
  virtual void setColorGray   ()  const { m_color.setGray();    } 
  virtual void setColorPink   ()  const { m_color.setPink();    }    
 
#pragma endregion IMPLEM_COLOR_METHODS


	//--------------------  override other  -------------------------------
 


  virtual HRESULT draw2dPoint(float x, float y,    float pointSize) const;

  virtual HRESULT draw2dPoint(int x, int y,        float pointSize) const { return  draw2dPoint( (float)x, (float)y, pointSize ); }

  virtual HRESULT draw2dPoint(const float* vec2_pos,      float pointSize) const 
  { 
	  VGVEC2 v(vec2_pos);
	  return draw2dPoint(v.x, v.y, pointSize ); 
  }

  //  virtual HRESULT draw2dPoint(const float* pos,  float pointSize) const { return draw2dPoint(pos->x, pos->y, pointSize );};
  virtual HRESULT draw2dPoint(const POINT p,  float pointSize) const  { return draw2dPoint( (float)p.x, (float)p.y   , pointSize );  };

  virtual HRESULT draw2dPoints(const float* pv, int num, float pointSize) const ;

  //-----------------------------------------------------------

 virtual HRESULT draw2dLine(const float* p1, const float* p2) const;
 virtual HRESULT draw2dLine(const POINT p1, const POINT p2) const 
 {
    VGVEC2 v1(p1);  VGVEC2 v2(p2);  
  // return draw2dLine( &float*( (float)p1.x, (float)p1.y ), &float*( (float)p2.x, (float)p2.y ) );
   return draw2dLine( v1 , v2 );
 };

 //virtual HRESULT draw2dLine(const float* p1, const float* p2) const 
 //{
 //  return draw2dLine( &float*(p1->x, p1->y),  &float*(p2->x, p2->y) );
 //};


#ifdef GB_MATH
 virtual HRESULT draw2dLine(const gb::math::geom2d::Line* line) const
 {
   return draw2dLine( &float*(line->src.x, line->src.y),  &float*(line->dest.x, line->dest.y) );
 }
#endif

 //virtual HRESULT draw2dLine(int x1, int y1, int x2, int y2) const 
 //{
 //   return draw2dLine( &float*( (float)x1, (float)y1 ),  &float*( (float)x2, (float)y2 ) );
 //};

 virtual HRESULT draw2dLine(float x1, float y1, float x2, float y2) const 
 {
	 VGVEC2 v1(x1,y1);   VGVEC2 v2(x2,y2); 
   return draw2dLine(  v1 , v2 );
 };

  virtual HRESULT draw2dLines(const float* pv, int num) const ;

 //---------------------------------------------------------------------


  virtual HRESULT draw2dRect(const D3DRECT& rect) const ;
  virtual HRESULT draw2dRect(int x1,   int y1,     int x2,   int y2) const 
  {
	  D3DRECT rect = { x1, y1, x2, y2 };
	  return draw2dRect(rect);
  };


 virtual HRESULT draw2dRect(float x1, float y1,   float x2, float y2) const 
 {
 	  D3DRECT rect = { (int)x1, (int)y1, (int)x2, (int)y2 };
	  return draw2dRect(rect); 
 };

 virtual HRESULT draw2dRect(const POINT p1, POINT p2) const 
 {
   	  D3DRECT rect = { p1.x, p1.y,   p2.x, p2.y };
	  return draw2dRect(rect); 
 };

 virtual HRESULT draw2dRect(const RECT rect) const 
 {
      D3DRECT nrect = { rect.left, rect.top, rect.right, rect.bottom   };
	  return draw2dRect(nrect); 
 };

 
#ifdef GB_MATH
 virtual HRESULT draw2dRect(gb::math::geom2d::Rect* rect) const 
 {
	  return draw2dRect( rect->x1, rect->y1,   rect->x2, rect->y2 ); 
 }
#endif


 //--------------------------------------------------------------------

#pragma message("ks777: Сделать базовый метод просто по точкам "  __FILE__ )

 virtual HRESULT draw2dSolidRect(int x1, int y1,   int x2, int y2) const ; //const D3DRECT* rect) const ;

 virtual HRESULT draw2dSolidRect(const POINT& p1, const POINT& p2) const 
 {
	 return draw2dSolidRect( p1.x,   p1.y,     p2.x,   p2.y  );
 };

 virtual HRESULT draw2dSolidRect(const D3DRECT& rect) const
 {
	 return draw2dSolidRect(rect.x1, rect.y1, rect.x2, rect.y2  );
 };

 virtual HRESULT draw2dSolidRect(const RECT& rect) const 
 {
	 return draw2dSolidRect( rect.left, rect.top, rect.right, rect.bottom  );
 };

#ifdef GB_MATH
 virtual HRESULT draw2dSolidRect(const gb::math::geom2d::Rect& rect) const ;
#endif

 //------------------------------------------------------------

 virtual HRESULT draw2dCircle(const float* pos, float radius) const ;

 virtual HRESULT draw2dCircle(float x, float y,       float radius) const 
 {
	 VGVEC2 v(x,y);
   return draw2dCircle( v , radius );
 }

 //virtual HRESULT draw2dCircle(int x, int y,           float radius) const 
 //{
//   return draw2dCircle( &float*( (float)x, (float)y) , radius );
 //};

 virtual HRESULT draw2dCircle(const POINT pos,        float radius) const 
 {
	 VGVEC2 v(pos);
   return draw2dCircle( v, radius); // &float*((float)pos.x, (float)pos.y) , radius );
 }

 #ifdef GB_MATH
 virtual HRESULT draw2dCircle(const gb::math::geom2d::Circle*   c) const 
 {
   return draw2dCircle( &float*( c->center.x, c->center.y ) , c->radius );
 }
#endif

 //-----------------------------------------------------------

 virtual HRESULT draw2dAxies(const float* vec2_coord) const ;
 virtual HRESULT draw2dAxies(float x, float y) const 
 {
	 VGVEC2 v( x ,y );
    return draw2dAxies(  v );
 }

 //virtual HRESULT draw2dAxies(int x, int y) const 
 //{
 //   return draw2dAxies( float*( (float)x   ,  (float)y )  ); 
 //};

 virtual HRESULT draw2dAxies(const POINT p) const 
 {
    return draw2dAxies(  VGVEC2(p) ); 
 }

 //virtual HRESULT draw2dAxies(const float* coord) const 
 //{
 //    return draw2dAxies( float*( coord.x   ,  coord.y )  ); 
 //};


 //------------------------------------------------------------

 virtual HRESULT draw2dTriangle(const float* p1, const float* p2,const float* p3) const ;


 virtual HRESULT draw2dTriangle(const POINT& p1, const POINT& p2, const POINT& p3) const 
 {
  return draw2dTriangle( 
	  VGVEC2((float)p1.x , (float)p1.y), 
	  VGVEC2((float)p2.x , (float)p2.y), 
	  VGVEC2((float)p3.x , (float)p3.y)  
	  );
 };

 //-----------------------------------------------------------

 virtual HRESULT draw2dSolidTriangle(const float* p1, const float* p2,const float* p3) const ;

 //-------------------------------------------------------

 virtual HRESULT draw2dPromtString(const float* vec2_coord, const char* s) const;
 virtual HRESULT draw2dPromtString(const   POINT p,         const char* s) const 
 {
	 VGVEC2 v( (float)p.x, (float)p.y );
   return draw2dPromtString( v, s );
 }

 virtual HRESULT draw2dPromtString(int x,   int y,          const char* s) const 
 {
	VGVEC2 v( (float)x, (float)y );
   return draw2dPromtString(  v , s );
 }

 virtual HRESULT draw2dPromtString(float x, float y,        const char* s) const 
 {
   VGVEC2 v(  x, y );
  return draw2dPromtString( v, s );
 }

 //--------------------------------------------------------------

 virtual HRESULT draw2dRay(const float* orig, const float* normal) const ;

 
 
 


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
	IDirect3DDevice9* m_pdevice;  
	mutable VGSaveRestoreDataD3D9 m_DeviceData;
 
	VGDraw3DGeometry_Impl_D3D9(IDirect3DDevice9* pdevice) : m_pdevice(pdevice)  
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
	}

#pragma region COLOR_METHODS


//-------------------------------------------------------------------------
//         implementation abstract methods
//-------------------------------------------------------------------------

#ifdef GB_COLOR
  //! \brief Установить цвет отрисовки 
	virtual HRESULT setColor(const gb::color::Color4f& color) const =0;
#endif



	virtual void setColor(const D3DCOLORVALUE* color) const 
	{   
		m_color.r=color->r;	m_color.g=color->g;	m_color.b=color->b;	m_color.a=color->a;
	}

	
#ifdef GB_D3DX9
	virtual void setColor(const D3DXCOLOR* color) const 
	{
		m_color.r=color->r;
		m_color.g=color->g;
		m_color.b=color->b;
		m_color.a=color->a;	
	}
#endif
	

	virtual void setColor(float r, float g, float b, float a) const 
	{
		m_color.r=r; m_color.g=g; m_color.b=b; m_color.a=a;
	}

  virtual void setColorRed    ()  const { m_color.setBlack();   }
  virtual void setColorGreen  ()  const { m_color.setBlack();   }
  virtual void setColorBlue   ()  const { m_color.setBlack();   }
  virtual void setColorYellow ()  const { m_color.setYellow();  }
  virtual void setColorWhite  ()  const { m_color.setWhite();   }
  virtual void setColorGray   ()  const { m_color.setGray();    } 
  virtual void setColorPink   ()  const { m_color.setPink();    } 

#pragma endregion COLOR_METHODS

	//---------------------------------------------------------------------

  virtual HRESULT  draw3dPoint(const float* vec3_coord, float  pointSize ) const
  {
	  HRESULT hr = 0;
	  assert(m_pdevice);
 
	  hr |= draw3dPoints( vec3_coord, 1, pointSize );

	  return hr;
  }



	virtual HRESULT draw3dPoint  (float _x, float _y, float _z,    float pointSize) const 
	{
		HRESULT hr = 0;
		assert(m_pdevice);

		hr |= draw3dPoint( VGVEC3(_x, _y, _z), pointSize );

		return hr;
	}


//	virtual HRESULT draw3dPoint  (const float**,          float pointSize,  _in_opt  float* * pTransf) const ;
	virtual HRESULT draw3dPoints (const float* pv, int num, float pointSize) const ;

	virtual HRESULT draw3dLine(const float* p1, const float* p2) const;
	virtual HRESULT draw3dLine(float x1, float y1, float z1,   float x2, float y2, float z2) const;
	virtual HRESULT draw3dLines( const float* pv, int num ) const;


	virtual HRESULT draw3dAABB(const float* min, const float* max) const ;

#ifdef GB_MATH
	virtual HRESULT draw3dAABB(const math::geom3d::AABB* aabb) const 
	{
       return draw3dAABB(&aabb->min, &aabb->max  );
	}
#endif

	virtual HRESULT draw3dRay(const float* orig, const float* normal ) const ;
	virtual HRESULT draw3dRay(float orgX, float orgY, float orgZ, float nrmlX, float nrmlY, float nrmlZ) const ;

#ifdef GB_MATH
	virtual HRESULT draw3dRay(const gb::math::geom3d::Ray* ray) const ;
#endif

	virtual HRESULT draw3dTraingle(const float* v1, const float* v2, const float* v3) const ;

#ifdef GB_MATH
	virtual HRESULT draw3dTraingle(const gb::math::geom3d::Triangle* tri) const ;
#endif

	virtual HRESULT draw3dArrow(const float* src, const float* dest) const ;  

	virtual HRESULT draw3dAxies(const float* coord, float axiesLen) const ;

	virtual HRESULT draw3dSolidSphere(const float* center, float radius) const ;
 
};
//end class




//------------------------------------------------------------------------------

}// end ns
}// end ns
}// end ns
}// end ns


#endif // #if ( defined(GB_D3D9) && defined(WIN32) )
// end file