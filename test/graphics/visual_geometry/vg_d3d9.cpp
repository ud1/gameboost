 // тест визуальной геометрии через d3d9

#ifdef _DEBUG
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#endif

#include <gb/Config.h>
#include <gb/base/Types.h >


#include <gb/graphics/d3d9/appl.h>

//#include <>

#include <gb/graphics/visual_geometry/visual_geometry.h>
#include <gb/macro.h>


//  experiment
#include <gb/graphics/d3d9/stack/RenderTargetStack.h>
#include <gb/graphics/d3d9/stack/StatesValueStack.h>
#include <gb/graphics/d3d9/stack/ViewPortStack.h>



 

using namespace gb::graphics::d3d9::appl;
using namespace gb::graphics::visual_geometry;
using namespace gb::math;
using namespace gb::math::base;
using namespace gb::math::geom3d;
using namespace gb::math::geom2d;




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

	  try {
  CreateInterfaceDraw3DGeometry(&g_pIDraw3d ,&opt );
	  }
	  catch(...)
	  {
	  GB_MBOX("Error create");
	  } // catch

  } // if


 //g_pIDraw3d->draw3dArrow()


  //  =====================  draw 3d   ==========================

  g_pIDraw3d->setColorWhite();

  // draw axies
  g_pIDraw3d->draw3dAxies( &VGVEC3(  0.0f,   0.0f  ,  0.0f ), 1.0f  );

  // draw line
g_pIDraw3d->draw3dLine( 0.35f,-0.5f, -0.8f,    1.0f,1.0f,1.0f  );

 // draw point
g_pIDraw3d->setColorGreen();
g_pIDraw3d->draw3dPoint(2.0f, 1.9f, 2.2f, 2.0f);

// draw points
g_pIDraw3d->setColorPink();
VGVEC3  varr[4];
varr[0].x = 1.5f; varr[0].y = -0.2f; varr[0].z = 0.70f;
varr[1].x = -1.9f; varr[1].y = 1.8f; varr[1].z = -0.1f;
varr[2].x = 0.2f; varr[2].y = -0.4f; varr[2].z = 0.3f;
g_pIDraw3d->draw3dPoints(varr, 3, 4.0f );

// draw ray
gb::math::geom3d::Ray ray(
						  vec3_s(0.2f, -1.56f, 1.98f) , 
						  vec3_s(4.5f, 0.8f, -1.5f) ,
						  true
						  );
 //ray.dir.normalize();
 g_pIDraw3d->setColorBlue();
 g_pIDraw3d->draw3dRay(&ray );

// draw aabb
 g_pIDraw3d->setColorYellow();
// AABB  aabb(vec3_s(-0.48f, -1.547f, -0.89f) , vec3_s(0.78f, 1.78f, 0.98f)  );
 AABB  aabb(vec3_s( 0.1f, 0.1f, 0.1f ) , vec3_s( 1.1f, 1.1f, 1.1f )  );

 g_pIDraw3d->draw3dAABB(&aabb  );




// =========================  draw 2d ===========================
hr |= appl->getD3D9Device()->Clear(0,NULL, D3DCLEAR_ZBUFFER,  0, 1.0, 0);






 
  return hr;
}

 //========================================================================
int main() 
{
 // test math func
	D3DXMATRIX  mdx;
	//D3DXMATRIX * D3DXMatrixPerspectiveFovLH(
	//	 &mdx,
	//	 1.35f, //FLOAT fovy,
	//	1.1f, //FLOAT Aspect,
	//	0.22f, //FLOAT zn,
	//	1123.0f // FLOAT zf
	//	);


	gb::math::base::mat44_s mgb;
	//mgb.setOrthoLH(   
	//	800.0f,
	//	600.0,
	//	0.1f,
	//	100.0f	
	//	
	//	);

	//**************************************************************
	//D3DXMatrixOrthoOffCenterLH
	//(
	//&mdx,
 // FLOAT xx, // l,
 // FLOAT xx, // r,
 // FLOAT xx, // b,
 // FLOAT xx, // t,
 //  0.125f, // zn,
 //  10.45748f, // zf
	//);






	//*****************************************************************


	/*
	 D3DXMatrixLookAtRH(
  &mdx,
    &D3DXVECTOR3(1.0f, 4.48f, 5.484f),// eye
    &D3DXVECTOR3(6.4f, -5.485f, -6.15f),  // pAt,
    &D3DXVECTOR3(0.78f,  -2.68f, 7.8) // pUp
);

	 mgb.setViewLookAtRH(
    vec3_s(1.0f, 4.48f, 5.484f),// eye
    vec3_s(6.4f, -5.485f, -6.15f),  // pAt,
    vec3_s(0.78f,  -2.68f, 7.8) // pUp


		 );
*/





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



