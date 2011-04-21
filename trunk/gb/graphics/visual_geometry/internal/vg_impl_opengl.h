#ifdef GB_OPENGL

#include <gb/graphics/visual_geometry/visual_geometry.h>
#include <gb/graphics/visual_geometry/internal/vg_impl_common.h>

#define GB_MATH
#include <gb/math/math.h>


// opengl include
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLAux.h>

#include <stdarg.h>
#include <gb/str/formater.h>
#include <assert.h>

#define xxxx  assert(false&& "NEED INSERT CODE !!!");


namespace gb {
namespace graphics {
namespace visual_geometry {
namespace internal {

//-------------------------------------------------------------------------------


//! Сохраняет и восстанавливает состояние OpenGL
class VGSaveRestoreDataOpenGL {
public:

	VGSaveRestoreDataOpenGL() 
	{

	}

	virtual ~VGSaveRestoreDataOpenGL() { }


  //! Cохранение состояния OpenGL
  void SaveDeviceData(const VGCOLOR* newColor = NULL, 
						float pointSize=1.0f  )
  {
  
  
  
  }

  //! восстановление состояния OpenGL
  void RestoreDeviceData() 
  {
  
  
  }


};




//----------------------------------------------------------------------

class VGDrawValuesImpl_ogl : public gb::graphics::visual_geometry::IDrawValues {
public:
	mutable VGCOLOR m_color;
	mutable POINT m_pos;
    mutable VGSaveRestoreDataOpenGL  m_OpenGlData; 

          VGDrawValuesImpl_ogl() { }
virtual  ~VGDrawValuesImpl_ogl() { }

//------------------------------------------------------------
virtual void setPos( int x, int y ) const
{
  m_pos.x = x; 
  m_pos.y = y;
}

#ifdef GB_COLOR
//! \brief Установить цвет отрисовки 
virtual void setColor(const gb::color::Color4f& c) const 
{
	m_color.r=c.r; m_color.g=c.g; m_color.b=c.b; m_color.a=c.a;
}
#endif


virtual void setColor( float r, float g, float b, float a ) const 
{ 
	m_color.r = r; 	m_color.g = g; m_color.b = b; m_color.a = a;
}

#ifdef GB_COLOR
   virtual HRESULT setColor(const gb::color::Color4f& c) const 
   {
	   m_color.r = c.r;
	   m_color.g = c.g;
	   m_color.b = c.b;
	   m_color.a = c.a;
   }
#endif

virtual void setColorRed()    const   { m_color.setRed();    }
virtual void setColorGreen()  const   { m_color.setGreen();  }
virtual void setColorBlue()   const   { m_color.setBlue();   }
virtual void setColorYellow() const   { m_color.setYellow(); }
virtual void setColorWhite()  const   { m_color.setWhite();  }
virtual void setColorGray()   const   { m_color.setGray();   }
virtual void setColorPink()   const   { m_color.setPink();   }  

//-----------------------------------------------


virtual void drawS(const char* s) const 
{
	xxxx
}

virtual void drawF(const char* _Format, ... ) const 
{
	xxxx
 
	//static char ss[8192];
	//ss[0] = 0;

	//va_list ap;
	//va_start(ap, _Format);
	//vsprintf(ss, _Format, ap);
	//va_end(ap);
	//drawS(ss);

 
#pragma message("NEED CHECK  CODE"  __FILE__)
}

 
virtual void drawBool  (bool  val, const char* promt=NULL) const 
{
  char buf[1024];
  buf[0] = 0;

  if (promt)
  {
    strcat(buf, promt);
  };

  if (val)
  {
    strcat(buf, "true");
  }
  else
  {
    strcat(buf, "fasle");
  };

 drawS(buf);

}
 	
virtual void drawInt   (int   val, const char* promt=NULL) const 
{
 char buf[1024];
  buf[0] = 0;

  if (promt)
  {
    strcat(buf, promt);
  };

  char bufdigit[32];
  bufdigit[0] = 0;

  sprintf(bufdigit, "%i", val);
  strcat(buf, bufdigit);
  drawS(buf);

}
 
virtual void drawFloat (float val, const char* promt=NULL) const 
{
 char buf[1024];
  buf[0] = 0;

  if (promt)
  {
    strcat(buf, promt);
  };

  char bufdigit[32];
  bufdigit[0] = 0;

  sprintf(bufdigit, "%f", val);
  strcat(buf, bufdigit);
 drawS(buf);

}


//---------------------------------------------------------------------

virtual void drawIntArray   (const int*   p, int num, const char* promt=NULL) const 
{
 static char ss[2048];
  ss[0] = 0;

  if (promt)
  {
    strcat(ss, promt);
    strcat(ss, " ");
  };

  char buf[32];

  for (int c = 0; c < num; c++)
  {
    buf[0] = 0;
    int curr = *(p + c);
    sprintf(buf, "%i", curr);
    strcat(ss, buf);
    strcat(ss, " ");

  };

  drawS(ss);
}

virtual void drawFloatArray (const float* p, int num, const char* promt=NULL) const 
{
 static char ss[2048];
  ss[0] = 0;

  if (promt)
  {
    strcat(ss, promt);
    strcat(ss, " ");
  };

  char buf[32];

  for (int c = 0; c < num; c++)
  {
    buf[0] = 0;
    float curr = *(p + c);
    sprintf(buf, "%f", curr);
    strcat(ss, buf);
    strcat(ss, " ");

  };

  drawS(ss);

}

//--------------------------------------------------------

#pragma message("ks777:  Перенести в общее  " __FILE__)
//==========================================================
static void __StrFromFloatForDrawVec(char *buf, const FLOAT f)
{
  _gcvt((double)f, 10, buf);
}

