// утилита для просмотра файлов fx
//

#define GB_D3D9
#define GB_D3DX9

#include <gb/graphics/d3d9/auto_include_libr.h>

#include <d3dx9.h>
#include <gb/macro.h>
#include <gb/system/console.h>

#include "context.h"


  class Parameter {
  public:
	  Parameter() { memset(&m_sem_id, 0, sizeof(Parameter) );  };
	 // virtual ~Parameter() {   };

	int m_sem_id;
	D3DXPARAMETER_DESC pd;
	D3DXHANDLE hp;

	float m_data[4];

	

	//void set_semid(int _val) {  m_sem_id = _val; };
	//inline int get_sem_id() const { return m_sem_id; };

  private:

};


  //kst::VectorPointers<Parameter> g_semparams; 
  std::vector<Parameter> g_vector_params; 
 



class Appl {
public:
   ID3DXEffect* m_peff ;
   char m_strFxFilePath[MAX_PATH+1];

	Appl(int argc,  char* argv[] )
	{
		m_peff = NULL;
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
 
			GB_SAFE_REL(m_peff)
 

	}

	HRESULT CreateEffet(IDirect3DDevice9* pdevice)
	{
      HRESULT hr =0;

	  if( m_strFxFilePath[0] == '\0' )
	  {
	   // no effect path
		  return hr;
	  }

	
	  return hr;
	}

	HRESULT OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc)
	{
	    HRESULT hr = S_OK;

		// create effect
		  hr |= CreateEffet(pd3dDevice);


		return hr;	
	}

	HRESULT OnResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc)
	{
	    HRESULT hr = S_OK;

		if(m_peff)
		{
		 hr |= m_peff->OnResetDevice();
		}

		return hr;	
	}

	HRESULT OnLostDevice()
	{
	    HRESULT hr = S_OK;
	   		if(m_peff)
		{
		 hr |= m_peff->OnLostDevice();
		}
		return hr;
	}

	HRESULT OnDestroyDevice()
	{
	   HRESULT hr = S_OK;
		GB_SAFE_REL(m_peff)
		return hr;	
	}




};

 
// end file