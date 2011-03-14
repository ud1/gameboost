/* 
 тест d3d9 приложения
*/
 

#ifdef _DEBUG
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#endif

#include <gb/graphics/d3d9/appl.h>
 

using namespace gb::graphics::d3d9::appl;


static  ApplD3D9*  g_pApplD3D9 = NULL; 


///  тесты добавлений

//#include <gb/graphics/d3d9/d3d9.h>
//#include <gb/graphics/d3d9/dataconv.h>
 

//=========================================================================
HRESULT FrameDraw(ApplD3D9* const appl, void* pUserParam)
{
	HRESULT hr =0;
 
  // hr |=appl->getD3D9Device()->SetTexture(0, g_pApplD3D9->getSampleTexture());
 
 return hr;
}



//=========================================================================
//INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
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

	g_pApplD3D9 = new  ApplD3D9();

	hr |= g_pApplD3D9->init(&initdata);
	if FAILED(hr) 
	{

		delete g_pApplD3D9;
		return -1; 
	};
 


	// run render
	hr |=  g_pApplD3D9->run();
	if FAILED(hr) 
	{

		delete g_pApplD3D9;
		return -1; 
	};


	// clear
	hr |= g_pApplD3D9->finalize(); 

	delete g_pApplD3D9;
	g_pApplD3D9 = NULL;



#ifdef _DEBUG
	_CrtMemDumpAllObjectsSince(&_ms);  
#endif

	return (int)hr;
}



