/** \file   RenderCubemapEnvironment.cpp
  \brief реализация интерфейса 

*/

#include "stdafx.h"
//#include "pch.h"

#if ( defined(WIN32) && defined(GB_D3D9) )

#include <gb/graphics/d3d9/render/render.h>

#include <gb/graphics/d3d9/d3d9.h>

#ifndef GB_MATH
   #error  gb::math пока нужен.  Должен быть определён GB_MATH
#else
   #include <gb/math/math.h>
#endif
 
#include <gb/base/Constants.h>


#pragma  warning(push)
#pragma  warning(disable : 4297)

namespace gb
{
	namespace graphics 
	{
		namespace d3d9 
		{
			namespace render 
			{


				//=========================================================================


				struct MARK_CPP_BEGIN {};

#include <gb/graphics/d3d9/draw.h>
#include <gb/macro.h>

				using namespace gb::graphics::d3d9;


				// Parameters:
				//
				//   float4x4 matViewInverse;
				//   float4x4 matViewProj;
				//   float4x4 matWorld;
				//
				//
				// Registers:
				//
				//   Name           Reg   Size
				//   -------------- ----- ----
				//   matWorld       c0       4
				//   matViewInverse c4       4
				//   matViewProj    c8       4
				//

				static DWORD* __getVertexShaderData()
				{
					static const BYTE data[] =
					{
						1,   2, 254, 255, 254, 255, 
						67,   0,  67,  84,  65,  66, 
						28,   0,   0,   0, 215,   0, 
						0,   0,   1,   2, 254, 255, 
						3,   0,   0,   0,  28,   0, 
						0,   0,   0,   1,   0,   0, 
						208,   0,   0,   0,  88,   0, 
						0,   0,   2,   0,   4,   0, 
						4,   0,   0,   0, 104,   0, 
						0,   0,   0,   0,   0,   0, 
						120,   0,   0,   0,   2,   0, 
						8,   0,   4,   0,   0,   0, 
						104,   0,   0,   0,   0,   0, 
						0,   0, 132,   0,   0,   0, 
						2,   0,   0,   0,   4,   0, 
						0,   0, 104,   0,   0,   0, 
						144,   0,   0,   0, 109,  97, 
						116,  86, 105, 101, 119,  73, 
						110, 118, 101, 114, 115, 101, 
						0, 171,   3,   0,   3,   0, 
						4,   0,   4,   0,   1,   0, 
						0,   0,   0,   0,   0,   0, 
						109,  97, 116,  86, 105, 101, 
						119,  80, 114, 111, 106,   0, 
						109,  97, 116,  87, 111, 114, 
						108, 100,   0, 171, 171, 171, 
						0,   0, 128,  63,   0,   0, 
						0,   0,   0,   0,   0,   0, 
						0,   0,   0,   0,   0,   0, 
						0,   0,   0,   0, 128,  63, 
						0,   0,   0,   0,   0,   0, 
						0,   0,   0,   0,   0,   0, 
						0,   0,   0,   0,   0,   0, 
						128,  63,   0,   0,   0,   0, 
						0,   0,   0,   0,   0,   0, 
						0,   0,   0,   0,   0,   0, 
						0,   0, 128,  63, 118, 115, 
						95,  50,  95,  97,   0,  77, 
						105,  99, 114, 111, 115, 111, 
						102, 116,  32,  40,  82,  41, 
						32,  72,  76,  83,  76,  32, 
						83, 104,  97, 100, 101, 114, 
						32,  67, 111, 109, 112, 105, 
						108, 101, 114,  32,  57,  46, 
						50,  55,  46,  57,  53,  50, 
						46,  51,  48,  50,  50,   0, 
						31,   0,   0,   2,   0,   0, 
						0, 128,   0,   0,  15, 144, 
						1,   0,   0,   2,   0,   0, 
						15, 128,   9,   0, 228, 160, 
						5,   0,   0,   3,   1,   0, 
						15, 128,   0,   0, 228, 128, 
						1,   0,  85, 160,   1,   0, 
						0,   2,   2,   0,  15, 128, 
						8,   0, 228, 160,   4,   0, 
						0,   4,   1,   0,  15, 128, 
						2,   0, 228, 128,   1,   0, 
						0, 160,   1,   0, 228, 128, 
						1,   0,   0,   2,   3,   0, 
						15, 128,  10,   0, 228, 160, 
						4,   0,   0,   4,   1,   0, 
						15, 128,   3,   0, 228, 128, 
						1,   0, 170, 160,   1,   0, 
						228, 128,   1,   0,   0,   2, 
						4,   0,  15, 128,  11,   0, 
						228, 160,   4,   0,   0,   4, 
						1,   0,  15, 128,   4,   0, 
						228, 128,   1,   0, 255, 160, 
						1,   0, 228, 128,   5,   0, 
						0,   3,   1,   0,  15, 128, 
						1,   0, 228, 128,   0,   0, 
						85, 144,   5,   0,   0,   3, 
						5,   0,  15, 128,   0,   0, 
						228, 128,   0,   0,  85, 160, 
						4,   0,   0,   4,   5,   0, 
						15, 128,   2,   0, 228, 128, 
						0,   0,   0, 160,   5,   0, 
						228, 128,   4,   0,   0,   4, 
						5,   0,  15, 128,   3,   0, 
						228, 128,   0,   0, 170, 160, 
						5,   0, 228, 128,   4,   0, 
						0,   4,   5,   0,  15, 128, 
						4,   0, 228, 128,   0,   0, 
						255, 160,   5,   0, 228, 128, 
						4,   0,   0,   4,   1,   0, 
						15, 128,   5,   0, 228, 128, 
						0,   0,   0, 144,   1,   0, 
						228, 128,   5,   0,   0,   3, 
						0,   0,  15, 128,   0,   0, 
						228, 128,   2,   0,  85, 160, 
						4,   0,   0,   4,   0,   0, 
						15, 128,   2,   0, 228, 128, 
						2,   0,   0, 160,   0,   0, 
						228, 128,   4,   0,   0,   4, 
						0,   0,  15, 128,   3,   0, 
						228, 128,   2,   0, 170, 160, 
						0,   0, 228, 128,   4,   0, 
						0,   4,   0,   0,  15, 128, 
						4,   0, 228, 128,   2,   0, 
						255, 160,   0,   0, 228, 128, 
						4,   0,   0,   4,   0,   0, 
						15, 128,   0,   0, 228, 128, 
						0,   0, 170, 144,   1,   0, 
						228, 128,   1,   0,   0,   2, 
						1,   0,   7, 128,   3,   0, 
						228, 160,   2,   0,   0,   3, 
						1,   0,   7, 128,   1,   0, 
						228, 128,   7,   0, 228, 160, 
						5,   0,   0,   3,   2,   0, 
						15, 128,   1,   0,  85, 128, 
						9,   0, 228, 160,   4,   0, 
						0,   4,   2,   0,  15, 128, 
						8,   0, 228, 160,   1,   0, 
						0, 128,   2,   0, 228, 128, 
						4,   0,   0,   4,   1,   0, 
						15, 128,  10,   0, 228, 160, 
						1,   0, 170, 128,   2,   0, 
						228, 128,   4,   0,   0,   4, 
						1,   0,  15, 128,   4,   0, 
						228, 128,   3,   0, 255, 160, 
						1,   0, 228, 128,   4,   0, 
						0,   4,   0,   0,  15, 192, 
						1,   0, 228, 128,   0,   0, 
						255, 144,   0,   0, 228, 128, 
						1,   0,   0,   2,   0,   0, 
						7, 224,   0,   0, 201, 144, 
						255, 255,   0,   0
					};


					return (DWORD*) data;
				}


