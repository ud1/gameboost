/** \file 
* \brief Рендертаргет для dapplLibr
*
*
*


 \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
 
 \todo убрать __exc_mon
 \todo Убрать зависимость от gb::color
 \todo  Переименовать макролпределения
 \todo  Убрать __exc_mon
*/

#if ( defined(WIN32) && defined(GB_D3D9) )

#pragma once
#define __GB_D3D9_RENDERTARGET_H__

#include <gb/Config.h>
#include <gb/base/Types.h>
#include <gb/base/Rectangle.h>

#include <d3d9.h>

#ifdef GB_COLOR
   #include <gb/color/color.h>
#endif

#ifndef GB_COLOR
#error gb::color пока нужен. Определить макрос GB_COLOR
#endif



//#ifdef GB_FMATH
   #include <gb/fmath/fmath.h>
//#endif

/*
#ifndef GB_FMATH
  #error  gb::math  пока нужен. Определить GB_MATH
#endif
*/


// УБРАТЬ !!
#define  __exc_mon __except(1)


/// begin макро-метки параметров -------------


/** \brief Обязательный параметр  только  для чтения (нельзя NULL если указатель).  */
#define   _in  const
/** \brief Обязательный параметр для записи (нельзя NULL если указатель).  */
#define   _out
/** \brief Обязательный параметр для чтения и записи (нельзя NULL если указатель) .  */
#define   _inout
/** \brief Опциональный параметр (по умолчанию)  для чтения (можно передать NULL если указатель).  */
#define   _in_opt  const
/** \brief Опциональный параметр (по умолчанию) для записи (можно передать NULL если указатель) .  */
#define   _out_opt
/** \brief Опциональный параметр (по умолчанию) для чтения и записи (можно передать NULL если указатель).  */
#define   _inout_opt
/** \brief Опциональный параметр указатель (можно передать NULL ).   */
#define   _opt 


/// end ---------------------------------------




//#ifndef  DAPPLLIBR_H
//   #pragma  message("ЗАЩИТА ОТ НЕПРАВИЛЬНОГО ВКЛЮЧЕНИЯ СНЯТА !!"  __FILE__)
//    // #error file dapplLibr.h most be a first included
//#endif

//! \brief Если != 0 , то будет использована DLL   
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


/** \brief Максимальное кол-во рендертаргетов в пуле  ПЕРЕИМЕНОВАТЬ!!!! */
#define GB_D3D9_MAX_RENDERTARGETS_ONPOOL     32


namespace gb {
namespace graphics {
namespace d3d9 { 
namespace rt {


/** \brief Размер поверхность рендертаргета в виде перечисления   ПЕРЕИМЕНОВАТЬ !!! */
enum RENDERTARGET_SIZE_ENUM 
{
  RTSZ_UNDEF = 0,  ///< не определено

  RTSZ_FULLSCREEN,   ///<  полноэкранные размеры

  RTSZ_HALF_FULLSCREEN,	     ///<    ширина и высота на пол экрана
  RTSZ_THIRD_FULLSCREEN,     ///<    ширина и высота на треть экрана
  RTSZ_FOURTH_FULLSCREEN,    ///<	 ширина и высота на четверть экрана

  RTSZ_64x64,      ///<   64 x 64
  RTSZ_256x256,	   ///<	  256 x 256
  RTSZ_512x512,	   ///<   512 x 512
  RTSZ_1024x1024   ///<   1024 x 1024
};

/** \brief Вычисление требуемого размера поверхности рендертаргета. 
  Вернёт E_FAIL если переданы некорректные аргументы  */
DAPP_RT_API ComputeNeedRtSize(_out UINT& nOutWidth, _out UINT& nOutHeight, 
										const RENDERTARGET_SIZE_ENUM eSize, 
										const UINT nScreenWidth, const UINT nScreenHeight  );


/** \brief Создать интерфейсы поверхности   */
DAPP_RT_API CreateRenderTargetInterfaces(_out IDirect3DSurface9** ppOutISrf,
									   _out IDirect3DTexture9** ppOutITxtr, 
									   IDirect3DDevice9* pdevice, 
									   const UINT nWidth, 
									   const UINT nHeight, 
									   const D3DFORMAT frmt );

/** \brief Утсановить  девайс для рендертаргетов УДАЛИТЬ */
DAPP_RT_API RenderTargetSetDevice(IDirect3DDevice9* pdevice);
/** \brief Установить структуру буфера отрисовки  (бэкбуфера) УДАЛИТЬ  */
DAPP_RT_API DAPLIB_RT_SetBackBufSurfDescr(const D3DSURFACE_DESC* descr);
/** \brief Установить указатель на поверхность буфера отрисовки  (бэкбуфера) */
DAPP_RT_API DAPLIB_RT_SetBackBufFrameDrawIntrfPtr(IDirect3DSurface9* psurf);
/** \brief Установить Пометить все рендертаргеты в пуле как неиспользуемые   */
DAPP_RT_API DAPLIB_RT_SetUnUsedAll();

/** \brief Вычисление общего среднего цвета поверхности  */
DAPP_RT_API DAPLIB_RT_ComputeAverSurfaceColor(
			_out gb::color::Color4f* pOut, 
			_inout_opt IDirect3DSurface9* surf,
			_in_opt gb::fmath::geom2d::Rect* rect);

DAPP_RT_API DAPLIB_RT_ComputeSurfacePixelColor(_out gb::color::Color4f* pColorOut, _in POINT& pntCoord, _inout_opt IDirect3DSurface9* pSrf);


 

/** \brief  Рендер таргет. Поверхность для отрисовки в неё / 
    Старое название IDAPLIB_RenderTarget  */
class IRenderTarget {
public:
	  virtual   ~IRenderTarget() {}