	virtual void drawVec2(const float* vect2, const char* promt=NULL) const 
	{
	 static char sdigit[16];
  sdigit[0] = 0;

  static std::string str;
  str = "";

  if (promt)
  {
    str += promt;
  };

  VGVEC2 v(vect2);

  //str += "x= ";
  __StrFromFloatForDrawVec(sdigit, v.x);
  str += sdigit;
  str += "  ";


  __StrFromFloatForDrawVec(sdigit, v.y);
  str += sdigit;

drawS(str.c_str());

	}

	virtual void drawVec3(const float* vect3, const char* promt=NULL) const 
	{
	 static char sdigit[16];
  sdigit[0] = 0;

  static std::string str;
  str = "";

  if (promt)
  {
    str += promt;
  };

    VGVEC3 v(vect3);


  __StrFromFloatForDrawVec(sdigit, v.x);
  str += sdigit;
  str += "  ";


  __StrFromFloatForDrawVec(sdigit, v.y);
  str += sdigit;


  __StrFromFloatForDrawVec(sdigit, v.y);
  str += sdigit;

  drawS(str.c_str());
 
	}

	virtual void drawVec4(const float* vect4, const char* promt=NULL) const 
	{
		static char sdigit[16];
		sdigit[0] = 0;

		static std::string str;
		str = "";

		if (promt)
		{
			str += promt;
		};

		VGVEC4 v(vect4);

		__StrFromFloatForDrawVec(sdigit, v.x);
		str += sdigit;
		str += "  ";


		__StrFromFloatForDrawVec(sdigit, v.y);
		str += sdigit;


		__StrFromFloatForDrawVec(sdigit, v.z);
		str += sdigit;


		__StrFromFloatForDrawVec(sdigit, v.w);
		str += sdigit;


		drawS(str.c_str());

	}


#pragma message("ks777:  Перенести в общее  " __FILE__)
	//=========================================================================
	static void __FormatFloatMatrix(char *buf, float f)
	{
		*buf = 0;

		char *pCurrBuffer = buf;

		if (f >= 0.0f)
		{
			strcat(buf, " ");
			pCurrBuffer++;

		};

		static char ssformat[8];
		ssformat[0] = 0;
		strcat(ssformat, "%");

		char tbuf[32];

		static int d0 = 0;
		gb::str::Formater::intToCstr(tbuf, 32, d0, false);
		strcat(ssformat, tbuf);

		static int d1 = 1;
		gb::str::Formater::intToCstr(tbuf, 32, d1, false);
		strcat(ssformat, tbuf);
		strcat(ssformat, ".");

		static int d2 = 6;
		gb::str::Formater::intToCstr(tbuf, 32, d2, false);
		strcat(ssformat, tbuf);



		// format
		sprintf(pCurrBuffer, "%01.6f", f); //  ssformat , f );


		const int STRLEN = (int)strlen(buf);

		static const int ALIGN = 10;
		for (int c = 0; c < ALIGN - STRLEN; c++)
		{
			strcat(buf, " ");
		};

		// debug
		// printf("len: %d\n", strlen(buf));
	}

virtual void drawMatrix4x4(const float* matrix4x4, const char* promt=NULL) const 
{
	static char sdigit[16];
	sdigit[0] = 0;

	static std::string str;
	str = "";

	if (promt)
	{
		str += promt;
		str += "\n";
	};

	const VGMAT4 mat (matrix4x4);
	const VGMAT4* m = &mat;


	// row 1
	__FormatFloatMatrix(sdigit, m->_11);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_12);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_13);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_14);
	str += sdigit;
	str += "\n";


