/** \file 
* \brief ������������ ��� dapplLibr
*
*
*

 \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
 
 \todo ������ __exc_mon
*/

#if ( defined(WIN32) && defined(GB_D3D9) )

#pragma once
#define __GB_D3D9_RENDERTARGET_H__

#include <gb/Config.h>

#include <d3d9.h>

#include <gb/base/Types.h>
#include <gb/color/color.h>

#include <gb/math/math.h>

#define  __exc_mon __except(1)


/// begin �����-����� ���������� -------------


/** \brief ������������ ��������  ������  ��� ������ (������ NULL ���� ���������).  */
#define   _in  const
/** \brief ������������ �������� ��� ������ (������ NULL ���� ���������).  */
#define   _out
/** \brief ������������ �������� ��� ������ � ������ (������ NULL ���� ���������) .  */
#define   _inout
/** \brief ������������ �������� (�� ���������)  ��� ������ (����� �������� NULL ���� ���������).  */
#define   _in_opt  const
/** \brief ������������ �������� (�� ���������) ��� ������ (����� �������� NULL ���� ���������) .  */
#define   _out_opt
/** \brief ������������ �������� (�� ���������) ��� ������ � ������ (����� �������� NULL ���� ���������).  */
#define   _inout_opt
/** \brief ������������ �������� ��������� (����� �������� NULL ).   */
#define   _opt 


/// end ---------------------------------------

#include <gb/base/Rectangle.h>


//#ifndef  DAPPLLIBR_H
//   #pragma  message("������ �� ������������� ��������� ����� !!"  __FILE__)
//    // #error file dapplLibr.h most be a first included
//#endif

//! \brief ���� != 0 , �� ����� ������������ DLL   
#define DAPL_RENDERTARGET_AS_DLL  1

#ifndef  DAPPLLIBR_H
  #define DLL_DAPPLLIBRARY_API
#endif
 

#if (DAPL_RENDERTARGET_AS_DLL != 0)
	   #define  DAPP_RT_API  HRESULT  DLL_DAPPLLIBRARY_API 
	   #define  DAPP_RT_CONSTRUCT   DLL_DAPPLLIBRARY_API 
#else
       #define  DAPP_RT_API  HRESULT 
       #define  DAPP_RT_CONSTRUCT   
#endif


/** \brief ������������ ���-�� �������������� � ���� */
#define DAPPL_MAX_RENDERTARGETS_ONPOOL     32


/** \brief ������ ����������� ������������� � ���� ������������  */
enum DAPLIB_RT_SIZE_ENM 
{
  RTSZ_UNDEF = 0,  ///< �� ����������

  RTSZ_FULLSCREEN,   ///<  ������������� �������

  RTSZ_HALF_FULLSCREEN,	     ///<    ������ � ������ �� ��� ������
  RTSZ_THIRD_FULLSCREEN,     ///<    ������ � ������ �� ����� ������
  RTSZ_FOURTH_FULLSCREEN,    ///<	 ������ � ������ �� �������� ������

  RTSZ_64x64,      ///<   64 x 64
  RTSZ_256x256,	   ///<	  256 x 256
  RTSZ_512x512,	   ///<   512 x 512
  RTSZ_1024x1024   ///<   1024 x 1024
};

/** \brief ���������� ���������� ������� ����������� �������������. 
  ����� E_FAIL ���� �������� ������������ ���������  */
DAPP_RT_API DAPLIB_RT_ComputeNeedRtSize(_out UINT& nOutWidth, _out UINT& nOutHeight, 
										const DAPLIB_RT_SIZE_ENM eSize, 
										const UINT nScreenWidth, const UINT nScreenHeight  );


/** \brief ������� ���������� �����������   */
DAPP_RT_API DAPLIB_RT_CreateInterfaces(_out IDirect3DSurface9** ppOutISrf, _out IDirect3DTexture9** ppOutITxtr, 
									   IDirect3DDevice9* pdevice, 
									      const UINT nWidth, const UINT nHeight, const D3DFORMAT frmt );

/** \brief ����������  ������ ��� �������������� */
DAPP_RT_API DAPLIB_RT_SetDevice(IDirect3DDevice9* pdevice);
/** \brief ���������� ��������� ������ ���������  (���������)  */
DAPP_RT_API DAPLIB_RT_SetBackBufSurfDescr(const D3DSURFACE_DESC* descr);
/** \brief ���������� ��������� �� ����������� ������ ���������  (���������) */
DAPP_RT_API DAPLIB_RT_SetBackBufFrameDrawIntrfPtr(IDirect3DSurface9* psurf);
/** \brief ���������� �������� ��� ������������� � ���� ��� ��������������   */
DAPP_RT_API DAPLIB_RT_SetUnUsedAll();

