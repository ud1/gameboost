/** \file  DAPLIB_RTarget_impl.h
 \brief  реализация интерфейса рендертаргет 

 \todo переименовать класс DAPLIB_RTarget в RenderTarget
  \todo убрать MONPRINTB

*/

#if ( defined(WIN32) && defined(GB_D3D9) )

#pragma once

#include <gb/Config.h>
#include <gb/macro.h>

////#include "dapplLibr_rendertarget.h"
#include <gb/graphics/d3d9/rt/rendertarget.h>

//! УБРАТЬ !!!!!!!!!!!
#define MONPRINTB(m)


//* \brief  реализация рендертаргетов
class RenderTarget  : public IRenderTarget {
public:
   	
	const UINT m_width;
	const UINT m_height;


	/** \brief В конструкторе передать требуемую ширину и высоту. 
	 \param width - [in] требуемая ширина. Если ноль, то будет использован размер заднего буфера.
	 \param height - [in] требуемая высота. Если ноль, то будет использован размер заднего буфера. 
	 \param pdevice - [in] девайс.
	 \param format - [in]  Формат поверхнсти. Если D3DFMT_UNKNOWN, 
	            то будет использован формат заднего буфера. 	*/
	RenderTarget(const UINT nWidth, const UINT nHeight, IDirect3DDevice9* pdevice, _out HRESULT& hr) 
		:  m_width(nWidth), m_height(nHeight), m_pdevice(pdevice)     
		//  IDAPLIB_RenderTarget(  nWidth,   nHeight)
		{
		   hr = CreateInterfeces(  pdevice);

		    if FAILED(hr) {
			throw std::runtime_error("Error create interfaces \n");
			return;
			};
 
		};

	virtual ~RenderTarget() {
	   m_bUsed=true; ReleaseInterfaces(); 
	};

	

	virtual UINT GetWidth()  const { return m_width; };
	virtual UINT GetHeight() const { return m_height; };

	virtual IDirect3DTexture9*  GetITexture() const { return  m_pITexture; };
	virtual IDirect3DSurface9* GetISurface() const { return  m_pISurface; };
	virtual D3DFORMAT GetFormat() const { return m_format; };

	virtual void  SetUsed(bool bUsed) const { m_bUsed = bUsed; };
	virtual bool IsUsed() const { return m_bUsed; };

	virtual bool IsSameInterfaces(const IRenderTarget* prt) const 
	{
	     return ( (m_pITexture == prt->GetITexture() ) && (m_pISurface == prt->GetISurface() ) );
	};

	virtual HRESULT MakeAsCurrentRender()  const ;
	virtual HRESULT MakeRenderToBackBuffer()  const ;

	virtual HRESULT  CheckCreateInterfaces() const ;

	virtual HRESULT  FillSurfaceColor(const D3DCOLOR color) const;
	virtual HRESULT  FillSurfaceColor(const D3DCOLORVALUE& color) const;

	virtual HRESULT  StretchFrom(const IRenderTarget* rtarget, const D3DTEXTUREFILTERTYPE ft=D3DTEXF_LINEAR) const;
    virtual HRESULT  StretchFrom(IDirect3DSurface9* pISurface, const D3DTEXTUREFILTERTYPE ft=D3DTEXF_LINEAR ) const;

	virtual HRESULT  StretchTo(const IRenderTarget* rtarget, const D3DTEXTUREFILTERTYPE ft=D3DTEXF_LINEAR ) const;
	virtual HRESULT  StretchTo(IDirect3DSurface9* pISurface, const D3DTEXTUREFILTERTYPE ft=D3DTEXF_LINEAR ) const;

    virtual HRESULT  ValidateInterfaces() const;
	
	//-------------------------------------

	virtual HRESULT  CreateInterfeces(IDirect3DDevice9* pdevice) {
		 HRESULT hr =0;
 
	   hr |=  DAPLIB_RT_CreateInterfaces( &m_pISurface, &m_pITexture,   pdevice, 
			  m_width, m_height,
			  GetFormat()
			 );

	   if FAILED(hr) {
		   static const char* ERR_STR = "Error create interfaces";
		   MONPRINTB(ERR_STR);
		  // throw std::runtime_error( ERR_STR );
		  return hr; 
		   };
 
		 return hr;
	};

	virtual HRESULT ReleaseInterfaces() const { 
		HRESULT hr=0;
		    GB_SAFE_EXC_RELEASE(m_pISurface);   
		    GB_SAFE_EXC_RELEASE(m_pITexture); 
		return hr; 
	};


	static RenderTarget* UnSafeCreateNewInstance(const UINT w, const UINT h, IDirect3DDevice9* pdevice, _out HRESULT& hr)   {
	   	 RenderTarget* pres = NULL;
	    pres = new	RenderTarget(w, h, pdevice, hr);


		
		return pres;
	};

protected:

	mutable IDirect3DTexture9*   m_pITexture;  ///< Поверхность в виде текстурного интерфейса 
	mutable IDirect3DSurface9*  m_pISurface;   ///<  Собственно сам интерфейс поверхности 

	  D3DFORMAT m_format;	///< Формат. Если D3DFMT_UNKNOWN то будет формат заднего буфера.

	mutable bool m_bUsed; ///< используется ли в настоящий момент для отрисовки
	IDirect3DDevice9* m_pdevice;

	
};
// end class



#endif   // #if ( defined(WIN32) && defined(GB_D3D9) )
// end file