 // тест визуальной геометрии через d3d9

#ifdef _DEBUG
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#endif

#include <gb/graphics/d3d9/appl.h>
#include <gb/graphics/visual_geometry/visual_geometry.h>
#include <gb/macro.h>
 

using namespace gb::graphics::d3d9::appl;
using namespace gb::graphics::visual_geometry;

 IDraw3DGeometry* g_pIDraw3d =NULL;


//=========================================================================
HRESULT FrameDraw(ApplD3D9* const appl, void* pUserParam)
{
  HRESULT hr =0;

  if( g_pIDraw3d == NULL)
  {
	  // create
	  CreteDrawValuesOptions opt;
	  opt.pdevice = appl->getD3D9Device();
	  opt.api =  ::vg_graph_api_e::VG_GAPY_D3D9;

 int32_t res =  CreateInterfaceDraw3DGeometry(&g_pIDraw3d ,&opt );
  if(res <0)
  {
	  GB_MBOX("Error create");
  }

  } // if


 //g_pIDraw3d->draw3dArrow()


  //  =====================  draw 3d   ==========================

  g_pIDraw3d->draw3dAxies( &VGVEC3(  0.0f,   0.0f  ,  0.0f ), 1.0f  );
g_pIDraw3d->draw3dLine(0.0f,0.0f,0.0f,    1.0f,1.0f,1.0f,     NULL );



// =========================  draw 2d ===========================





 
  return hr;
}

 
int main() 
{

#ifdef _DEBUG
	_CrtMemState _ms; 
	_CrtMemCheckpoint(&_ms); 
#endif


	HRESULT hr =0;

 
		 APPL_D3D9_INIT_DATA initdata;
	initdata.callback_d3d9.funcOnFrameDraw =  FrameDraw;
	initdata.hInstance  = 0 ; // hInst;

 
	 ApplD3D9*   g_pApplD3D9 = new  ApplD3D9();



	hr |= g_pApplD3D9->init(&initdata);
	if FAILED(hr) 
	{

		delete g_pApplD3D9;
		return -1; 
	};
 
	// set crea color black
	g_pApplD3D9->setClearColor( 0.0f, 0.0f, 0.0f );

	// run render
	hr |=  g_pApplD3D9->run();
	if FAILED(hr) 
	{

		delete g_pApplD3D9;
		return -1; 
	};

   GB_SAFE_DEL_OBJ(g_pIDraw3d);


	// clear
	hr |= g_pApplD3D9->finalize(); 

	delete g_pApplD3D9;
	g_pApplD3D9 = NULL;



#ifdef _DEBUG
	_CrtMemDumpAllObjectsSince(&_ms);  
#endif

	return (int)hr;
}