	// row 2
	__FormatFloatMatrix(sdigit, m->_21);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_22);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_23);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_24);
	str += sdigit;
	str += "\n";


	// row 3
	__FormatFloatMatrix(sdigit, m->_31);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_32);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_33);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_34);
	str += sdigit;
	str += "\n";


	// row 4
	__FormatFloatMatrix(sdigit, m->_41);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_42);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_43);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_44);
	str += sdigit;
	str += "\n";

	drawS(str.c_str());

}

virtual void drawMatrix2x2(const float* matrix2x2, const char* promt=NULL) const
{
	static char sdigit[16];
	sdigit[0] = 0;

	static std::string str;
	str = "";

	if (promt)
	{
		str += promt;
		str += "\n";
	};

	const gb::math::base::mat22_s mat =  (matrix2x2);
	const gb::math::base::mat22_s* m = &mat;


	// row 1
	__FormatFloatMatrix(sdigit, m->_11);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_12);
	str += sdigit;
	str += "\n";



	// row 2
	__FormatFloatMatrix(sdigit, m->_21);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_22);
	str += sdigit;
	str += "\n";

	drawS(str.c_str());

}

virtual void drawMatrix3x3(const float* matrix3x3, const char* promt=NULL) const 
{
	static char sdigit[16];
	sdigit[0] = 0;

	static std::string str;
	str = "";

	if (promt)
	{
		str += promt;
		str += "\n";
	};

	const gb::math::base::mat33_s mat (matrix3x3);
	const gb::math::base::mat33_s* m = &mat;


	// row 1
	__FormatFloatMatrix(sdigit, m->_11);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_12);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_13);
	str += "\n";



	// row 2
	__FormatFloatMatrix(sdigit, m->_21);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_22);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_23);
	str += sdigit;
	str += "\n";



	// row 3
	__FormatFloatMatrix(sdigit, m->_31);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_32);
	str += sdigit;
	str += "  ";

	__FormatFloatMatrix(sdigit, m->_33);
	str += sdigit;
	str += "\n";

 

	drawS(str.c_str());

}

//-----------------------------------------------------

virtual void drawPoint(const POINT pnt,  const char* promt=NULL) const 
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

virtual void drawPoint(int x, int y,     const char* promt=NULL) const 
{
		POINT pnt = {x, y};
		  drawPoint(pnt, promt);	
}

virtual void drawPoint(const float* vec2_point, const char* promt=NULL) const 
{
	VGVEC2 pos(vec2_point);
	drawPoint(gb::math::scalar::round(pos.x) , gb::math::scalar::round(pos.y) , promt);
}

 





};
// end class

 

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

class VGDraw2DGeometry_Impl_ogl : public gb::graphics::visual_geometry::IDraw2DGeometry {
public:
	mutable VGCOLOR  m_color;
    mutable VGSaveRestoreDataOpenGL  m_OpenGlData; 