				// Parameters:
				//
				//   float4 colorCube;
				//   float envirBri;
				//   samplerCUBE skyBox;
				//
				//
				// Registers:
				//
				//   Name         Reg   Size
				//   ------------ ----- ----
				//   envirBri     c0       1
				//   colorCube    c1       1
				//   skyBox       s0       1
				//

				static DWORD* __getPixelShaderData()
				{
					static const BYTE  data[] =
					{
						0,   2, 255, 255, 254, 255, 
						65,   0,  67,  84,  65,  66, 
						28,   0,   0,   0, 207,   0, 
						0,   0,   0,   2, 255, 255, 
						3,   0,   0,   0,  28,   0, 
						0,   0,   0,   1,   0,   0, 
						200,   0,   0,   0,  88,   0, 
						0,   0,   2,   0,   1,   0, 
						1,   0,   0,   0, 100,   0, 
						0,   0, 116,   0,   0,   0, 
						132,   0,   0,   0,   2,   0, 
						0,   0,   1,   0,   0,   0, 
						144,   0,   0,   0, 160,   0, 
						0,   0, 176,   0,   0,   0, 
						3,   0,   0,   0,   1,   0, 
						0,   0, 184,   0,   0,   0, 
						0,   0,   0,   0,  99, 111, 
						108, 111, 114,  67, 117,  98, 
						101,   0, 171, 171,   1,   0, 
						3,   0,   1,   0,   4,   0, 
						1,   0,   0,   0,   0,   0, 
						0,   0, 143, 194, 117,  63, 
						51,  51, 115,  63,   0,   0, 
						128,  63,   0,   0, 128,  63, 
						101, 110, 118, 105, 114,  66, 
						114, 105,   0, 171, 171, 171, 
						0,   0,   3,   0,   1,   0, 
						1,   0,   1,   0,   0,   0, 
						0,   0,   0,   0,  20, 174, 
						135,  63,   0,   0,   0,   0, 
						0,   0,   0,   0,   0,   0, 
						0,   0, 115, 107, 121,  66, 
						111, 120,   0, 171,   4,   0, 
						14,   0,   1,   0,   1,   0, 
						1,   0,   0,   0,   0,   0, 
						0,   0, 112, 115,  95,  50, 
						95,  48,   0,  77, 105,  99, 
						114, 111, 115, 111, 102, 116, 
						32,  40,  82,  41,  32,  72, 
						76,  83,  76,  32,  83, 104, 
						97, 100, 101, 114,  32,  67, 
						111, 109, 112, 105, 108, 101, 
						114,  32,  57,  46,  50,  55, 
						46,  57,  53,  50,  46,  51, 
						48,  50,  50,   0,  31,   0, 
						0,   2,   0,   0,   0, 128, 
						0,   0,   7, 176,  31,   0, 
						0,   2,   0,   0,   0, 152, 
						0,   8,  15, 160,  66,   0, 
						0,   3,   0,   0,  15, 128, 
						0,   0, 228, 176,   0,   8, 
						228, 160,   5,   0,   0,   3, 
						0,   0,  15, 128,   0,   0, 
						228, 128,   1,   0, 228, 160, 
						5,   0,   0,   3,   0,   0, 
						15, 128,   0,   0, 228, 128, 
						0,   0,   0, 160,   1,   0, 
						0,   2,   0,   8,  15, 128, 
						0,   0, 228, 128, 255, 255, 
						0,   0
					};


					return (DWORD*) data;
				}