	/** \brief Ширина поверхности. Если ноль тогда полноэкранная ширина */
	virtual UINT getWidth()  const =0;
	/** \brief Высота поверхности. Если ноль тогда полноэкранная высота */
	virtual UINT getHeight() const =0;

	//DAPP_RT_CONSTRUCT IDAPLIB_RenderTarget(const UINT nWidth, const UINT nHeight, 
	    //const D3DFORMAT format=D3DFMT_UNKNOWN);
	       


	/** \brief Получить интерфейс  текстуры */
	virtual IDirect3DTexture9*  getITexture() const  =0;
    /** \brief Получить интерфейс   поверхности */
	virtual IDirect3DSurface9* getISurface() const  =0;
	/** \brief Получить формат поверхности */
	virtual D3DFORMAT getFormat() const =0;

	/** \brief Установить флаг использования . 
	   Если true (используется), то по запросу на свободный рендертаргет он не будет возвращаться */
	virtual void  SetUsed(bool bUsed) const =0;
	/** \brief Используется или нет в отрисовке в текущем кадре */
	virtual bool IsUsed() const =0;

	/** \brief Сравнение  на одинаковые интерфейсы */
	virtual bool IsSameInterfaces(const IRenderTarget* prt) const =0; 
 
	/** \brief  Установить как текущую отрисовку. */
    virtual HRESULT MakeAsCurrentRender()  const =0;
	/** \brief Восстановить рендертаргет в бэкбуфер девайса */
    virtual HRESULT MakeRenderToBackBuffer()  const =0;
 
	/** \brief Проверить интерфейсы.  */
    virtual HRESULT  CheckCreateInterfaces() const =0;

	/** \brief Заполнить цветом. */
    virtual HRESULT  FillSurfaceColor(const D3DCOLOR color) const =0;
	/** \brief Заполнить цветом. */
	virtual HRESULT  FillSurfaceColor(const D3DCOLORVALUE& color) const =0;

	/** \brief Скопировать из другого рендертаргета.   */
    virtual HRESULT  StretchFrom(const IRenderTarget* rtarget, const D3DTEXTUREFILTERTYPE ft=D3DTEXF_LINEAR) const =0;
    /** \brief Скопировать из другой поверхности.   */
    virtual HRESULT  StretchFrom(IDirect3DSurface9* pISurface, const D3DTEXTUREFILTERTYPE ft=D3DTEXF_LINEAR ) const =0;

	/** \brief Скопировать в другой рендертаргет.   */
	virtual HRESULT  StretchTo(const IRenderTarget* rtarget, const D3DTEXTUREFILTERTYPE ft=D3DTEXF_LINEAR ) const =0;
	/** \brief Скопировать в другую поверхность.  ПРОВЕРИТЬ !!!!!  */
	virtual HRESULT  StretchTo(IDirect3DSurface9* pISurface, const D3DTEXTUREFILTERTYPE ft=D3DTEXF_LINEAR ) const =0;

	/** \brief Проверка на валидность интерфейсов . Проверка в лоб с перехватом исключения  */
    virtual HRESULT  ValidateInterfaces() const =0;
	


protected:
	virtual HRESULT  CreateInterfeces(IDirect3DDevice9* pdevice) = 0;
 
	/** \brief Удалить интерфейсы.  */
	virtual HRESULT ReleaseInterfaces() const =0;
 
};
// end class

 
/** \brief Получить свободную для отрисовки поверхность */
DAPP_RT_API DAPLIB_RT_GetUnusedRenderTarget(_out IRenderTarget** ppOut, const RENDERTARGET_SIZE_ENUM eSize);
DAPP_RT_API DAPLIB_RT_GetUnusedRenderTarget(_out IRenderTarget** ppOut, const UINT nWidth, const UINT nHeight);





} // end namespace
} // end namespace
} // end namespace
} // end namespace


#endif // #if ( defined(WIN32) && defined(GB_D3D9) )
// end file