#ifdef GB_OPENGL

#include <gb/graphics/visual_geometry/visual_geometry.h>


#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLAux.h>


namespace gb {
namespace graphics {
namespace visual_geometry {
namespace internal {

//-------------------------------------------------------------------------------


//! Сохраняет и восстанавливает состояние OpenGL
class VGSaveRestoreDataOpenGL {
public:

	         VGSaveRestoreDataOpenGL() {}
	virtual ~VGSaveRestoreDataOpenGL() {}


  //! Cохранение состояния OpenGL
  void SaveDeviceData(const VGCOLOR& newColor, 
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





};





//------------------------------------------------------------------------------------------

} // end ns
} // end ns
} // end ns
} // end ns

#endif // #ifdef GB_OPENGL
// end file