// утилита для просмотра файлов fx
//

//#define GB_D3D9
//#define GB_D3DX9

#include <gb/fmath/fmath.h>
using namespace gb::fmath;
using namespace gb::fmath::context;

#include <gb/devhelp/devcamera.h>
using namespace gb::devhelp;

#include <gb/color/color.h>
using namespace gb::color;

#include <gb/str/String.h>
using namespace gb::str;

#include <gb/system/console.h>

#include <gb/graphics/Teapot.h>
#include <gb/graphics/value_semantic/value_semantic.h>
 
#include <ce/dxut_wonly/dxut_wonly.h>

#include <gb/graphics/d3d9/d3dx9_dynamic_load/d3dx9_dynamic_load.h>
using gb::graphics::d3d9::d3dx9_dynamic_load::CD3DX9_Dll_Loader; 

#include <gb/graphics/d3d9/fx/create_effect.h>
#include <gb/graphics/d3d9/fx/param.h>
using namespace gb::graphics::d3d9::fx;

#include <gb/graphics/d3d9/draw/draw.h>
using namespace gb::graphics::d3d9::draw;

#include <assert.h>
#include <string>
#include <vector>



#pragma warning(push)
#pragma warning( disable : 4996 )



class Mesh 
{
   cccccccccc


};

class Appl 
{
public:
   ID3DXEffect* m_peff ;
   gb::graphics::d3d9::fx::Parameter* m_params;
   IDirect3DDevice9* m_pdevice;
   CD3DX9_Dll_Loader m_d3dxloader;
   gb::fmath::context::GeometryContext m_GeometryContext;
   gb::fmath::context::FloatContext    m_FloatContext;
   std::string m_strError;

    ModelViewerCamera m_camera;


   char m_strFxFilePath[MAX_PATH+1];

	Appl(int argc,  char* argv[] )
	{
		m_peff = NULL;
		m_params = NULL;
		m_pdevice = NULL;
		m_strFxFilePath[0] = '\0';
		m_peff = NULL;
	   if(argc > 1)
	   {
		   assert(false);
		   strncpy(m_strFxFilePath, argv[1] , MAX_PATH );
	   }

	}

	virtual ~Appl()
	{
		 ReleaseEffect();
			
 

	}

	HRESULT CreateEffect( )  throw()
	{
      HRESULT hr =0;
	  m_strError = "";

	  if( m_strFxFilePath[0] == '\0' )
	  {
	   // no effect path
		  return hr;
	  }

	  std::string text ;
	  if( !gb::str::loadStrFromFileA(text,  m_strFxFilePath ) )
	  {
		  GB_MBOX("Error read file");
		  return E_FAIL;
	  }
 
	  CreateEffectOptions opt(NULL, NULL);

	  hr = gb::graphics::d3d9::fx::createEffectFromText(&m_peff, &m_d3dxloader, 
		  m_pdevice, text.c_str(),
		  m_strError, &opt, true  );

	  if FAILED(hr)
	  {
		 return E_FAIL;
	  }

	  m_params =   CreateParamsBuffer(m_peff);

	
	  return hr;
	}

	void ReleaseEffect()
	{
		if(m_peff)
		{
		 GB_SAFE_REL(m_peff)

		 D3DXEFFECT_DESC des;
		 if FAILED( m_peff->GetDesc(&des) )
		 {
			 throw std::runtime_error("failed operation");
		 }





		}

	    
        GB_SAFE_DEL_BUF(m_params);
	}

	HRESULT OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc)
	{
	    HRESULT hr = S_OK;

		// create effect
		m_pdevice = pd3dDevice;
		  hr |= CreateEffect( );


		return hr;	
	}

	HRESULT OnResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc)
	{
	    HRESULT hr = S_OK;
		m_pdevice = pd3dDevice;

		if(m_peff)
		{
		 hr |= m_peff->OnResetDevice();
		}

		return hr;	
	}

	HRESULT OnLostDevice()
	{
	    HRESULT hr = S_OK;
		  m_pdevice = NULL;

	   	if(m_peff)
		{
		 hr |= m_peff->OnLostDevice();
		}
		return hr;
	}

	HRESULT OnDestroyDevice()
	{
		HRESULT hr = S_OK;
		m_pdevice = NULL;
		GB_SAFE_REL(m_peff)
		GB_SAFE_DEL_BUF(m_params)


		return hr;	
	}

	HRESULT OnFrameRender(IDirect3DDevice9* pdevice, float time, float delta)
	{
		HRESULT hr =0;

	  hr |= m_camera.makeCurrent(pdevice, false);

   // update float context  
   m_GeometryContext.setMatrices( 
		   &m_camera.getWorldMatrix(), 
		   &m_camera.getViewMatrix(), 
		   &m_camera.getProjMatrix()   );  


	   if(m_peff)
	   {
	   hr |= SetSemanticParams(m_peff, m_params, &m_GeometryContext, &m_FloatContext);


	   UINT passes =0;
		hr |= m_peff->Begin(&passes, 0);
		hr |= m_peff->BeginPass(0);

		hr |= gb::graphics::d3d9::draw::drawMeshPrimitiveCube1x1Mem(pdevice);

		hr |= m_peff->EndPass();
		hr |= m_peff->End();

	   }


		return hr;
	}



	void OnKeyboard(UINT key)
	{
		if(key == 'R')
		{
			ReleaseEffect();
			Sleep(100);
			CreateEffect();
		}



	}


};


#pragma warning(pop)
 
// end file