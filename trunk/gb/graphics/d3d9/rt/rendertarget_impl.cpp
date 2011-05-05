

#if ( defined(GB_D3D9) && defined(WIN32) )

//#include "dappllibrary_stdafx.h"
//#include "dappllibr.cpp"

#include <gb/graphics/d3d9/d3d9.h>
#include <gb/graphics/d3d9/rt/rendertarget_impl.h>
//#include <gb/base/Debug.h>
//#include "DAPLIB_RTarget_impl.h"


namespace gb {
namespace graphics {
namespace d3d9 { 
namespace rt {




//=========================================================================
//	DAPLIB_RTarget
//=========================================================================

//=========================================================================
HRESULT  RenderTarget::MakeAsCurrentRender()  const  
{
  HRESULT hr =0;
	if(NULL == m_pdevice) 
		   return E_FAIL;
 
	 if( (NULL==m_pITexture) || (NULL==m_pISurface) ) { 
	   return E_FAIL;
	 }

	 _try {
	 hr |= m_pdevice->SetRenderTarget(0, m_pISurface);
	 } 
	 __except(EXCEPTION_EXECUTE_HANDLER) 
	 {
	   return E_FAIL;
	 }

   return hr;
};


//===========================================================
HRESULT  RenderTarget::MakeRenderToBackBuffer()  const  
{
   HRESULT hr = 0;
   
#pragma message ("ВСТАВИТЬ КОД ДЛЯ УСТАНОВКИ В КОНТЕКСТ "  __FILE__ )

	 assert(false&&"ВСТАВИТЬ КОД ДЛЯ УСТАНОВКИ В КОНТЕКСТ");
 
   //if( ( g_pISrfFrameDraw == NULL) || (m_pdevice == NULL) ) 
	//{
	//   return E_FAIL;
	//};


   //hr |= m_pdevice->SetRenderTarget(0 , g_pISrfFrameDraw);
 
   return hr;   
};

//====================================================
HRESULT RenderTarget::CheckCreateInterfaces( ) const 
{
	   if(  (m_pISurface) && (m_pITexture)  )   return  0;

	   ReleaseInterfaces();
   return  E_FAIL;
};


//===================================================
HRESULT RenderTarget::FillSurfaceColor(const D3DCOLORVALUE& color) const  
{
  HRESULT hr =0;
   D3DCOLOR col = D3DCOLOR_COLORVALUE( color.r, color.g, color.b, color.a);
	   hr |= FillSurfaceColor(col);
 
  return hr;
};

//=========================================================================
HRESULT RenderTarget::FillSurfaceColor(  const D3DCOLOR color) const 
{
  HRESULT hr =0;

  if(  NULL == m_pdevice  )
  {     
		  return E_FAIL;   
  };

 
		  if(!m_pISurface) return E_FAIL;

		__try { 
			hr =  m_pdevice->ColorFill(m_pISurface, NULL, color);  
		}
		__except(EXCEPTION_EXECUTE_HANDLER) { 
			return E_FAIL; 
		}

   return hr;
};


//=========================================================================
HRESULT RenderTarget::StretchFrom(const IRenderTarget* rtarget, 
											   const D3DTEXTUREFILTERTYPE ft ) const 
{
   HRESULT hr=0;
   __try {
	    hr |= StretchFrom( rtarget->getISurface() , ft );
	  } __except(1) { hr |= E_FAIL; };
  return  hr;
};


//=========================================================================
HRESULT RenderTarget::StretchFrom(IDirect3DSurface9* pISurface, 
											   const D3DTEXTUREFILTERTYPE ft ) const  
{  
	
	HRESULT hr=0;
	   if(NULL == m_pdevice)
	   {     
			   return E_FAIL;   
	   };


 
	__try {
		if(!m_pISurface) return E_FAIL;
		if(!pISurface ) return E_FAIL;
 
		if FAILED(hr) { 
			// MONPRINT("");
			return hr;   
			};

		
		// Stretch From
	 hr|= m_pdevice->StretchRect( pISurface, NULL, m_pISurface, NULL,  ft );
  // (StretchRect)(THIS_ IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,
	          //IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,  
	           //D3DTEXTUREFILTERTYPE Filter) PURE;

		} 
      __exc_mon
		{
			//SAFE_EXC_RELEASE(pdevice);
			hr |= E_FAIL;
		};

       return hr;
};

//=============================================================
HRESULT RenderTarget::StretchTo(const IRenderTarget* rtarget, 
											const D3DTEXTUREFILTERTYPE ft) const 
{
 	HRESULT hr=0;
	__try {
	 hr |= StretchTo( rtarget->getISurface() , ft );
	} __except(1) { hr |= E_FAIL; };
    return hr;
};


//=======================================================
HRESULT RenderTarget::StretchTo(IDirect3DSurface9* pISurface, 
											const D3DTEXTUREFILTERTYPE ft ) const 
{
	HRESULT hr=0;
	if(NULL == m_pdevice)
	{     return E_FAIL;   };



	__try {
		if(!m_pISurface) return E_FAIL;
		if(!pISurface ) return E_FAIL;

		if FAILED(hr) { 
			// MONPRINT("");
			return hr;   
		};

		// stretch to ...
		hr|= m_pdevice->StretchRect(  m_pISurface, NULL,  pISurface, NULL, ft );
		// (StretchRect)(THIS_ IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,
		//IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,  
		//D3DTEXTUREFILTERTYPE Filter) PURE;


	} 
	__exc_mon
	{
	 
		hr |= E_FAIL;
	};

	return hr;
};





//=========================================================================
HRESULT RenderTarget::ValidateInterfaces() const {
  HRESULT hr =0;	
 
  	  if(!m_pITexture ) return E_FAIL;
	  if(!m_pISurface) return E_FAIL;
	
		// check texture
		  __try {
		   DWORD dwlc = m_pITexture->GetLevelCount();
		  }
		  __except(1) {
		   return E_FAIL;
		  };

		// check surface
		  __try {
		    D3DSURFACE_DESC sd;
			HRESULT hr = m_pISurface->GetDesc(&sd);
		  }
		  __except(1) {
		   return E_FAIL;
		  };

 
	return hr;
};

 



//=========================================================================

} // end namespace
} // end namespace
} // end namespace
} // end namespace

#endif // #if  ( #defined(WIN32) && #defined(GB_D3D9) )
// end file