				//! implementation
				class RenderEnvImpl : public  IRenderCubemapEnvironment {
				public:
					IDirect3DDevice9* m_pdevice;
					IDirect3DVertexShader9* m_pIVsh;
					IDirect3DPixelShader9*  m_pIPsh;


					class InternalData {
					public:
						InternalData(IDirect3DDevice9* pdevice) 
						{


						}


					};

					class OldData {
					public:
						IDirect3DVertexShader9* pvsh;
						IDirect3DPixelShader9*  ppsh;

						OldData()
						{
							pvsh = NULL;
							ppsh = NULL;
						};
					};

					RenderEnvImpl(IDirect3DDevice9*  pdevice, HRESULT* pOuthr ) throw() 
					{

						*pOuthr = S_OK;
						m_pIVsh = NULL;
						m_pIPsh = NULL;
						m_pdevice = pdevice;
						if (!m_pdevice)
						{
							throw (std::runtime_error("invalid arg") );
						}

						*pOuthr |= m_pdevice->CreateVertexShader( __getVertexShaderData(), &m_pIVsh );
						if FAILED(*pOuthr)
						{
							throw (std::runtime_error("failed create vertex shader") );
						}
						*pOuthr |= m_pdevice->CreatePixelShader(  __getPixelShaderData(), &m_pIPsh );
						if FAILED(*pOuthr)
						{
							throw (std::runtime_error("failed create pixel shader") );
						}





					}
					virtual ~RenderEnvImpl() 
					{
						if(m_pIVsh)
						{
							m_pIVsh->Release();
							m_pIVsh = NULL;
						}
						if(m_pIPsh)
						{
							m_pIPsh->Release();
							m_pIPsh = NULL;
						}

					}



					HRESULT setShadersConstants()
					{
						HRESULT hr = S_OK;





						return hr;
					}