/** \brief ���������� ������ �������� ����� �����������  */
DAPP_RT_API DAPLIB_RT_ComputeAverSurfaceColor(
			_out gb::color::Color4f* pOut, 
			_inout_opt IDirect3DSurface9* surf,
			_in_opt gb::math::geom2d::Rect* rect);

DAPP_RT_API DAPLIB_RT_ComputeSurfacePixelColor(_out gb::color::Color4f* pColorOut, _in POINT& pntCoord, _inout_opt IDirect3DSurface9* pSrf);


class IRenderTarget;



/** \brief  ������ ������. ����������� ��� ��������� � �� / 
    ������ �������� IDAPLIB_RenderTarget  */
class IRenderTarget 
{
public:
//protected:
	  virtual   ~IRenderTarget() {};

public:

	/** \brief ������ �����������. ���� ���� ����� ������������� ������ */
	virtual UINT GetWidth()  const =0;
	/** \brief ������ �����������. ���� ���� ����� ������������� ������ */
	virtual UINT GetHeight() const =0;

	//DAPP_RT_CONSTRUCT IDAPLIB_RenderTarget(const UINT nWidth, const UINT nHeight, 
	    //const D3DFORMAT format=D3DFMT_UNKNOWN);
	       


	/** \brief �������� ���������  �������� */
	virtual IDirect3DTexture9*  GetITexture() const  =0;
    /** \brief �������� ���������   ����������� */
	virtual IDirect3DSurface9* GetISurface() const  =0;
	/** \brief �������� ������ ����������� */
	virtual D3DFORMAT GetFormat() const =0;

	/** \brief ���������� ���� ������������� . 
	   ���� true (������������), �� �� ������� �� ��������� ������������ �� �� ����� ������������ */
	virtual void  SetUsed(bool bUsed) const =0;
	/** \brief ������������ ��� ��� � ��������� � ������� ����� */
	virtual bool IsUsed() const =0;

	/** \brief ���������  �� ���������� ���������� */
	virtual bool IsSameInterfaces(const IRenderTarget* prt) const =0; 
 
	/** \brief  ���������� ��� ������� ���������. */
    virtual HRESULT MakeAsCurrentRender()  const =0;
	/** \brief ������������ ������������ � �������� ������� */
    virtual HRESULT MakeRenderToBackBuffer()  const =0;
 
	/** \brief ��������� ����������.  */
    virtual HRESULT  CheckCreateInterfaces() const =0;

	/** \brief ��������� ������. */
    virtual HRESULT  FillSurfaceColor(const D3DCOLOR color) const =0;
	/** \brief ��������� ������. */
	virtual HRESULT  FillSurfaceColor(const D3DCOLORVALUE& color) const =0;

	/** \brief ����������� �� ������� �������������.   */
    virtual HRESULT  StretchFrom(const IRenderTarget* rtarget, const D3DTEXTUREFILTERTYPE ft=D3DTEXF_LINEAR) const =0;
    /** \brief ����������� �� ������ �����������.   */
    virtual HRESULT  StretchFrom(IDirect3DSurface9* pISurface, const D3DTEXTUREFILTERTYPE ft=D3DTEXF_LINEAR ) const =0;

	/** \brief ����������� � ������ ������������.   */
	virtual HRESULT  StretchTo(const IRenderTarget* rtarget, const D3DTEXTUREFILTERTYPE ft=D3DTEXF_LINEAR ) const =0;
	/** \brief ����������� � ������ �����������.  ��������� !!!!!  */
	virtual HRESULT  StretchTo(IDirect3DSurface9* pISurface, const D3DTEXTUREFILTERTYPE ft=D3DTEXF_LINEAR ) const =0;

	/** \brief �������� �� ���������� ����������� . �������� � ��� � ���������� ����������  */
    virtual HRESULT  ValidateInterfaces() const =0;
	


protected:
	virtual HRESULT  CreateInterfeces(IDirect3DDevice9* pdevice) = 0;
 
	/** \brief ������� ����������.  */
	virtual HRESULT ReleaseInterfaces() const =0;
 
};
// end class

 
/** \brief �������� ��������� ��� ��������� ����������� */
DAPP_RT_API DAPLIB_RT_GetUnusedRenderTarget(_out IRenderTarget** ppOut, const DAPLIB_RT_SIZE_ENM eSize);
DAPP_RT_API DAPLIB_RT_GetUnusedRenderTarget(_out IRenderTarget** ppOut, const UINT nWidth, const UINT nHeight);





#endif // #if ( defined(WIN32) && defined(GB_D3D9) )
// end file