          VGDraw2DGeometry_Impl_ogl() { }
virtual  ~VGDraw2DGeometry_Impl_ogl() { }

#ifdef GB_COLOR
//! \brief Установить цвет отрисовки 
virtual void setColor(const gb::color::Color4f& c) const 
{
  m_color.r=c.r; m_color.g=c.g; m_color.b=c.b; m_color.a=c.a;
};
#endif


virtual void setColor( float r, float g, float b, float a ) const 
{ 
	m_color.r = r; 	m_color.g = g; m_color.b = b; m_color.a = a;
}

#ifdef GB_COLOR
virtual HRESULT setColor(const gb::color::Color4f& color) const =0;
#endif

virtual void setColorRed()    const   { m_color.setRed();    }
virtual void setColorGreen()  const   { m_color.setGreen();  }
virtual void setColorBlue()   const   { m_color.setBlue();   }
virtual void setColorYellow() const   { m_color.setYellow(); }
virtual void setColorWhite()  const   { m_color.setWhite();  }
virtual void setColorGray()   const   { m_color.setGray();   }
virtual void setColorPink()   const   { m_color.setPink();   }  

//-----------------------------------------------
virtual HRESULT draw2dPoint(float x, float y,  float pointSize) const 
{
 gb::math::base::vec2_s v(x,y);
  return draw2dPoint(&v.x , pointSize);

}

virtual HRESULT draw2dPoint(const float* vec2_coord,  float pointSize) const 
{
	m_OpenGlData.SaveDeviceData();
	gb::math::base::vec2_s v = vec2_coord;
xxxx
  m_OpenGlData.RestoreDeviceData();
  return 0;
}
// virtual HRESULT Draw2dPoint(const float* pos,  float pointSize) const =0;
virtual HRESULT draw2dPoint(const POINT p,  float pointSize) const 
{
  gb::math::base::vec2_s v;
  v.x = (float)p.x;
  v.y = (float)p.y;
  return draw2dPoint(&v.x , pointSize);
}

//-------------------------------------------------
 virtual HRESULT draw2dPoints(const float* vec2Array_points, int num, float pointSize) const
 {
	const gb::math::base::vec2_s* pv = (gb::math::base::vec2_s*)vec2Array_points;
 	m_OpenGlData.SaveDeviceData();

xxxx


    m_OpenGlData.RestoreDeviceData();
return 0;
 };
//-----------------------------------------------

 virtual HRESULT draw2dLine(const float* vec2_p1, const float* vec2_p2) const 
 {
   const gb::math::base::vec2_s v1 = vec2_p1;
   const gb::math::base::vec2_s v2 = vec2_p2;

    m_OpenGlData.SaveDeviceData();
    xxxx
	m_OpenGlData.RestoreDeviceData();
	return 0;
 }

 virtual HRESULT draw2dLine(const POINT p1, const POINT p2) const 
 {
	 gb::math::base::vec2_s v1( (float)p1.x , (float)p1.y );
	 gb::math::base::vec2_s v2( (float)p2.x , (float)p2.y );
	   return draw2dLine( v1 , v2 ); 
 }

#ifdef GB_MATH
 virtual HRESULT draw2dLine(const math::geom2d::Line* line) const 
 {
   return  draw2dLine(line->src , line->dest); 
 }
#endif 

 //virtual HRESULT draw2dLine(int x1,   int y1,      int x2,   int y2   ) const =0;
 virtual HRESULT draw2dLine(float x1, float y1,    float x2, float y2 ) const 
 {
	 gb::math::base::vec2_s v1( x1, y1 );
	 gb::math::base::vec2_s v2( x2, y2 );
	 return draw2dLine( v1 , v2 );
 }

//-------------------------------------------------------------------------
 virtual HRESULT draw2dLines(const float* vec2Array_points, int num) const 
 {
  xxxx
	  return 0;
 }

 //-----------------------------------------------------

 virtual HRESULT draw2dRect(const float* vec2_min, const float* vec2_max) const 
 {
	 gb::math::base::vec2_s vmin = vec2_min;
	 gb::math::base::vec2_s vmax = vec2_max;
 xxxx

	 m_OpenGlData.SaveDeviceData();

     m_OpenGlData.RestoreDeviceData();
	 return 0;
 }
 
