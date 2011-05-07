﻿

#if ( defined(WIN32) && defined(GB_D3D9) )

#include <gb/graphics/d3d9/render/render.h>
#include <gb/macro.h>
#include <gb/graphics/d3d9/d3d9.h>

using namespace gb::graphics::d3d9::render;


 
//#include <gb/graphics/d3d9/Device.h>
 
 
  //-------------------------------------

  class RenderBillboardImpl : public IRenderBillboard {
  public:

	  RenderBillboardImpl(IDirect3DDevice9* pdevice, HRESULT* phrOut ) ;

	  virtual ~RenderBillboardImpl()
	  {
		 GB_SAFE_REL(m_pPsh);
		 GB_SAFE_REL(m_pVsh);


	  }


 	virtual HRESULT Render(IDirect3DDevice9* pdevice,
		IDirect3DTexture9* pTexture,
		const float* matrix4x4_View,  
		const float* matrix4x4_WorldViewProj,  
		const RenderBillbOptions& opt,
		const FlagData& flag  ) const ;



  public:

	  IDirect3DVertexShader9* m_pVsh;
	  IDirect3DPixelShader9* m_pPsh;


	  //! \brief  Данные для восстановления 
	struct RestoreData 
	{
	  DWORD dwOldCullMode;
	  DWORD dwD3DRS_ALPHABLENDENABLE;
	  DWORD dwD3DRS_SRCBLEND;
	  DWORD dwD3DRS_DESTBLEND;

	};

	//HRESULT hr =  dvc->SetRenderState(D3DRS_ALPHABLENDENABLE,1);
	//hr |=         dvc->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	//hr |=         dvc->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA); 


mutable	RestoreData m_RestoreData;

  };
  // end class



 

	  struct MARK_BEGIN_VS {};
 
	  //
	  // Generated by Microsoft (R) HLSL Shader Compiler 9.27.952.3022
	  //
	  //   fxc /nologo /Fh billiboard_HObj.txt /T vs_2_a /E vs_main
	  //    C:\TEMP\z_test_compile_eff\billiboard.fx
	  //
	  //
	  // Parameters:
	  //
	  //   float ang;
	  //   float4x4 mView;
	  //   float4x4 mWorldViewProj;
	  //   float4 posit;
	  //   float size;
	  //
	  //
	  // Registers:
	  //
	  //   Name           Reg   Size
	  //   -------------- ----- ----
	  //   mWorldViewProj c0       4
	  //   mView          c4       3
	  //   ang            c7       1
	  //   posit          c8       1
	  //   size           c9       1
	  //

	  /*
	  vs_2_x
		  def c12, 0.159154937, 0.5, 6.28318548, -3.14159274
		  def c10, -1.55009923e-006, -2.17013894e-005, 0.00260416674, 0.00026041668
		  def c11, -0.020833334, -0.125, 1, 0.5
		  dcl_position v0
		  dcl_texcoord v1
		  mov r0.xy, c12
		  mad r0.x, c7.x, r0.x, r0.y
		  frc r0.x, r0.x
		  mad r0.x, r0.x, c12.z, c12.w
		  sincos r1.xy, r0.x, c10, c11
		  mul r0.xyz, r1.xyxw, v0.xxyw
		  mad r0.x, -r1.y, v0.y, r0.x
		  add r0.y, r0.z, r0.y
		  mul r1.x, r0.x, c4.x
		  mul r1.y, r0.x, c5.x
		  mul r1.z, r0.x, c6.x
		  mul r2.x, r0.y, c4.y
		  mul r2.y, r0.y, c5.y
		  mul r2.z, r0.y, c6.y
		  add r0.xyz, r1, r2
		  mov r1.x, c9.x
		  mad r0.xyz, r1.x, r0, c8
		  mul r1, r0.y, c1
		  mad r1, c0, r0.x, r1
		  mad r0, c2, r0.z, r1
		  add oPos, r0, c3
		  mov oT0.xy, v1
	   */
		  // approximately 29 instruction slots used
 

	   static  const BYTE  g_vs_data[] =
	  {
		  1,   2, 254, 255, 254, 255, 
		  82,   0,  67,  84,  65,  66, 
		  28,   0,   0,   0,  19,   1, 
		  0,   0,   1,   2, 254, 255, 
		  5,   0,   0,   0,  28,   0, 
		  0,   0,   0,   1,   0,   0, 
		  12,   1,   0,   0, 128,   0, 
		  0,   0,   2,   0,   7,   0, 
		  1,   0,   0,   0, 132,   0, 
		  0,   0, 148,   0,   0,   0, 
		  164,   0,   0,   0,   2,   0, 
		  4,   0,   3,   0,   0,   0, 
		  172,   0,   0,   0,   0,   0, 
		  0,   0, 188,   0,   0,   0, 
		  2,   0,   0,   0,   4,   0, 
		  0,   0, 172,   0,   0,   0, 
		  0,   0,   0,   0, 203,   0, 
		  0,   0,   2,   0,   8,   0, 
		  1,   0,   0,   0, 212,   0, 
		  0,   0, 228,   0,   0,   0, 
		  244,   0,   0,   0,   2,   0, 
		  9,   0,   1,   0,   0,   0, 
		  132,   0,   0,   0, 252,   0, 
		  0,   0,  97, 110, 103,   0, 
		  0,   0,   3,   0,   1,   0, 
		  1,   0,   1,   0,   0,   0, 
		  0,   0,   0,   0, 123,  20, 
		  174, 190,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0, 
		  0,   0, 109,  86, 105, 101, 
		  119,   0, 171, 171,   3,   0, 
		  3,   0,   4,   0,   4,   0, 
		  1,   0,   0,   0,   0,   0, 
		  0,   0, 109,  87, 111, 114, 
		  108, 100,  86, 105, 101, 119, 
		  80, 114, 111, 106,   0, 112, 
		  111, 115, 105, 116,   0, 171, 
		  171, 171,   1,   0,   3,   0, 
		  1,   0,   4,   0,   1,   0, 
		  0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0, 
		  0,   0, 128,  63, 115, 105, 
		  122, 101,   0, 171, 171, 171, 
		  205, 204,  76,  63,   0,   0, 
		  0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0, 118, 115, 
		  95,  50,  95,  97,   0,  77, 
		  105,  99, 114, 111, 115, 111, 
		  102, 116,  32,  40,  82,  41, 
		  32,  72,  76,  83,  76,  32, 
		  83, 104,  97, 100, 101, 114, 
		  32,  67, 111, 109, 112, 105, 
		  108, 101, 114,  32,  57,  46, 
		  50,  55,  46,  57,  53,  50, 
		  46,  51,  48,  50,  50,   0, 
		  81,   0,   0,   5,  12,   0, 
		  15, 160, 131, 249,  34,  62, 
		  0,   0,   0,  63, 219,  15, 
		  201,  64, 219,  15,  73, 192, 
		  81,   0,   0,   5,  10,   0, 
		  15, 160,   1,  13, 208, 181, 
		  97,  11, 182, 183, 171, 170, 
		  42,  59, 137, 136, 136,  57, 
		  81,   0,   0,   5,  11,   0, 
		  15, 160, 171, 170, 170, 188, 
		  0,   0,   0, 190,   0,   0, 
		  128,  63,   0,   0,   0,  63, 
		  31,   0,   0,   2,   0,   0, 
		  0, 128,   0,   0,  15, 144, 
		  31,   0,   0,   2,   5,   0, 
		  0, 128,   1,   0,  15, 144, 
		  1,   0,   0,   2,   0,   0, 
		  3, 128,  12,   0, 228, 160, 
		  4,   0,   0,   4,   0,   0, 
		  1, 128,   7,   0,   0, 160, 
		  0,   0,   0, 128,   0,   0, 
		  85, 128,  19,   0,   0,   2, 
		  0,   0,   1, 128,   0,   0, 
		  0, 128,   4,   0,   0,   4, 
		  0,   0,   1, 128,   0,   0, 
		  0, 128,  12,   0, 170, 160, 
		  12,   0, 255, 160,  37,   0, 
		  0,   4,   1,   0,   3, 128, 
		  0,   0,   0, 128,  10,   0, 
		  228, 160,  11,   0, 228, 160, 
		  5,   0,   0,   3,   0,   0, 
		  7, 128,   1,   0, 196, 128, 
		  0,   0, 208, 144,   4,   0, 
		  0,   4,   0,   0,   1, 128, 
		  1,   0,  85, 129,   0,   0, 
		  85, 144,   0,   0,   0, 128, 
		  2,   0,   0,   3,   0,   0, 
		  2, 128,   0,   0, 170, 128, 
		  0,   0,  85, 128,   5,   0, 
		  0,   3,   1,   0,   1, 128, 
		  0,   0,   0, 128,   4,   0, 
		  0, 160,   5,   0,   0,   3, 
		  1,   0,   2, 128,   0,   0, 
		  0, 128,   5,   0,   0, 160, 
		  5,   0,   0,   3,   1,   0, 
		  4, 128,   0,   0,   0, 128, 
		  6,   0,   0, 160,   5,   0, 
		  0,   3,   2,   0,   1, 128, 
		  0,   0,  85, 128,   4,   0, 
		  85, 160,   5,   0,   0,   3, 
		  2,   0,   2, 128,   0,   0, 
		  85, 128,   5,   0,  85, 160, 
		  5,   0,   0,   3,   2,   0, 
		  4, 128,   0,   0,  85, 128, 
		  6,   0,  85, 160,   2,   0, 
		  0,   3,   0,   0,   7, 128, 
		  1,   0, 228, 128,   2,   0, 
		  228, 128,   1,   0,   0,   2, 
		  1,   0,   1, 128,   9,   0, 
		  0, 160,   4,   0,   0,   4, 
		  0,   0,   7, 128,   1,   0, 
		  0, 128,   0,   0, 228, 128, 
		  8,   0, 228, 160,   5,   0, 
		  0,   3,   1,   0,  15, 128, 
		  0,   0,  85, 128,   1,   0, 
		  228, 160,   4,   0,   0,   4, 
		  1,   0,  15, 128,   0,   0, 
		  228, 160,   0,   0,   0, 128, 
		  1,   0, 228, 128,   4,   0, 
		  0,   4,   0,   0,  15, 128, 
		  2,   0, 228, 160,   0,   0, 
		  170, 128,   1,   0, 228, 128, 
		  2,   0,   0,   3,   0,   0, 
		  15, 192,   0,   0, 228, 128, 
		  3,   0, 228, 160,   1,   0, 
		  0,   2,   0,   0,   3, 224, 
		  1,   0, 228, 144, 255, 255, 
		  0,   0
	  };

		  struct MARK_END_VS {};

	 //===========================================================


		  struct MARK_BEGIN_PSH {};


 
		  //
		  // Generated by Microsoft (R) HLSL Shader Compiler 9.27.952.3022
		  //
		  //   fxc /nologo /Fh billiboard_HObj.txt /T ps_2_0 /E ps_main
		  //    C:\TEMP\z_test_compile_eff\billiboard.fx
		  //
		  //
		  // Parameters:
		  //
		  //   float4 color;
		  //   sampler2D smplr;
		  //
		  //
		  // Registers:
		  //
		  //   Name         Reg   Size
		  //   ------------ ----- ----
		  //   color        c0       1
		  //   smplr        s0       1
		  //

		  /*
		  ps_2_0
			  dcl t0.xy
			  dcl_2d s0
			  texld r0, t0, s0
			  mul r0, r0, c0
			  mov oC0, r0
			  */

			  // approximately 3 instruction slots used (1 texture, 2 arithmetic)
 

		  static const BYTE g_ps_data[] =
		  {
			  0,   2, 255, 255, 254, 255, 
			  48,   0,  67,  84,  65,  66, 
			  28,   0,   0,   0, 139,   0, 
			  0,   0,   0,   2, 255, 255, 
			  2,   0,   0,   0,  28,   0, 
			  0,   0,   0,   1,   0,   0, 
			  132,   0,   0,   0,  68,   0, 
			  0,   0,   2,   0,   0,   0, 
			  1,   0,   0,   0,  76,   0, 
			  0,   0,  92,   0,   0,   0, 
			  108,   0,   0,   0,   3,   0, 
			  0,   0,   1,   0,   0,   0, 
			  116,   0,   0,   0,   0,   0, 
			  0,   0,  99, 111, 108, 111, 
			  114,   0, 171, 171,   1,   0, 
			  3,   0,   1,   0,   4,   0, 
			  1,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0, 128,  63, 
			  0,   0, 128,  63,   0,   0, 
			  128,  63,   0,   0, 128,  63, 
			  115, 109, 112, 108, 114,   0, 
			  171, 171,   4,   0,  12,   0, 
			  1,   0,   1,   0,   1,   0, 
			  0,   0,   0,   0,   0,   0, 
			  112, 115,  95,  50,  95,  48, 
			  0,  77, 105,  99, 114, 111, 
			  115, 111, 102, 116,  32,  40, 
			  82,  41,  32,  72,  76,  83, 
			  76,  32,  83, 104,  97, 100, 
			  101, 114,  32,  67, 111, 109, 
			  112, 105, 108, 101, 114,  32, 
			  57,  46,  50,  55,  46,  57, 
			  53,  50,  46,  51,  48,  50, 
			  50,   0,  31,   0,   0,   2, 
			  0,   0,   0, 128,   0,   0, 
			  3, 176,  31,   0,   0,   2, 
			  0,   0,   0, 144,   0,   8, 
			  15, 160,  66,   0,   0,   3, 
			  0,   0,  15, 128,   0,   0, 
			  228, 176,   0,   8, 228, 160, 
			  5,   0,   0,   3,   0,   0, 
			  15, 128,   0,   0, 228, 128, 
			  0,   0, 228, 160,   1,   0, 
			  0,   2,   0,   8,  15, 128, 
			  0,   0, 228, 128, 255, 255, 
			  0,   0
		  };
 
		  struct MARK_END_PSH {};



