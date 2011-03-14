
#include <gb/graphics/visual_geometry/visual_geometry.h>


#ifdef GB_D3D9
  #include <gb/graphics/visual_geometry/internal/vg_impl_d3d9.h>
#endif 

#ifdef GB_OPENGL
  #include <gb/graphics/visual_geometry/internal/vg_drval_impl_opengl.h>
#endif 


using namespace gb::graphics::visual_geometry;
using namespace gb::graphics::visual_geometry::internal;




//=========================================================================
int32_t gb::graphics::visual_geometry::CreateInterfaceDrawValues(
	gb::graphics::visual_geometry::IDrawValues **ppOut, 
	const gb::graphics::visual_geometry::CreteDrawValuesOptions *opt)
{
  int32_t hr = 0;


  switch (opt->api)
  {

    #ifdef GB_D3D9
      case visual_geometry::vg_graph_api_e::VG_GAPY_D3D9: 
      {
        *ppOut = (IDrawValues*)new VGDrawValuesImpl_D3D9(opt->pdevice);
        return 0;

      }
      break;
    #endif 



    #ifdef GB_OPENGL  
      case visual_geometry::vg_graph_api_e::xxxxopengl
      {
        *ppOut = (IDrawValues*)new VGImpl_OpenGL();
      }
      break;
    #endif 


    default:
      {
        // invalid param
        return  - 1;

      }


  } // switch




  return hr;
}

//=========================================================================
int32_t gb::graphics::visual_geometry::CreateInterfaceDraw2DGeometry(
	gb::graphics::visual_geometry::IDraw2DGeometry **ppOut, 
	const gb::graphics::visual_geometry::CreteDrawValuesOptions *opt)
{
  int32_t hr = 0;
  *ppOut = NULL;

  switch (opt->api)
  {

    #ifdef GB_D3D9
      case visual_geometry::vg_graph_api_e::VG_GAPY_D3D9: 
      {
        *ppOut = (IDraw2DGeometry*)new VGDraw2DGeometry_Impl_D3D9(opt->pdevice);
        return 0;

      }
      break;
    #endif 


    #ifdef GB_OPENGL  
      case _opengl:
        {
          *ppOut = (IDraw2DGeometry*)new VGImpl_OpenGL();
        }
        break;
      #endif 




    default:
      {
        // invalid param
        return  - 1;

      }


  } // switch





  return hr;
};


//=========================================================================
int32_t gb::graphics::visual_geometry::CreateInterfaceDraw2DGeometry(gb
  ::graphics::visual_geometry::IDraw3DGeometry **ppOut, const gb::graphics
  ::visual_geometry::CreteDrawValuesOptions *opt)
{
  int32_t hr = 0;
  *ppOut = NULL;
  assert(false);

  assert(opt->pdevice);
  assert(opt->api);

  switch (opt->api)
  {



    #ifdef GB_D3D9
      case visual_geometry::vg_graph_api_e::VG_GAPY_D3D9: 
      {
        *ppOut = (IDraw3DGeometry*)new VGDraw3DGeometry_Impl_D3D9(opt->pdevice);
        return 0;

      }
      break;
    #endif 



    #ifdef GB_OPENGL  
      case _opengl:
        {
          *ppOut = (IDraw3DGeometry*)new xxxxxx_ogl();
        }
        break;
      #endif 


    default:
      {
        // invalid param
        return  - 1;

      }


  } // switch



  return hr;
};






// end file
