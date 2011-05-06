/** \file 
 \brief  ��������������� ������ , ���� ��� ��������� ��������. 



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

   //! \brief   ��������������� ������ , ���� ��� ��������� ��������. 
   namespace render 
   {

   //---------------------------------------------------------------------

				//! \brief ��������� ��������� ����������� ���������.
				class IRenderCubemapEnvironment {
				public:

					//! \brief ����� ��������� ���������� ���������
					class RenderEnvirOptions {
					public:

						float brightnes;  ///< ������� ��������

						float yaw;	 // ���� ��������
						float pitch;
						float roll;

						D3DCOLORVALUE color;  ///< ���� ��������

						//! \brief ����������� ������ �� ���������.
						RenderEnvirOptions() 
						{
							brightnes = 1.0f;
							yaw = pitch = roll = 0.0f;
							color.r=color.b=color.g=color.a=1.0f;

						}
					};

					virtual ~IRenderCubemapEnvironment() {}

					//! \brief ���������� ���������.
					virtual HRESULT RenderEnvironment(
						IDirect3DDevice9* pd3device,
						const float* matrix4x4_ViewProj,
						const float* matrix4x4_InverseView,
						IDirect3DCubeTexture9* pTexture,
						const RenderEnvirOptions& opt    ) const   = 0;


				};


				//! \brief ������� ��������� ��������� ����������� ���������.
				GB_D3D9_API HRESULT CreateInterfaceCubemapRender(
					IRenderCubemapEnvironment** ppOut, 
					IDirect3DDevice9* pd3device);



 //---------------------------------------------------------------------

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