//=============================================================
HRESULT RenderBillboardImpl::Render(IDirect3DDevice9* pdevice,
			  IDirect3DTexture9* pTexture,
			  const float* matrix4x4_View,  
			  const float* matrix4x4_WorldViewProj,  
			  const RenderBillbOptions& opt,
			  const FlagData& flag ) const 
{
	HRESULT hr = S_OK;

	if(!pdevice)
	{
		return E_FAIL;
	}
 
	//Device dvc(pdevice);
 
	// get old data
	 // TODO ....
	hr |= pdevice->GetRenderState(D3DRS_CULLMODE, &m_RestoreData.dwOldCullMode );

	if(flag.enableStrAlphaBlending)
	{
	hr |= pdevice->GetRenderState(D3DRS_ALPHABLENDENABLE, &m_RestoreData.dwD3DRS_ALPHABLENDENABLE );
	hr |= pdevice->GetRenderState(D3DRS_SRCBLEND, &m_RestoreData.dwD3DRS_SRCBLEND );
 	hr |= pdevice->GetRenderState(D3DRS_DESTBLEND, &m_RestoreData.dwD3DRS_DESTBLEND );
 


	}



	// set vertex shader
	  
	 if(m_pVsh == NULL)
	 {
		 return E_FAIL;
	 }

	 hr |= pdevice->SetVertexShader(m_pVsh);

 

	//              set vertex shader data

	   //   DATA           REGISTER  COUNT
	  //   mWorldViewProj c0       4
	  //   mView          c4       3
	  //   ang            c7       1
	  //   posit          c8       1
	  //   size           c9       1

	 float array [4];
	 array[0] = array[1] = array[2] = array[3] = 1.0f;

	 hr |= pdevice->SetVertexShaderConstantF(0, matrix4x4_WorldViewProj, 4 );
	 hr |= pdevice->SetVertexShaderConstantF(4, matrix4x4_View, 3);

	 array[0] =  - opt.fRotationAngle;   // minus
	 hr |= pdevice->SetVertexShaderConstantF(7, array, 1);

	 array[0] = opt.position.x;
	 array[1] = opt.position.y;
	 array[2] = opt.position.z;
	 array[3] = 1.0f;
	 hr |= pdevice->SetVertexShaderConstantF(8, &opt.position.x , 1);

	  array[0] = opt.size;
	 hr |= pdevice->SetVertexShaderConstantF(9,  array, 1);
 
 

	// set pixel shader	
	 if( m_pPsh == NULL)
	 {
		 return E_FAIL;
	 }
	hr |= pdevice->SetPixelShader( m_pPsh );


	// set pixel shader data
		  //   Name         Reg   Size
		  //   ------------ ----- ----
		  //   color        c0       1	   float4 color;
		  //   smplr        s0       1	  sampler2D smplr;


		hr |= pdevice->SetPixelShaderConstantF(0, &opt.color.r, 1 );
		

	// set texture
	hr |= pdevice->SetTexture( 0 , pTexture );



	// set needed other data
	  // TODO  NONE
	 hr |= pdevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE );
 
	 if(flag.enableStrAlphaBlending)
	 {
		hr =   pdevice->SetRenderState(D3DRS_ALPHABLENDENABLE,1);
		hr |=  pdevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		hr |=  pdevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA); 
	 }
 



	// draw
	hr |= gb::graphics::d3d9::draw::drawMeshPrimitiveQuadXyMem(pdevice) ;


	// restore old data
	  // TODO ...  NONE
	hr |= pdevice->SetRenderState(D3DRS_CULLMODE, m_RestoreData.dwOldCullMode );

	if(flag.enableStrAlphaBlending)
	{
		hr |= pdevice->SetRenderState(D3DRS_ALPHABLENDENABLE, m_RestoreData.dwD3DRS_ALPHABLENDENABLE );
		hr |= pdevice->SetRenderState(D3DRS_SRCBLEND, m_RestoreData.dwD3DRS_SRCBLEND );
		hr |= pdevice->SetRenderState(D3DRS_DESTBLEND, m_RestoreData.dwD3DRS_DESTBLEND );

	}


  return hr;
};



