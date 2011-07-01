﻿// ok !
#include "d3d9pch.h"


#if ( defined(WIN32) && defined(_D3D9_H_) )

#include "../rendertarget.h" 
#include <gb/macro.h>
 
#include "rendertarget_impl.h"
#include <gb/t/func.h>
 
#include <assert.h>

#ifdef SURFAVEARCOLORCOMPUTER
#include "surfavearcolorcomputer.h"
 SurfAvearColorComputer  g_SurfAvearColorComputer;
#endif


#ifdef COMPUTESURFACEPIXELCOLOROBJECT
#include "computesurfacepixelcolorobject.h"
 ComputeSurfacePixelColorObject g_ComputeSurfacePixelColorObject;
#endif

 HRESULT __CPPI_Init();

namespace gb {
namespace graphics {
namespace d3d9 { 
namespace rendertarget {

//==============================================================




//* global device  
static    IDirect3DDevice9* g_pdevice =  NULL;
//* global for create surface
static D3DSURFACE_DESC  g_D3DSURFACE_DESC;
//* global frame draw render Target (NO RELEASE !)
static IDirect3DSurface9* g_pISrfFrameDraw = NULL;




//* \brief пул рендертаргетов 
class RenderTargetsPool {
private:
     IRenderTarget* m_arr[GB_D3D9_MAX_RENDERTARGETS_ONPOOL] ;  


public:

	RenderTargetsPool() 
	{
		//?????????????????
	  memset(m_arr, 0, sizeof(m_arr) );
	  memset(&g_D3DSURFACE_DESC, 0, sizeof(g_D3DSURFACE_DESC) );
	}

	~RenderTargetsPool() 
	{
	    // ???????????????	
		
	}

	//-----------------------------------------------------------
	HRESULT DeleteAllRenderTargets() {
	  HRESULT hr =0;

	  for(int c=0; c<GB_D3D9_MAX_RENDERTARGETS_ONPOOL; c++) {
	    IRenderTarget* pcurr = NULL;
		pcurr = m_arr[c];

		gb::t::func::safeExceptionDelete( &m_arr[c] );
		
		  
	  };

		
	  return hr	;
	};

	//------------------------------------------------
	unsigned int FindNullIndex() {
		 for(unsigned int c=0; c<GB_D3D9_MAX_RENDERTARGETS_ONPOOL; c++) {
		   if( m_arr[c] == NULL )
			    return c;

		 };

		 // not found
	    return -1;
	};

	//--------------------------------------------------------------
	HRESULT GetUnused(IRenderTarget** ppOut,  UINT nWidth, UINT nHeight, IDirect3DDevice9* pdevice) {
		HRESULT hr =0;
 
      #pragma message ("NEED CHECK CODE" __FILE__  )

			*ppOut = NULL;

			// check backbuf descr struct
			if( (g_D3DSURFACE_DESC.Width == 0) || (g_D3DSURFACE_DESC.Height == 0)  ) {
				return E_FAIL;
				
				};
 

				IRenderTarget* prt = NULL;

				for(int c=0; c<GB_D3D9_MAX_RENDERTARGETS_ONPOOL; c++) {
				  
				   prt = m_arr[c];

				   if(prt)  {
						   if( (prt->getWidth() == nWidth) && (prt->getHeight() == nHeight) && ( !prt->IsUsed() ) )
						   {
								// found !!
								 if FAILED(prt->ValidateInterfaces()  ) {
									 // FAIL !!
									 gb::t::func::safeExceptionDelete(&m_arr[c]); 
									 continue;
								  };
							  

							 prt->SetUsed(true);
						    
							break;
						   
						   }
					   
					}
				   else {
					 

				   };
				   
				   
				 prt = NULL;

				}; // for


				if(prt) {
					// found !
					*ppOut = prt;
					return hr;
					};


				  // not found !!create
				  for(int c=0; c<GB_D3D9_MAX_RENDERTARGETS_ONPOOL; c++) {
					 prt = NULL;


					  if( m_arr[c] == NULL ) {

						  try {
						  m_arr[c] =  RenderTarget::UnSafeCreateNewInstance(nWidth, nHeight, pdevice , hr); 
						  m_arr[c]->SetUsed(true);
						  prt = m_arr[c];
						  break;
							  }
						  // __except(1) 
						  catch(...)
						  {
							  // error
							  gb::t::func::safeExceptionDelete(&m_arr[c] );
							  m_arr[c] = NULL;
							  prt = NULL;
							  *ppOut = NULL;
							  hr |= E_FAIL;
							  return hr;

						  };// __except(1)


						  
					  }
					  else
					  {
						continue;

					  }
	 

				  }; // for


	 

	 
	   // check error  : unused not found
	   if( prt == NULL ) {
		GB_MONPRINT("unused rendertargets not found");
		  *ppOut = NULL;
		   hr |= E_FAIL;
	   }
	   else
	   {
		   // ok !
		   *ppOut = prt;

	   }
			
	  return hr;
	};


