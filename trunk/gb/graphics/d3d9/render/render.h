/** \file 
 \brief  Вспомогательные классы , типы для отрисовки объкетов. 



  \author ksacvet777

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