					//================================================================
					virtual HRESULT RenderEnvironment(
						IDirect3DDevice9* pd3device,
						const float* matrix4x4_ViewProj,
						const float* matrix4x4_InverseView,
						IDirect3DCubeTexture9* pTexture,
						const RenderEnvirOptions& opt ) const  
					{
						HRESULT hr =S_OK;


						// get old data
						IDirect3DBaseTexture9* pOldTxtr = NULL;
						hr |= pd3device->GetTexture(0, &pOldTxtr);

						IDirect3DVertexShader9* pOldVsh = NULL; 
						hr |= pd3device->GetVertexShader(&pOldVsh);
						IDirect3DPixelShader9*  pOldPsh = NULL;
						hr |= pd3device->GetPixelShader(&pOldPsh);

						DWORD dwOldCullMode = 0;
						hr |= pd3device->GetRenderState(D3DRS_CULLMODE, &dwOldCullMode);

						DWORD dwOldZEnable = 0;
						hr |= pd3device->GetRenderState(D3DRS_ZENABLE , &dwOldZEnable);

						DWORD dwOldZWriteEnable = 0;
						hr |= pd3device->GetRenderState(D3DRS_ZWRITEENABLE , &dwOldZWriteEnable);




						// set shaders
						hr |= pd3device->SetVertexShader( m_pIVsh);


						// set const vertex shader
						//

						mat44_s mWorld (1.0f);
						if( (opt.yaw!=0.0f) || (opt.pitch!=0.0f) || (opt.roll!=0.0f) )
						{
							mWorld.setRotationYawPitchRoll( opt.yaw, opt.pitch, opt.roll );
						}

						//   Name           Reg   Size
						//   -------------- ----- ----
						//   matWorld       c0       4	   float4x4 matWorld;
						//   matViewInverse c4       4	   float4x4 matViewInverse;
						//   matViewProj    c8       4	   float4x4 matViewProj;

						bool transp =  false; //true;

						if(transp)
						{
							mWorld.transpone();
							hr |= pd3device->SetVertexShaderConstantF(0, mWorld, 4 );
						}
						else
						{
							hr |= pd3device->SetVertexShaderConstantF(0, mWorld, 4 );
						}


						if(transp)
						{
							mat44_s mInvViewTransp (matrix4x4_InverseView);
							mInvViewTransp.transpone();
							hr |= pd3device->SetVertexShaderConstantF(4, mInvViewTransp, 4 );
						}
						else
						{
							hr |= pd3device->SetVertexShaderConstantF(4, matrix4x4_InverseView, 4 );
						}

						if( transp )
						{
							mat44_s mViewProjTransp (matrix4x4_ViewProj);
							mViewProjTransp.transpone();
							hr |= pd3device->SetVertexShaderConstantF(8, mViewProjTransp, 4 );

						}
						else
						{
							hr |= pd3device->SetVertexShaderConstantF(8, matrix4x4_ViewProj, 4 );
						}


						//
						// end



						//--------------------------------------------------

						hr |= pd3device->SetPixelShader(m_pIPsh);

						// set const pixel shader
						//

						//   Name         Reg   Size
						//   ------------ ----- ----
						//   envirBri     c0       1   float envirBri;
						//   colorCube    c1       1   float4 colorCube;
						//   skyBox       s0       1   samplerCUBE skyBox;
						float farray[4];
						farray[0] = farray[1] = farray[2] = farray[3] = 1.0f;
						farray[0] = opt.brightnes;
						hr |= pd3device->SetPixelShaderConstantF(0, farray, 1);
						hr |= pd3device->SetPixelShaderConstantF(1,  &opt.color.r, 1);

						// set texture
						hr |= pd3device->SetTexture(0, pTexture);

						//
						// end

						//--------------------------------------------------



						// set render state
						hr |= pd3device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
						hr |= pd3device->SetRenderState(D3DRS_ZENABLE ,  0);
						hr |= pd3device->SetRenderState(D3DRS_ZWRITEENABLE ,  0 );


						// draw

						hr |=  draw::drawMeshPrimitiveCube1x1Mem(pd3device);


						// set old data
						//if(pOldVsh)
						//{
						hr |= pd3device->SetVertexShader(pOldVsh);
						//}

						//if(pOldPsh)
						//{
						hr |= pd3device->SetPixelShader(pOldPsh);
						//}

						hr |= pd3device->SetRenderState(D3DRS_CULLMODE, dwOldCullMode);

						//if(pOldTxtr)
						//{
						hr |= pd3device->SetTexture(0, pOldTxtr);
						//}


						// release old data
						GB_SAFE_REL(pOldTxtr)
							GB_SAFE_REL(pOldVsh)
							GB_SAFE_REL(pOldPsh)


							return hr;
					};


					OldData  m_OldData;

				};


	//=========================================================================
	GB_D3D9_API HRESULT CreateInterfaceCubemapRender(IRenderCubemapEnvironment** ppOut,
		IDirect3DDevice9* pd3device)
	{
		HRESULT hr = S_OK;


		*ppOut = NULL;

		try {
			*ppOut = (IRenderCubemapEnvironment*) new RenderEnvImpl(pd3device, &hr);
		}
		catch(...)
		{
			// error create
			return hr;
		}


		return hr;
	};


 //=====================================================================

}
// end namespace

}
// end namespace

}
// end namespace

}
// end namespace

#pragma  warning( pop )

#endif // #if ( defined(WIN32) && defined(GB_D3D9) ) 
// end file