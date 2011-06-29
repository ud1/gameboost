// ok ! 

#include "d3d9pch.h"

#include "computesurfacepixelcolorobject.h"

static IDirect3DSurface9* __getBackBuffer(IDirect3DDevice9* pdevice) 
{
	IDirect3DSurface9* res = NULL;
	HRESULT hr = pdevice->GetBackBuffer( 0 , 0, D3DBACKBUFFER_TYPE_MONO, &res  );
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return res;
};

static D3DSURFACE_DESC __getBackBufferDescr(IDirect3DDevice9* pdevice) 
{
	D3DSURFACE_DESC res;
	IDirect3DSurface9* pbbuf = __getBackBuffer(pdevice);
	HRESULT hr = pbbuf->GetDesc(&res);
	if(pbbuf)
	{
		pbbuf->Release();
	}

	if FAILED(hr) throw std::runtime_error("Failed operation");
	return res;
};


//===================================================================
HRESULT ComputeSurfacePixelColorObject::CheckCreateInterfaces(IDirect3DDevice9 *pdevice, const D3DSURFACE_DESC *psrfdes)
{
  HRESULT hr = 0;

  if (!m_pTxtrRenderTarget_1x1)
  {

    __try
    {

      hr |= pdevice->CreateTexture(1,  //UINT Width,
      1,  //UINT Height,
      1,  //UINT Levels,
      D3DUSAGE_RENDERTARGET,  // DWORD Usage,
      psrfdes->Format,  // D3DFORMAT Format,
      D3DPOOL_DEFAULT,  // D3DPOOL Pool,
       &m_pTxtrRenderTarget_1x1, NULL  // HANDLE* pSharedHandle
      );

    }
    __except(1)
    {
     // MONPRINT("Exception create texture ");
	  assert(false && "Exception create texture " );
      hr |= E_FAIL;
    };

    if FAILED(hr)
    {
      return hr;
    }

    __try
    {
      hr |= m_pTxtrRenderTarget_1x1->GetSurfaceLevel(0,  &m_pSrfRenderTarget_1x1);
    }
    __except(1)
    {
     // MONPRINT("Exception GetSurfaceLevel");
	   assert(false && "Exception GetSurfaceLevel" );
      hr |= E_FAIL;
    }

    if FAILED(hr)
    {
      return hr;
    }


  };



  if (!m_pTxtrMemory_1x1)
  {
    __try
    {

      hr |= pdevice->CreateTexture(1,  //UINT Width,
      1,  //UINT Height,
      1,  //UINT Levels,
      D3DUSAGE_DYNAMIC,  // DWORD Usage,
      psrfdes->Format,  // D3DFORMAT Format,
      D3DPOOL_SYSTEMMEM,  // D3DPOOL_DEFAULT, // D3DPOOL Pool,
       &m_pTxtrMemory_1x1, NULL  // HANDLE* pSharedHandle
      );

    }
    __except(1)
    {
      //MONPRINT("Exception CreateTexture");
	  assert( false && "Exception CreateTexture" );
      hr |= E_FAIL;
    }

    if FAILED(hr)
    {
      return hr;
    }

    __try
    {
      hr |= m_pTxtrMemory_1x1->GetSurfaceLevel(0, &m_pSrfMemory_1x1);
    }
    __except(1)
    {
      //MONPRINT("Exception GetSurfaceLevel");
      assert(false && "Exception GetSurfaceLevel");
      hr |= E_FAIL;
    }


    if FAILED(hr)
    {
      return hr;
    }


  }


  return hr;
};

//===================================================================
HRESULT ComputeSurfacePixelColorObject::ComputeSurfacePixelColor(
		gb_out gb::color::Color4f *pColorOut, 
		 //PINC context,
		 IDirect3DDevice9 *pdevice, 
		 gb_in POINT &pntCoord, 
		  IDirect3DSurface9 *pSrf)
{
  HRESULT hr = 0;
  assert(pdevice);
  assert(pColorOut);
  assert(pSrf);


    D3DSURFACE_DESC bbsd =  __getBackBufferDescr(pdevice);
 

  // check valid point coordinate
  if (pntCoord.x < 0)
  {
    return S_FALSE;
  }

  if (pntCoord.y < 0)
  {
    return S_FALSE;
  }

  if (pntCoord.x > (int)bbsd.Width - 1)
  {
    return S_FALSE;
  }

  if (pntCoord.y > (int)bbsd.Height - 1)
  {
    return S_FALSE;
  }


  //  make rect
  RECT rct;
  rct.top = pntCoord.y;
  rct.left = pntCoord.x;
  rct.bottom = rct.top + 1;
  rct.right = rct.left + 1;

  // check interfaces
  __try
  {
    hr |= CheckCreateInterfaces( pdevice,  &bbsd );
  }
  __except(1)
  {
    // MONPRINT("Exception  CheckCreateInterfaces");
    assert(false && "Exception  CheckCreateInterfaces");
    hr |= E_FAIL;
  }

  if FAILED(hr)
  {
    return hr;
  }


  // make job surface
  IDirect3DSurface9 *pSrcSurface = NULL;
  if (pSrf)
  {
    pSrcSurface = pSrf;
  }
  else
  {
    assert(false);
	return E_FAIL;
  }


  // StretchRect
  __try
  {
    hr |= pdevice->StretchRect(pSrcSurface, &rct, m_pSrfRenderTarget_1x1, NULL, D3DTEXF_LINEAR);
  }
  __except(1)
  {
    //MONPRINT("Exception  CheckCreateInterfaces");
    assert(false && "Exception  CheckCreateInterfaces");
    hr |= E_FAIL;
  }

  if FAILED(hr)
  {
    return hr;
  }


  // copy render target
  __try
  {
    hr |= pdevice->GetRenderTargetData(m_pSrfRenderTarget_1x1, m_pSrfMemory_1x1);
  }
  __except(1)
  {
    hr |= E_FAIL;
  }

  if FAILED(hr)
  {
    return hr;
  }


  // lock
  D3DLOCKED_RECT lockedRect;
  DWORD dwLockedflags = D3DLOCK_READONLY;

  hr |= m_pSrfMemory_1x1->LockRect(&lockedRect, NULL, dwLockedflags);
  if FAILED(hr)
  {
    return hr;
  }

  // get pixels
  D3DCOLOR d3dcol = 0;

  // memcpy(&d3dcol, lockedRect.pBits, sizeof(D3DCOLOR)  );

  // copy data
  __try
  {
    d3dcol = *((D3DCOLOR*)(lockedRect.pBits));
  }
  __except(1)
  {
    assert(false);
    hr |= E_FAIL;
  }


  hr |= m_pSrfMemory_1x1->UnlockRect();

  if FAILED(hr)
  {
    return hr;
  }

  // copy pixels to result
  BYTE byteTemp;
  byteTemp = BYTE(d3dcol >> 24);
  pColorOut->a = (FLOAT)byteTemp / 255.0f;
  byteTemp = BYTE(d3dcol >> 16);
  pColorOut->r = (FLOAT)byteTemp / 255.0f;
  byteTemp = BYTE(d3dcol >> 8);
  pColorOut->g = (FLOAT)byteTemp / 255.0f;
  byteTemp = BYTE(d3dcol >> 0);
  pColorOut->b = (FLOAT)byteTemp / 255.0f;


  return hr;
};




// end file
