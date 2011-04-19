
#include <gb/graphics/visual_geometry/visual_geometry.h>


#ifdef GB_D3D9
  #include <gb/graphics/visual_geometry/internal/vg_impl_d3d9.h>
#endif 

#ifdef GB_OPENGL
  #include <gb/graphics/visual_geometry/internal/vg_impl_opengl.h>
#endif 


using namespace gb::graphics::visual_geometry;
using namespace gb::graphics::visual_geometry::internal;




//=========================================================================
GB_VG_API void gb::graphics::visual_geometry::CreateInterfaceDrawValues(
	gb::graphics::visual_geometry::IDrawValues **ppOut, 
	const gb::graphics::visual_geometry::CreteDrawValuesOptions *opt)  throw()
{
	*ppOut = NULL;

	  assert(opt->api && "API не определено");
 
  switch (opt->api)
  {

    #ifdef GB_D3D9
      case visual_geometry::vg_graph_api_e::VG_GAPY_D3D9: 
      {
        *ppOut = (IDrawValues*)new VGDrawValuesImpl_D3D9(opt->pdevice);
        return ;

      }
      break;
    #endif 



    #ifdef GB_OPENGL 
   //#error  OpenGL пока не поддерживается
	  case visual_geometry::vg_graph_api_e::VG_GAPY_OPENGL:
      {
		  *ppOut = (IDrawValues*)new internal::VGDrawValuesImpl_ogl();
      }
      break;
    #endif 


    default:
      {
        // invalid param
     	throw std::runtime_error("Invalid input param");
        return ;

      }


  } // switch



  // ok
}

//=========================================================================
GB_VG_API void gb::graphics::visual_geometry::CreateInterfaceDraw2DGeometry(
	gb::graphics::visual_geometry::IDraw2DGeometry **ppOut, 
	const gb::graphics::visual_geometry::CreteDrawValuesOptions *opt)  throw()
{

  *ppOut = NULL;

    assert(opt->api && "API не определено");

  switch (opt->api)
  {

    #ifdef GB_D3D9
	  	  assert(opt->pdevice && "Устройство d3d9 == NULL");
      case visual_geometry::vg_graph_api_e::VG_GAPY_D3D9: 
      {
        *ppOut = (IDraw2DGeometry*)new VGDraw2DGeometry_Impl_D3D9(opt->pdevice);
        return ;

      }
      break;
    #endif 


    #ifdef GB_OPENGL 
	 // #error  OpenGL пока не поддерживается
	  case visual_geometry::vg_graph_api_e::VG_GAPY_OPENGL:
       {
          *ppOut = (IDraw2DGeometry*)new VGDraw2DGeometry_Impl_ogl();
       }
        break;
      #endif 




    default:
      {
        // invalid param
       throw std::runtime_error("Invalid input param");
        return ;

      }


  } // switch


 // ok
};


//=========================================================================
GB_VG_API void gb::graphics::visual_geometry::CreateInterfaceDraw3DGeometry(
	gb::graphics::visual_geometry::IDraw3DGeometry **ppOut, 
	const gb::graphics::visual_geometry::CreteDrawValuesOptions *opt) throw()
{

  *ppOut = NULL;

  assert(opt->api && "API не определено");

  switch (opt->api)
  {



    #ifdef GB_D3D9
	  assert(opt->pdevice && "Устройство d3d9 == NULL");
      case visual_geometry::vg_graph_api_e::VG_GAPY_D3D9: 
      {
        *ppOut = (IDraw3DGeometry*)new VGDraw3DGeometry_Impl_D3D9(opt->pdevice);
        return ;

      }
      break;
    #endif 



    #ifdef GB_OPENGL  
	 // #error  OpenGL пока не поддерживается
	  case visual_geometry::vg_graph_api_e::VG_GAPY_OPENGL:
      {
          *ppOut = (IDraw3DGeometry*)new VGDraw3DGeometry_Impl_ogl();
      }
      break;

    #endif 


    default:
      {
        // invalid param
		  throw std::runtime_error("Invalid input param");
        return ;

      }


  } // switch



 // ok
};






// end file
