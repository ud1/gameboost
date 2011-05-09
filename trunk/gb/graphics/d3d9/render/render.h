/** \file 
 \brief  Вспомогательные классы , типы для отрисовки объкетов. 



  \author ksacvet777

  \todo для билбоардов и спрайтов добавить методы множественной отрисовки.
  \todo для RenderBitmapFont.cpp  сделать расширеное детектирование глюков в отладке.

*/

#if ( defined(WIN32) && defined(GB_D3D9) )

#pragma once

#include <d3d9.h>


// temp
#define GB_D3D9_API

namespace gb
{
 namespace graphics 
 {
  namespace d3d9 
  {

   //! \brief   Вспомогательные классы , типы для отрисовки объкетов. 
   namespace render 
   {


   //---------------------------------------------------------------------

				//! \brief Интерфейс отрисовки кубического окружения.
				class IRenderCubemapEnvironment {
				public:

					//! \brief Опции отрисовки кубческого окружения
					class RenderEnvirOptions {
					public:

						float brightnes;  ///< яркость текстуры

						float yaw;	 // углы поворота
						float pitch;
						float roll;

						D3DCOLORVALUE color;  ///< цвет текстуры

						//! \brief Конструктор ставит по умолчанию.
						RenderEnvirOptions() 
						{
							brightnes = 1.0f;
							yaw = pitch = roll = 0.0f;
							color.r=color.b=color.g=color.a=1.0f;

						}
					};

					virtual ~IRenderCubemapEnvironment() {}

					//! \brief Нарисовать окружение.
					virtual HRESULT RenderEnvironment(
						IDirect3DDevice9* pd3device,
						const float* matrix4x4_ViewProj,
						const float* matrix4x4_InverseView,
						IDirect3DCubeTexture9* pTexture,
						const RenderEnvirOptions& opt    ) const   = 0;


				};


				//! \brief Создать интерфейс отрисовки кубического окружения.
				GB_D3D9_API HRESULT CreateInterfaceCubemapRender(
					IRenderCubemapEnvironment** ppOut, 
					IDirect3DDevice9* pd3device);



 //---------------------------------------------------------------------


				/**   \brief  Интерфейс отрисовки билбоардов. Цвет , поворот и т.д.  */
				class IRenderBillboard {
				public:		 
					virtual ~IRenderBillboard() {}



					//! \brief Опции отрисовки билбоарда
					class RenderBillbOptions {
					public:
						float fRotationAngle;
						D3DCOLORVALUE color;
						D3DVECTOR position;
						float size;


						//! \brief Конструктор заполняет значениями по умолчанию
						RenderBillbOptions()
						{
							fRotationAngle = 0.0f;
							color.r = color.g = color.b = color.a = 1.0f;
							position.x = position.y = position.z = 0.0f;
							size = 1.0f;
						}
					};

					//! \brief Флаги для функции рендер. 
					class FlagData {
					public:
						bool enableStrAlphaBlending; //< включать или нет альфасмешивание по стандартной схеме.
						bool needRestoreOldStates; //< надо ли восстанавливать старые стейты девайса.

						//! \brief   Конструктор заполняет по умолчанию.
						FlagData()
						{
							enableStrAlphaBlending = false;
							needRestoreOldStates = true;
						}
					};


					//! \brief Отрисовать одиночный билбоард.
					virtual HRESULT Render(IDirect3DDevice9* pdevice,
						IDirect3DTexture9* pTexture,
						const float* matrix4x4_View,  
						const float* matrix4x4_WorldViewProj,  
						const RenderBillbOptions& opt,
						const FlagData& flag ) const = 0;


				};
 
//! \brief  Создать интерфейс вывода билбоардов.
GB_D3D9_API HRESULT  CreateRenderBillboardInterface (IRenderBillboard** ppOut,
													 IDirect3DDevice9* pdevice);





class IRenderBitmapFont {
public:

	//! \brief  описание для отрисовки символа
	struct CharDescr {
		POINT offset;	  //< отступ меж символам  //  (x-меж символов в строке, y-меж строками).
		RECT  recTexture; //< расположение символа на текстуре.
		int advance;
	};


	//! \brief Таблица  для всех символов ASCII (0-255).
	struct CharDescrTableAnsi 
	{
		CharDescr table [256];
	};


	//! \brief  Опции отрисовки.
	class DrawOptions {
	public:
		int nSymbolsWidth;
		int nSymbolHeight;
		int nBetweenSymbols;
		int nBetweenLines;

		//! \brief Конструктор заливает всё по умолчанию.
		DrawOptions()
		{
   		  nSymbolsWidth = 12;
		  nSymbolHeight = 12;
		  nBetweenSymbols = 0;
		  nBetweenLines   = 0;

		}
	};


	//! \brief  Опции создания шрифта.
	class CreateRenderBitmapFontOptions  {
	public:
 
		    CreateRenderBitmapFontOptions() { }
	};

	virtual ~IRenderBitmapFont() {}



	virtual HRESULT DrawStr(int x, int y, const char* str ) const =0;

	virtual const DrawOptions& getDrawOptions() const =0;
	virtual void  setDrawOptions(const DrawOptions& opt)  =0;


};


 
/** \brief  Создать интерфейс вывода текстурного шрифта.  <br> */
GB_D3D9_API HRESULT  CreateRenderBitmapFontInterface(
				IRenderBitmapFont** ppOut,  
				IDirect3DDevice9* pdevice,	
				IDirect3DTexture9* pBitmapTexture, //<	текстура  шрифта.
				const IRenderBitmapFont::CharDescrTableAnsi& table //< заранее созданая таблица символов
	);


GB_D3D9_API HRESULT  CreateRenderBitmapFontInterfaceFromXmlFileA(
	IRenderBitmapFont** ppOut,  
	IDirect3DDevice9* pdevice,	
	IDirect3DTexture9* pBitmapTexture, //<	текстура  шрифта.
	const char* sXmlFileFontDescr //<  XML файл с описанием шрифта. По программе Font Builder .
	);








//------------------------------------------------------------------------


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