//================================================
RenderBillboardImpl::RenderBillboardImpl(IDirect3DDevice9* pdevice, HRESULT* phrOut) 
{
	m_pVsh = NULL;
	m_pPsh = NULL;


	HRESULT  hr = S_OK;
	*phrOut |= pdevice->CreateVertexShader( (DWORD*)g_vs_data , &m_pVsh );
	if FAILED(*phrOut)
	{			
		throw (std::runtime_error("failed create vertex shader") );
	}

	*phrOut |= pdevice->CreatePixelShader( (DWORD*)g_ps_data , &m_pPsh );
	if FAILED(*phrOut)
	{			
		throw (std::runtime_error("failed create vertex shader") );
	}


	if FAILED(*phrOut)
	{
		throw (std::runtime_error("fail operation "));
	}

	// end func ....
}



//===============================================================
GB_D3D9_API HRESULT  gb::graphics::d3d9::render::CreateRenderBillboardInterface (
								IRenderBillboard** ppOut,
								IDirect3DDevice9* pdevice)
 {
  HRESULT hr = S_OK;

   *ppOut = NULL;

 try 
 {
	 *ppOut =  (IRenderBillboard*)  new RenderBillboardImpl(pdevice, &hr);
 }
 catch(...)
 {
   hr |= E_FAIL;
   // todo :  add debug code
 }



  return hr;
 };

 //===========================================================
 

#endif // 
// end file