/** \file
 \brief Класс для вычисления цвета пикселя поверхности

 */

#pragma once

#include <gb/color/color.h>
#include <d3d9.h>



/** \brief Вычисление цвета пикселя. */
class ComputeSurfacePixelColorObject
{


  public:
    ComputeSurfacePixelColorObject()
    {
        ReleaseInterfaces();
    }
    ~ComputeSurfacePixelColorObject()
    {
        ReleaseInterfaces();
    }

	//IDirect3DSurface9
	//IDirect3DTexture9


    //===================================================================
    HRESULT ComputeSurfacePixelColor_ksmtcColor(
		gb_out gb::color::Color4f  *pColorOut, 
		//PINC context, 
		IDirect3DDevice9* pdevice,
		gb_in POINT &pntCoord, 
		gb_inout_opt IDirect3DSurface9 *pSrf)

    {
        HRESULT hr = 0;

        __try
        {
            hr |= ComputeSurfacePixelColor( 
				pColorOut, 
				//context,
				pdevice, 
              pntCoord,
			  pSrf);
        }
        __except(1)
        {
            // error
            hr |= E_FAIL;

        }

        return hr;
    };
 
    HRESULT ComputeSurfacePixelColor(
			gb_out gb::color::Color4f *pColorOut, 
			//PINC context,
			IDirect3DDevice9* pdevice,
			gb_in POINT &pntCoord, 
			gb_inout_opt IDirect3DSurface9 *pSrf) ;
 
    HRESULT ReleaseInterfaces()
    {
        HRESULT hr = 0;

        GB_SAFE_REL(m_pSrfRenderTarget_1x1);
        GB_SAFE_REL(m_pTxtrRenderTarget_1x1);

        GB_SAFE_REL(m_pSrfMemory_1x1);
        GB_SAFE_REL(m_pTxtrMemory_1x1);

        return hr;
    };



  private:

 
    HRESULT CheckCreateInterfaces(IDirect3DDevice9 *pdevice, const D3DSURFACE_DESC *psrfdes) ;

    IDirect3DSurface9 *m_pSrfRenderTarget_1x1;
    IDirect3DTexture9 *m_pTxtrRenderTarget_1x1;

    IDirect3DSurface9 *m_pSrfMemory_1x1;
    IDirect3DTexture9 *m_pTxtrMemory_1x1;

};

// end file