	//-----------------------------------------------------------
	HRESULT GetUnused(IRenderTarget** ppOut,  const RenderTargeteSize_e eSize, IDirect3DDevice9* pdevice) {
		HRESULT hr =0;

		*ppOut = NULL;

		// check backbuf descr struct
		if( (g_D3DSURFACE_DESC.Width == 0) || (g_D3DSURFACE_DESC.Height == 0)  ) {
			GB_MONPRINT("Serface descr is not defined");
			return E_FAIL;
			
			};


		   UINT  w  = 0; 
		   UINT  h  = 0;

		   hr |= ComputeNeedRtSize(w, h, eSize, g_D3DSURFACE_DESC.Width, g_D3DSURFACE_DESC.Height );
		   if FAILED(hr) 
			   {
					 GB_MONPRINT("Incorrect input data \n");
			        return hr;
			   };
		   
	  hr |= GetUnused( ppOut, w, h, pdevice);
		
  return hr;	 	
};

//-------------------------------------------------------------------
HRESULT SetUnusedAll() {
  HRESULT hr =0;

  for(unsigned int c=0; c<GB_D3D9_MAX_RENDERTARGETS_ONPOOL; c++) {
	 IRenderTarget* prt = m_arr[c];
	 if(prt) {

		 __try {
		     prt->SetUsed(false);

		 }
		 __except(1) {
			 hr |= E_FAIL;
		 };
	 };


  }




	return hr  ;
};
	

 
};
// end class

static RenderTargetsPool g_RenderTargetsPool;




//===============================================
static HRESULT  __CPPI_DeviceCritResRel (void* pUserData )
{
	
  g_RenderTargetsPool.DeleteAllRenderTargets();	
	memset(&g_D3DSURFACE_DESC, 0, sizeof(g_D3DSURFACE_DESC) );

    g_pdevice = NULL;
	g_pISrfFrameDraw = NULL;


#ifdef SURFAVEARCOLORCOMPUTER
	g_SurfAvearColorComputer.ReleaseInterfaces();
#endif


#ifdef COMPUTESURFACEPIXELCOLOROBJECT
	g_ComputeSurfacePixelColorObject.ReleaseInterfaces();
#endif
	
  return 0;	
};


//======================================================================
HRESULT  ComputeNeedRtSize( gb_out UINT& nOutWidth, 
							gb_out UINT& nOutHeight, 
							const RenderTargeteSize_e eSize, 
							const UINT nScreenWidth, 
							const UINT nScreenHeight
								)
{
   HRESULT hr =0 ;

     	hr |= __CPPI_Init(); GB_RETFAIL
	
switch (eSize) {

 case FULLSCREEN : { nOutWidth = nScreenWidth; nOutHeight = nScreenHeight; return 0;   } break;	
 case HALF_FULLSCREEN : {  nOutWidth = nScreenWidth/2; nOutHeight = nScreenHeight/2; return 0;  } break;	
 case THIRD_FULLSCREEN : {  nOutWidth = nScreenWidth/3; nOutHeight = nScreenHeight/3; return 0;   } break;
 case FOURTH_FULLSCREEN : { nOutWidth = nScreenWidth/4; nOutHeight = nScreenHeight/4; return 0;   } break;
 case _64X64 :    { nOutWidth =  64;    nOutHeight = 64 ; return 0;   } break;
 case _256X256 :  { nOutWidth =  256;   nOutHeight = 256 ; return 0;   } break;	
 case _512X512 :  {  nOutWidth =  512;  nOutHeight = 512 ; return 0;  } break;
 case _1024X1024: {  nOutWidth =  1024; nOutHeight = 1024 ; return 0;   } break;


  // case xxx : {    } break;

 default: {
	  return E_FAIL;
	 }
  
	} // switch	

 
		// unknow ...
		assert(false);
		return  E_FAIL;
};


//=========================================================================
GB_D3D9_RT_API CreateRenderTargetInterfaces(gb_out IDirect3DSurface9** ppOutISrf,
									   gb_out IDirect3DTexture9** ppOutITxtr, 
									   IDirect3DDevice9* pdevice, 
									   const UINT nWidth, 
									   const UINT nHeight, 
									   const D3DFORMAT frmt )
{
		HRESULT hr=0;
			hr |= __CPPI_Init(); GB_RETFAIL

		//* текущие ширина и высота
		UINT currW = nWidth; 
		UINT currH = nHeight;
 
	// get back buffer surface
	 IDirect3DSurface9* pISurfBackBuffer = NULL;

	 hr |= pdevice->GetBackBuffer ( 
		0, // UINT iSwapChain, 
		 0, //UINT iBackBuffer,  
		  D3DBACKBUFFER_TYPE_MONO,
		   &pISurfBackBuffer   );

	 if FAILED(hr) {
		 GB_MONPRINT("FAIL get back buf device surface \n");
		 GB_SAFE_EXC_RELEASE(pISurfBackBuffer);
		  return hr;

		 };

	 // get description surface
	  D3DSURFACE_DESC backSurfDescr;
	  hr |= pISurfBackBuffer->GetDesc(&backSurfDescr);
	      if FAILED(hr) 
		  {
		  GB_MONPRINT("Failed get surf description \n");
		    GB_SAFE_EXC_RELEASE(pISurfBackBuffer);
		    return hr;
		   };

 

		if(currW ==0) {currW =  backSurfDescr.Width;  };
		if(currH ==0) {currH =  backSurfDescr.Height; };

		D3DFORMAT currFormat = D3DFMT_UNKNOWN; 
		if(frmt == D3DFMT_UNKNOWN) {
			currFormat =  backSurfDescr.Format;
		}
		else
		{
		  currFormat = frmt;
		}

	
#pragma message("ks777:  create texture without d3dx ????? " __FILE__)
	assert(false && "create texture without d3dx ?????" );
		//hr |= D3DXCreateTexture(
		//	pdevice,
		//	currW,
		//	currH,
		//	1,
		//	D3DUSAGE_RENDERTARGET,
		//	currFormat,
		//	D3DPOOL_DEFAULT,
		//	ppOutITxtr
		//	);
 


		if FAILED(hr) { 
			 GB_MONPRINT("fail create rendertarget texture \n");
			GB_SAFE_EXC_RELEASE(pISurfBackBuffer);

			return hr;  
			};


		// get surface 
		 IDirect3DTexture9*  txtr = *ppOutITxtr;
		hr |= txtr->GetSurfaceLevel (0,  ppOutISrf  );
		if FAILED(hr) {
			GB_MONPRINT("FAILED get surface level from texture \n");
			GB_SAFE_EXC_RELEASE(pISurfBackBuffer);
			return hr;   
			};
 
  // release back buf interface
  GB_SAFE_EXC_RELEASE(pISurfBackBuffer);


 
	  return   hr;
};

//===============================================
GB_D3D9_RT_API RenderTargetSetDevice(IDirect3DDevice9* pdevice) {
	HRESULT hr =0;
	hr |= __CPPI_Init(); GB_RETFAIL

	 g_pdevice = pdevice; 

   return hr;	
};


//================================================
GB_D3D9_RT_API SetBackBufSurfDescr(const D3DSURFACE_DESC* descr) {
  HRESULT hr =0;
	  hr |= __CPPI_Init(); GB_RETFAIL

	   g_D3DSURFACE_DESC = *descr;
	
   return hr;
};

//=================================================
GB_D3D9_RT_API SetBackBufFrameDrawIntrfPtr(IDirect3DSurface9* psurf) {
	
   HRESULT hr =0;
	hr |= __CPPI_Init(); GB_RETFAIL

	 g_pISrfFrameDraw = psurf;
	return hr;
};

//================================================
GB_D3D9_RT_API GetUnusedRenderTarget(gb_out IRenderTarget** ppOut, 
											  const RenderTargeteSize_e eSize) 
{
 HRESULT hr =0;
 hr |= __CPPI_Init(); GB_RETFAIL
 if(g_pdevice == NULL) {
	 
	 GB_MONPRINT("Device is NULL \n");
	  return E_FAIL;
	 };


 __try {
   hr |= g_RenderTargetsPool.GetUnused(ppOut,  eSize, g_pdevice );
	 } __except(1) {
	  hr |= E_FAIL;
	 };
 
   return hr;	
};

//=========================================================
GB_D3D9_RT_API GetUnusedRenderTarget(gb_out IRenderTarget** ppOut, 
											const UINT nWidth, 
											const UINT nHeight)
{
 HRESULT hr =0;

 hr |= __CPPI_Init(); GB_RETFAIL
 if(g_pdevice == NULL) 
 {
	 
	 GB_MONPRINT("Device is NULL \n");
	  return E_FAIL;
 };


   __try {
   hr |= g_RenderTargetsPool.GetUnused(ppOut,  nWidth,   nHeight, g_pdevice );
	 } __except(1) {
	  hr |= E_FAIL;
	 };



   return hr;
};

//============================================================
GB_D3D9_RT_API SetUnUsedAll() {
   HRESULT hr =0;

  hr |=  g_RenderTargetsPool.SetUnusedAll();


  return hr;
};

//====================================================================
GB_D3D9_RT_API ComputeAverSurfaceColor(
	     gb_out         gb::color::Color4f*   pOut, 
		 gb_inout_opt   IDirect3DSurface9*     surf, 
		 gb_in_opt      gb::fmath::geom2d::Rect*     rect  )

{
	HRESULT hr =0;

	   if(!g_pdevice) 
		{
		 return E_FAIL;
		}
		 
#ifdef SURFAVEARCOLORCOMPUTER
   hr |=  g_SurfAvearColorComputer.ComputeColor2(  pOut, g_pdevice,  surf,  rect );	
#else
   assert(false&&"no implem");
   return E_FAIL;
#endif
	

  return hr;
};

//=====================================================================
GB_D3D9_RT_API ComputeSurfacePixelColor (
	   gb_out           gb::color::Color4f*  pColorOut, 
	   gb_in            POINT&               pntCoord,
	   gb_inout_opt     IDirect3DSurface9*   pSrf )

{   
   HRESULT hr =0;

#ifdef COMPUTESURFACEPIXELCOLOROBJECT
	const IDAPLIB_RenderContext* context = DAPL_GetRenderContext();

  hr |= 
   g_ComputeSurfacePixelColorObject.ComputeSurfacePixelColor_ksmtcColor
	  (  pColorOut, context,  pntCoord,  pSrf  );

#else 
  assert(false&&"not implement");

#endif
	
  return hr;	
};


 /**********
DAPP_RT_CONSTRUCT IDAPLIB_RenderTarget::IDAPLIB_RenderTarget
		 (
	      const UINT nWidth, const UINT nHeight, const D3DFORMAT format 
		  ) 
		: m_width(nWidth), m_height(nHeight), m_format(format) 
{  
	HRESULT hr = 0;


 
	
	
};
 *****************/


 
//==============================================================

} // end namespace
} // end namespace
} // end namespace
} // end namespace



//=========================================================
static HRESULT __CPPI_Init()
{
	HRESULT  hr = 0;

	static bool stb_firstcall = true;
	if(stb_firstcall) 
	{
		stb_firstcall = false;

		// hr |= DAPLIB_RegisterDeviceCritResRelCallback ( __CPPI_DeviceCritResRel ,  NULL );   

		// none
	}


	return hr;
}


#endif  // #if ( defined(WIN32) && defined(GB_D3D9) )
// end file