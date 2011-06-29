 // ok !

#include "d3d9pch.h"
#include "surfavearcolorcomputer.h"

#pragma warning(push)
#pragma warning (disable : 4244)
#pragma warning (disable : 4996)


//=================================================
HRESULT SurfAvearcolInterfaces::CreateStretched(IDirect3DDevice9 *device, 
												UINT w, UINT h, 
												const D3DSURFACE_DESC *des)
{
  HRESULT hr = 0;

  // создание стреча 256 * 256
  hr |= device->CreateTexture(w, h, 1, D3DUSAGE_RENDERTARGET,  //DWORD Usage,
  des->Format,  // D3DFORMAT Format,   // задний экранный передаётся как  D3DFMT_X8R8G8B8 
  des->Pool,  // D3DPOOL_DEFAULT, //D3DPOOL Pool,
   &texture, NULL);
  if FAILED(hr)
  {
    //* Create  stretched texture    error  
    return hr;
  }

  //* получение поверхности стретча
  hr |= texture->GetSurfaceLevel(0, &surface);
  if FAILED(hr)
  {
    Release();
    //* error stretched texture->GetSurfaceLevel 
    return hr;
  }

  return hr;
};

//======================================================
HRESULT SurfAvearcolInterfaces::CreateEnd(IDirect3DDevice9 *device, 
										  const D3DSURFACE_DESC *des)
{
  HRESULT hr = 0;
  hr |= device->CreateTexture(1,  // UINT Width,
  1,  // UINT Height,
  1,  // UINT Levels,
  0,  // DWORD Usage,
  des->Format,  //  D3DFMT_R8G8_B8G8, // D3DFORMAT Format,
  D3DPOOL_SYSTEMMEM,  // D3DPOOL Pool,
   &texture, NULL);
  if FAILED(hr)
  {
    //*  Error Create end texture  
    return hr;
  }

  hr |= texture->GetSurfaceLevel(0, &surface);
  if FAILED(hr)
  {
    Release();
    //* error get surf level
    return hr;
  };

  return hr;
};




//==============================================================
SurfAvearColorComputer::SurfAvearColorComputer()
{
  m_strError[0] = 0;
};

//=====================================================
//SurfAvearColorComputer* SurfAvearColorComputer::GetGlobalInstance()
// {
//	return &g_SurfAvearColorComputer;
//};

//=====================================================
HRESULT SurfAvearColorComputer::CheckInit()
{
  HRESULT hr = 0;

  {
    //static bool stb_firstcall = true;
    //if (stb_firstcall)
    //{
    //  stb_firstcall = false;

    //  // init code
    //  hr |= DAPLIB_RegisterDeviceCritResRelCallback(__CPPI_DeviceCritResRel, NULL);


    //}

  }



  return hr;
}

//===================================================================
HRESULT SurfAvearColorComputer::ComputeColor(gb_out gb::color::Color4f *pOut,
											 IDirect3DDevice9 *device, 
											 IDirect3DSurface9 *surf, 
											 const RECT *rect)
{
  D3DCOLOR col;
  HRESULT hr = Compute(&col, device, surf, rect);
  if FAILED(hr)
  {
    return hr;
  }
  BYTE byteTemp;
  byteTemp = col >> 24;
  pOut->a = (FLOAT)byteTemp / 255.0f;
  byteTemp = col >> 16;
  pOut->r = (FLOAT)byteTemp / 255.0f;
  byteTemp = col >> 8;
  pOut->g = (FLOAT)byteTemp / 255.0f;
  byteTemp = col >> 0;
  pOut->b = (FLOAT)byteTemp / 255.0f;
  /*
  //  correct small
  if(pOut->a < 0.01f) { pOut->a = 0.0f;  };
  if(pOut->r < 0.01f) { pOut->r = 0.0f;  };
  if(pOut->g < 0.01f) { pOut->g = 0.0f;  };
  if(pOut->b < 0.01f) { pOut->b = 0.0f;  };
   */

  return hr;
};