 virtual HRESULT draw2dRect(float x1, float y1,   float x2, float y2) const 
 {
	 gb::math::base::vec2_s v1(x1,y1);
	 gb::math::base::vec2_s v2(x2,y2);
     return draw2dRect(v1,v2); 
 }

 virtual HRESULT draw2dRect(const POINT& p1, POINT& p2) const 
 {
	 gb::math::base::vec2_s v1( (float)p1.x , (float)p1.y  );
	 gb::math::base::vec2_s v2( (float)p2.x , (float)p2.y  );
	 return draw2dRect(v1,v2); 
 }

 virtual HRESULT draw2dRect(const RECT& rect) const 
 {
	 gb::math::base::vec2_s v1( (float)rect.left  , (float)rect.top   );
	 gb::math::base::vec2_s v2( (float)rect.right  , (float)rect.bottom   );
	  return draw2dRect(v1,v2); 
 }

#ifdef GB_MATH
 // ИЗМЕНИЛ !!!!
 virtual HRESULT draw2dRect(gb::math::geom2d::Rect& rect) const 
 {
  return draw2dRect( rect.x1, rect.y1, rect.x2, rect.y2 );
 }
#endif

 //--------------------------------------------------------------

 //-----------------------------------------------  

#ifdef GB_D3D9
 virtual HRESULT draw2dSolidRect(const D3DRECT& rect) const 
 {
    return draw2dSolidRect( rect.x1 , rect.y1 , rect.x2 , rect.y2 );
 }
#endif

 virtual HRESULT draw2dSolidRect(const float* vec2_min, const float* vec2_max) const 
 {
	 gb::math::base::vec2_s v1 =  vec2_min;
	 gb::math::base::vec2_s v2 =  vec2_max;
	 m_OpenGlData.SaveDeviceData();
	
	 m_OpenGlData.RestoreDeviceData();
	 return   0;
 }

 virtual HRESULT draw2dSolidRect(const POINT& p1, const POINT& p2) const 
 {
	 gb::math::base::vec2_s v1 ( (float)p1.x , (float)p1.y );
	 gb::math::base::vec2_s v2 ( (float)p2.x , (float)p2.y );
	 draw2dSolidRect(v1,v2);
	 return   0;
 }

 virtual HRESULT draw2dSolidRect(int x1, int y1,   int x2, int y2) const 
 {
	 gb::math::base::vec2_s v1 ( (float)x1 , (float)y1 );
	 gb::math::base::vec2_s v2 ( (float)x2 , (float)y2 );
	 draw2dSolidRect(v1,v2);
	 return   0;
 }
 virtual HRESULT draw2dSolidRect(const RECT& rect) const 
 {
	 gb::math::base::vec2_s v1 ( (float)rect.left  , (float)rect.top    );
	 gb::math::base::vec2_s v2 ( (float)rect.bottom  , (float)rect.right );
	 draw2dSolidRect(v1,v2);
	 return   0;
 }

 //---------------------------------------------

#ifdef GB_MATH
 virtual HRESULT draw2dSolidRect(const gb::math::geom2d::Rect& rect) const
 {
    return  draw2dSolidRect( rect.x1, rect.y1,  rect.x2, rect.y2 );
 }
#endif

 //--------------------------------------------

 virtual HRESULT draw2dCircle(const float* vec2_pos, float radius) const 
 {
  xxxx
  return 0;
 }

 virtual HRESULT draw2dCircle(float x, float y,       float radius) const 
 {
	 gb::math::base::vec2_s v(x,y);
    return draw2dCircle(v,radius);
 }

 virtual HRESULT draw2dCircle(const POINT pos,        float radius) const 
 {
    gb::math::base::vec2_s v( (float)pos.x , (float)pos.y );
    return draw2dCircle( v , radius );
 }

#ifdef GB_MATH
 virtual HRESULT draw2dCircle(const math::geom2d::Circle&   c) const 
 {
    return draw2dCircle( c.center , c.radius ); 
 }
#endif
//----------------------------------------------

