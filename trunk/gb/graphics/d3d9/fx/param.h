/** \file
 \brief Обобщёные параметры для эффекта.

*/

#if ( defined(WIN32) && defined(__D3DX9_H__) )


#pragma once
//#include <gb/>

#include <gb/graphics/d3d9/api_decl.h>
#include <gb/graphics/d3d9/d3dx9_dynamic_load/d3dx9_dynamic_load.h>
using   gb::graphics::d3d9::d3dx9_dynamic_load::CD3DX9_Dll_Loader;

#include <gb/fmath/fmath.h> 
#include <gb/color/color.h>

#include <gb/macro.h>


#pragma warning(push)
#pragma warning(disable : 4290)



namespace gb
{

namespace graphics
{

namespace d3d9
{

namespace fx
{

//--------------------------------------------------------------------------
 

  /** \brief Параметр эффекта */
  class Parameter {
  public:
		UINT   semanticid;
		D3DXHANDLE handle;
		D3DXPARAMETER_DESC descr;

		union TUsedData 
		{
			void* ptr;
			float vector4 [4];
		    char bufer [16];
		};

		TUsedData userData;
 
	  Parameter() 
	  { 
		  memset(&semanticid, 0, sizeof(Parameter) );
	  }
 
	  Parameter( const Parameter& par)
	  { 
		 *this = par;
	  }
 
  };
 
 
 

	GB_D3D9_API Parameter*  CreateParamsBuffer(ID3DXEffect* peff) throw(std::runtime_error) ;

	
	GB_D3D9_API HRESULT SetSemanticParams(
				ID3DXEffect* peff, 
				const Parameter* params,
				const gb::fmath::context::GeometryContext* gc,
				const gb::fmath::context::FloatContext* fc
				);
 
 

//-------------------------------------------------------------------------

}
}
}
}

#pragma warning(pop)

#endif
// end file