//======================================================
HRESULT SurfAvearColorComputer::Compute(D3DCOLOR *pOut, IDirect3DDevice9 *device, IDirect3DSurface9 *surf, const RECT *rect)
{
  HRESULT hr = 0;

  hr |= CheckInit();
  if FAILED(hr)
  {
	  return hr;
  }


  hr |= CreateInterfaces(device);
  if FAILED(hr)
  {
    return hr;
  }

  if (surf)
  {
    //* код проверки формата
    D3DSURFACE_DESC srcSurfDesc; //* описание переданой поверхности.
    D3DSURFACE_DESC stretchSurfDesc; //* описание стретч поверхности.
    hr |= surf->GetDesc(&srcSurfDesc);
    if FAILED(hr)
    {
      strcpy(m_strError, "Error  surf->GetDesc ");
      return hr;
    }

    hr |= m_stretch1x1.surface->GetDesc(&stretchSurfDesc);
    bool bCheckRes = CheckSourceDescription(&srcSurfDesc, &stretchSurfDesc);
    if (!bCheckRes)
    {
      strcpy(m_strError, "Error  different format ");
      return E_FAIL;
    }
  } //if

  //* Begin operation
  IDirect3DSurface9 *surfOper = NULL;

  if (surf)
  {
    surfOper = surf;
  }
  else
  {
    hr |= device->GetRenderTarget(0, &surfOper);
    if FAILED(hr)
    {
      strcpy(m_strError, "Error  device->GetRenderTarget ");
      return hr;
    }
  } // if(surf)/else

  //* stretch
  //

  D3DTEXTUREFILTERTYPE filter = 
  // D3DTEXF_NONE       
  //  D3DTEXF_POINT      
  D3DTEXF_LINEAR 
  //  D3DTEXF_ANISOTROPIC  
  ;
  //* first stretch
  hr |= device->StretchRect(surfOper, rect, m_stretch256x256.surface, NULL, filter);
  if FAILED(hr)
  {
    if (surfOper)
    {
      surfOper->Release();
      surfOper = NULL;
    };
    strcpy(m_strError, "Error  device->StretchRect  from input surface  ");
    return hr;
  };

  //* stretch again

  hr |= device->StretchRect(m_stretch256x256.surface, NULL, m_stretch32x32.surface, NULL, filter);
  hr |= device->StretchRect(m_stretch32x32.surface, NULL, m_stretch8x8.surface, NULL, filter);
  hr |= device->StretchRect(m_stretch8x8.surface, NULL, m_stretch4x4.surface, NULL, filter);
  hr |= device->StretchRect(m_stretch4x4.surface, NULL, m_stretch2x2.surface, NULL, filter);
  hr |= device->StretchRect(m_stretch2x2.surface, NULL, m_stretch1x1.surface, NULL, filter);
  if FAILED(hr)
  {
    strcpy(m_strError, "Error  device->StretchRect ");
    return hr;
  }

  hr |= device->GetRenderTargetData(m_stretch1x1.surface, m_end.surface);
  if FAILED(hr)
  {
    strcpy(m_strError, " Error device->GetRenderTargetData ");
    if (surfOper)
    {
      surfOper->Release();
      surfOper = NULL;
    };
    return hr;
  };

  /// end
  //

  if (surf == NULL)
  {
    surfOper->Release();
    surfOper = NULL;
  }

  //* вычисление конечного цвета
  D3DLOCKED_RECT locrect;
  static DWORD FlagsLock = 0x00000010L  // D3DLOCK_READONLY
  //      0x00002000L	// D3DLOCK_DISCARD
  //   0x00001000L	  // D3DLOCK_NOOVERWRITE
  //     0x00000800L	// D3DLOCK_NOSYSLOCK
  //     0x00004000L // D3DLOCK_DONOTWAIT     

  ;

  hr |= m_end.surface->LockRect( &locrect, NULL, FlagsLock);
  if FAILED(hr)
  {
    strcpy(m_strError, " Error m_end.surface->LockRect ");
    return hr;
  };



  //locrect.
  D3DCOLOR d3dColor = 0;
  d3dColor = *((D3DCOLOR*)(locrect.pBits));
  hr |= m_end.surface->UnlockRect();
  if FAILED(hr)
  {
    strcpy(m_strError, " Error m_end.surface->UnlockRect ");
    return hr;
  };
  *pOut = d3dColor;

  m_strError[0] = 0;
  return hr;
};

//===========================================================
HRESULT SurfAvearColorComputer::CreateInterfaces(IDirect3DDevice9 *device)
{
  HRESULT hr = 0;
  //* проверка на уже созданое
  if (m_end.texture)
  {
    return hr;
  };

  IDirect3DSurface9 *pBackBuffer = NULL;
  hr |= device->GetBackBuffer(0,  //UINT  iSwapChain,
  0,  //UINT BackBuffer,
  D3DBACKBUFFER_TYPE_MONO,  //D3DBACKBUFFER_TYPE Type,
   &pBackBuffer);
  if FAILED(hr)
  {
    strcpy(m_strError, "Error device->GetBackBuffer");
    return hr;
  };
  D3DSURFACE_DESC bbDescr;
  hr |= pBackBuffer->GetDesc(&bbDescr);
  if FAILED(hr)
  {
    if (pBackBuffer)
    {
      pBackBuffer->Release();
      pBackBuffer = NULL;
    };
    strcpy(m_strError, "Error pBackBuffer->GetDesc ");
    return hr;
  }
  if (pBackBuffer)
  {
    pBackBuffer->Release();
    pBackBuffer = NULL;
  };

  hr |= m_stretch256x256.CreateStretched(device, 256, 256, &bbDescr);
  hr |= m_stretch32x32.CreateStretched(device, 32, 32, &bbDescr);
  hr |= m_stretch8x8.CreateStretched(device, 8, 8, &bbDescr);
  hr |= m_stretch4x4.CreateStretched(device, 4, 4, &bbDescr);
  hr |= m_stretch2x2.CreateStretched(device, 2, 2, &bbDescr);
  hr |= m_stretch1x1.CreateStretched(device, 1, 1, &bbDescr);
  if FAILED(hr)
  {
    strcpy(m_strError, "Error CreateStretched ");
    return hr;
  };

  hr |= m_end.CreateEnd(device, &bbDescr);
  if FAILED(hr)
  {
    strcpy(m_strError, "Error Create end resource ");
    return hr;
  };

  return hr;
};



#pragma warning(pop)
// end file