 virtual HRESULT draw2dAxies(const float* vec2_coord) const 
 {
	 gb::math::base::vec2_s  v = vec2_coord;
    xxxx

		return 0;
 }

 virtual HRESULT draw2dAxies(float x, float y) const 
 {
	 gb::math::base::vec2_s  v (x,y);
	 return draw2dAxies(v);
 }

 virtual HRESULT draw2dAxies(const POINT p) const
 {
   gb::math::base::vec2_s  v ( (float)p.x , (float)p.y );
	 return draw2dAxies(v);
 }

 //---------------------------------------------------------------------

 virtual HRESULT draw2dTriangle(const float* vec2_p1, const float* vec2_p2, const float* vec2_p3) const 
 {
   gb::math::base::vec2_s  v1 = vec2_p1;
   gb::math::base::vec2_s  v2 = vec2_p2;
   gb::math::base::vec2_s  v3 = vec2_p3;
     return  draw2dTriangle(v1,v2,v3);
 }

 virtual HRESULT draw2dTriangle(const POINT& p1, const POINT& p2, const POINT& p3) const 
 {
   gb::math::base::vec2_s  v1 ( (float)p1.x , (float)p1.y );
   gb::math::base::vec2_s  v2 ( (float)p2.x , (float)p2.y );
   gb::math::base::vec2_s  v3 ( (float)p3.x , (float)p3.y );
     return  draw2dTriangle( v1 , v2 , v3 );
 }

 //--------------------------------------------------------------

 virtual HRESULT draw2dSolidTriangle(const float* vec2_p1, const float* vec2_p2, const float* vec2_p3) const
 {
   gb::math::base::vec2_s  v1 = vec2_p1;
   gb::math::base::vec2_s  v2 = vec2_p2;
   gb::math::base::vec2_s  v3 = vec2_p3;

   xxxx
	   return 0;
 }
 
 //-------------------------------------------------------------

 virtual HRESULT draw2dPromtString(const float* vec2_coord, const char* s) const
 {
 xxxx
	 return 0;
 }

 virtual HRESULT draw2dPromtString(const   POINT p,         const char* s) const
 {
   gb::math::base::vec2_s v( (float)p.x , (float)p.y  );
	 return draw2dPromtString(v, s);

 }

 virtual HRESULT draw2dPromtString(int x,   int y,          const char* s) const
 {
   gb::math::base::vec2_s v( (float)x , (float)y );
	 return draw2dPromtString(v, s);
 }

 virtual HRESULT draw2dPromtString(float x, float y,        const char* s) const 
 {
     gb::math::base::vec2_s v(  x , y  );
	 return draw2dPromtString(v, s);
 }
	    
 //----------------------------------------------------------------------

 virtual HRESULT draw2dRay(const float* vec2_orig, const float* vec2_normal) const
 {
   xxxx
	m_OpenGlData.SaveDeviceData();
	m_OpenGlData.RestoreDeviceData();

   return 0; 
 }




};

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------


class VGDraw3DGeometry_Impl_ogl  : public gb::graphics::visual_geometry::IDraw3DGeometry {
public:
          VGDraw3DGeometry_Impl_ogl() { }
virtual  ~VGDraw3DGeometry_Impl_ogl() { }

mutable VGCOLOR                  m_color;
mutable VGSaveRestoreDataOpenGL  m_OpenGlData; 


virtual void setColor( float r, float g, float b, float a ) const 
{ 
	m_color.r = r; 
	m_color.g = g; 
	m_color.b = b;
	m_color.a = a;
}

#ifdef GB_COLOR
  virtual HRESULT setColor(const gb::color::Color4f& color) const =0;
#endif

virtual void setColorRed()    const   { m_color.setRed();    }
virtual void setColorGreen()  const   { m_color.setGreen();  }
virtual void setColorBlue()   const   { m_color.setBlue();   }
virtual void setColorYellow() const   { m_color.setYellow(); }
virtual void setColorWhite()  const   { m_color.setWhite();  }
virtual void setColorGray()   const   { m_color.setGray();   }
virtual void setColorPink()   const   { m_color.setPink();   }  


virtual HRESULT  draw3dPoint(const float* vec3_coord, float  pointSize ) const
{
	  draw3dPoints( vec3_coord, 1, pointSize );

	return  0;
}

virtual HRESULT draw3dPoint  (float _x, float _y, float _z,    float pointSize) const 
{
	 draw3dPoint( VGVEC3(_x, _y, _z), pointSize );
	return 0;
}


