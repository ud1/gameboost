/** \file 
* \brief Рендертаргет для dapplLibr


 \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
 
 \todo убрать __except(1)
 \todo Убрать зависимость от gb::color
 \todo  Переименовать макролпределения
 
*/

 

#if ( defined(WIN32) && defined(_D3D9_H_) )

#pragma once
#define __GB_D3D9_RENDERTARGET_H__

//#include <gb/Config.h>
#include <gb/base/Types.h>
#include <gb/base/Rectangle.h>

#include <gb/color/color.h>
#include <gb/fmath/fmath.h>
#include <gb/graphics/RenderTarget.h>
 
#include <d3d9.h>
//#include <gb/graphics/d3d9/auto_include_libr.h>

 

#define  GB_D3D9_RT_API HRESULT  

/** \brief Максимальное кол-во рендертаргетов в пуле   */
#define GB_D3D9_MAX_RENDERTARGETS_ONPOOL     32


namespace gb 
{
namespace graphics 
{
namespace d3d9 
{ 
namespace rendertarget 
{



/** \brief Размер поверхность рендертаргета в виде перечисления   ПЕРЕИМЕНОВАТЬ !!! */
enum RenderTargeteSize_e 
{
  UNDEFINED = 0,  ///< НЕ ОПРЕДЕЛЕНО !

  FULLSCREEN,   ///<  полноэкранные размеры

  HALF_FULLSCREEN,	    ///<    ширина и высота на пол экрана
  THIRD_FULLSCREEN,     ///<    ширина и высота на треть экрана
  FOURTH_FULLSCREEN,    ///<	 ширина и высота на четверть экрана

  _64X64,      ///<   64 x 64
  _256X256,	   ///<	  256 x 256
  _512X512,	   ///<   512 x 512
  _1024X1024   ///<   1024 x 1024
};


/** \brief Вычисление требуемого размера поверхности рендертаргета. 
  Вернёт E_FAIL если переданы некорректные аргументы  */
GB_D3D9_RT_API ComputeNeedRtSize(
				gb_out UINT& nOutWidth, 
				gb_out UINT& nOutHeight, 
				const RenderTargeteSize_e eSize, 
				const UINT nScreenWidth, 
				const UINT nScreenHeight  
								);


/** \brief Создать интерфейсы поверхности   */
GB_D3D9_RT_API CreateRenderTargetInterfaces(
				gb_out IDirect3DSurface9** ppOutISrf,
				gb_out IDirect3DTexture9** ppOutITxtr, 
				IDirect3DDevice9* pdevice, 
				const UINT nWidth, 
				const UINT nHeight, 
				const D3DFORMAT frmt 
									   );

/** \brief Утсановить  девайс для рендертаргетов УДАЛИТЬ */
GB_D3D9_RT_API RenderTargetSetDevice(IDirect3DDevice9* pdevice);

/** \brief Установить структуру буфера отрисовки  (бэкбуфера) УДАЛИТЬ  */
GB_D3D9_RT_API SetBackBufSurfDescr(const D3DSURFACE_DESC* descr);

/** \brief Установить указатель на поверхность буфера отрисовки  (бэкбуфера) */
GB_D3D9_RT_API SetBackBufFrameDrawIntrfPtr(IDirect3DSurface9* psurf);

/** \brief Установить Пометить все рендертаргеты в пуле как неиспользуемые   */
GB_D3D9_RT_API SetUnUsedAll();

/** \brief Вычисление общего среднего цвета поверхности  */
GB_D3D9_RT_API ComputeAverSurfaceColor(
			gb_out gb::color::Color4f* pOut, 
			gb_inout_opt IDirect3DSurface9* surf,
			gb_in_opt gb::fmath::geom2d::Rectangle* rect);

GB_D3D9_RT_API ComputeSurfacePixelColor(
			gb_out gb::color::Color4f* pColorOut, 
			gb_in POINT& pntCoord, 
			gb_inout_opt IDirect3DSurface9* pSrf
	);


 

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
 
 
};
// end class

 
/** \brief Получить свободную для отрисовки поверхность */
GB_D3D9_RT_API GetUnusedRenderTarget(gb_out IRenderTarget** ppOut, 
									 const RenderTargeteSize_e eSize);

GB_D3D9_RT_API GetUnusedRenderTarget(gb_out IRenderTarget** ppOut, 
									 const UINT nWidth, const UINT nHeight);





} 
// end namespace
} 
// end namespace
} 
// end namespace
} 
// end namespace


#endif // #if ( defined(WIN32) && defined(GB_D3D9) )
// end file