#ifdef GB_OPENGL

#include <gb/graphics/visual_geometry/visual_geometry.h>

#include <gb/graphics/visual_geometry/internal/vg_impl_common.h>
#include <gb/math/math.h>


// opengl include
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLAux.h>

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

	VGSaveRestoreDataOpenGL() {


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



class VGImpl_OpenGL  : public gb::graphics::visual_geometry::IDrawValues {
public:

          VGImpl_OpenGL() {}
virtual  ~VGImpl_OpenGL() {}



};

//------------------------------------------------------------------------------------------

class VGDrawValuesImpl_ogl : public gb::graphics::visual_geometry::IDrawValues {
public:
          VGDrawValuesImpl_ogl() { }
virtual  ~VGDrawValuesImpl_ogl() { }





};

//------------------------------------------------------------------------------------------

class VGDraw2DGeometry_Impl_ogl : public gb::graphics::visual_geometry::IDraw2DGeometry {
public:
          VGDraw2DGeometry_Impl_ogl() { }
virtual  ~VGDraw2DGeometry_Impl_ogl() { }




};

//------------------------------------------------------------------------------------------


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
	virtual HRESULT draw3dAABB(const math::geom3d::AABB* aabb) const 
	{
       return draw3dAABB(&aabb->min, &aabb->max  );
	}
#endif

	virtual HRESULT draw3dRay(const float* vec3_orig, const float* vec3_normal ) const 
	{
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
	virtual HRESULT draw3dRay(const gb::math::geom3d::Ray* ray) const ;
#endif

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
	virtual HRESULT draw3dTraingle(const gb::math::geom3d::Triangle* tri) const ;
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





//------------------------------------------------------------------------------------------

} // end ns
} // end ns
} // end ns
} // end ns

#endif // #ifdef GB_OPENGL
// end file