	virtual HRESULT draw3dPoints (const float* pv, int num, float pointSize) const 
	{
		m_OpenGlData.SaveDeviceData();
		xxxx
			m_OpenGlData.RestoreDeviceData();
	  return 0;
	};

	virtual HRESULT draw3dLine(const float* p1, const float* p2) const
	{
   m_OpenGlData.SaveDeviceData();
xxxx
	m_OpenGlData.RestoreDeviceData();
	 return 0;
	};

	virtual HRESULT draw3dLine(float x1, float y1, float z1,   float x2, float y2, float z2) const
	{
		VGVEC3 v1(x1, y1, z1);    VGVEC3 v2(x2, y2, z2);
       return draw3dLine( v1 , v2 );
	};

	virtual HRESULT draw3dLines( const float* vec3_arrayCoord, int num ) const
	{
		m_OpenGlData.SaveDeviceData();
		xxxx
			m_OpenGlData.RestoreDeviceData();
      return 0;
	};


	virtual HRESULT draw3dAABB(const float* vec3_min, const float* vec3_max) const 
	{
		m_OpenGlData.SaveDeviceData();
		xxxx
		m_OpenGlData.RestoreDeviceData();
		return 0;
	};

#ifdef GB_MATH
	virtual HRESULT draw3dAABB(const math::geom3d::AABB& aabb) const 
	{
       return draw3dAABB(aabb.min, aabb.max  );
	}
#endif

	virtual HRESULT draw3dRay(const float* vec3_orig, const float* vec3_normal ) const 
	{
		gb::math::base::vec3_s orig = vec3_orig;
		gb::math::base::vec3_s norm = vec3_normal;
		norm.normalize();
		

		m_OpenGlData.SaveDeviceData();
		xxxx
			m_OpenGlData.RestoreDeviceData();
		return 0;
	};

	virtual HRESULT draw3dRay(float orgX, float orgY, float orgZ, float nrmlX, float nrmlY, float nrmlZ) const 
	{
		VGVEC3 o(orgX, orgY, orgZ);  VGVEC3 d(nrmlX, nrmlY, nrmlZ); 
       return  draw3dRay( o , d );
	};

#ifdef GB_MATH
	virtual HRESULT draw3dRay(const gb::math::geom3d::Ray& ray) const 
	{

      return  draw3dRay ( ray.orig , ray.dir );
	}
#endif

	//------------------------------------------------------------------

	virtual HRESULT draw3dTraingle(const float* vec3_v1, const float* vec3_v2, const float* vec3_v3) const 
	{
    		VGVEC3 varr[4];
			varr[0] = VGVEC3(vec3_v1);
			varr[1] = VGVEC3(vec3_v2);
			varr[2] = VGVEC3(vec3_v3);
			varr[0] = VGVEC3(vec3_v1);

		m_OpenGlData.SaveDeviceData();
		xxxx
			m_OpenGlData.RestoreDeviceData();  
       return 0;
	};

#ifdef GB_MATH
	virtual HRESULT draw3dTraingle(const gb::math::geom3d::Triangle& tri) const 
	{
   xxxx
	   return 0;
	}
#endif

	virtual HRESULT draw3dArrow(const float* src, const float* dest) const 
	{
		xxxx
			       return 0;
	};  

	virtual HRESULT draw3dAxies(const float* coord, float axiesLen) const 
	{
		xxxx
	 return 0;
	};

	virtual HRESULT draw3dSolidSphere(const float* center, float radius) const
	{
		xxxx
	 return 0;
	};
 

};
 


//-------------------------------------------------------------------------

} // end ns
} // end ns
} // end ns
} // end ns

#endif // #ifdef GB_OPENGL
// end file