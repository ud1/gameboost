#include "d3d9pch.h"

#if ( defined(WIN32) && defined(__D3DX9_H__) )

#include "param.h"

#pragma warning(push)
#pragma warning(disable : 4290)
#pragma warning(disable : 4297)

namespace gb {
namespace graphics {
namespace d3d9 {
namespace fx {

//======================================================================



//======================================================================
GB_D3D9_API Parameter*  CreateParamsBuffer(ID3DXEffect* peff) throw(std::runtime_error)
{
Parameter* res = NULL;
HRESULT hr =0;
 D3DXEFFECT_DESC  effDescr;
 hr |= peff->GetDesc(&effDescr);
 if FAILED(hr)
 {
	 throw std::runtime_error("operation failed");
 }

 res = new	Parameter[ effDescr.Parameters ];

 for(int c=0; c<(int)effDescr.Parameters; c++)
 {

		  res[c].handle = peff->GetParameter( NULL, c);
		 if( NULL == res[c].handle  ) 
		 {
			  delete [] res;
			  throw std::runtime_error("get handle error"); 
		 }

		 hr |= peff->GetParameterDesc( res[c].handle , &res[c].descr );
		 if FAILED(hr)
		 {
			 delete [] res;
			 throw std::runtime_error("operation failed");
		 }

		 if( res[c].descr.Semantic )
		 {
			 std::string strSemantic = res[c].descr.Semantic;
			 D3DXPARAMETER_DESC _pardes = res[c].descr;


			 // string param ignored;
			 if( (res[c].descr.Class == D3DXPC_OBJECT)&& (res[0].descr.Type == D3DXPT_STRING)  )
			 {
			  continue;
			 }

			 // float
			 if( (res[c].descr.Class==D3DXPC_SCALAR) && (res[c].descr.Type==D3DXPT_FLOAT)  )
			 {
				 gb::fmath::context::float_context_type_e::e _type = gb::fmath::context::float_context_type_e::UNDEFINED;
				 if(!gb::fmath::context::float_context_type_e::fromstr(_type, strSemantic.c_str() )  )
				 {

					 assert(false);
					 throw std::runtime_error("undef semantic name for matrix");
				 }

				 res[c].semanticid = (UINT)_type;
				 continue;
			 }


			 // vector4
			 if( (res[c].descr.Class == D3DXPC_VECTOR) && (res[c].descr.Type == D3DXPT_FLOAT) && (res[c].descr.Columns==4) )
			 {
				 gb::fmath::context::vector_context_type_e::e _type = gb::fmath::context::vector_context_type_e::UNDEFINED;
			   if( !gb::fmath::context::vector_context_type_e::fromstr(_type , strSemantic.c_str() ) )
			   {
				   assert(false);
				   throw std::runtime_error("undef semantic name for vector4");					   
			   }

			   res[c].semanticid = (UINT)_type;
			 }

			 // matrix 4x4
			 if( ((res[c].descr.Class == D3DXPC_MATRIX_ROWS) || (res[c].descr.Class == D3DXPC_MATRIX_COLUMNS)) && (res[c].descr.Rows==4) && (res[c].descr.Columns==4) )
			 {
				 gb::fmath::context::matrix4x4_context_type_e::e  _type = gb::fmath::context::matrix4x4_context_type_e::UNDEFINED;
					 if( !gb::fmath::context::matrix4x4_context_type_e::fromstr( _type , strSemantic.c_str() ) )
				 {

				  assert(false);
				  throw std::runtime_error("undef semantic name for matrix");
				 }

				 res[c].semanticid = (UINT)_type;
				 continue;
			 }

			 // texture
			 if( (res[c].descr.Type==D3DXPT_TEXTURE) || 
				 (res[c].descr.Type==D3DXPT_TEXTURE1D)|| 
				 (res[c].descr.Type==D3DXPT_TEXTURE2D)|| 
				 (res[c].descr.Type==D3DXPT_TEXTURE3D)|| 
				 (res[c].descr.Type==D3DXPT_TEXTURECUBE) )
			 {



			 }



			 // ???
			// assert(false);
		 }
		 // if


 if FAILED(hr)
 {
	 assert(false);
	 delete [] res;
	 throw std::runtime_error("operation failed");
 }


 }
 // for


 return res;
}


//=====================================================================
GB_D3D9_API HRESULT SetSemanticParams(
				ID3DXEffect* peff, 
				const Parameter* params,
				const gb::fmath::context::GeometryContext* gc,
				const gb::fmath::context::FloatContext* fc
				) 
{
	  HRESULT hr =0;
	  D3DXEFFECT_DESC  effDescr;
	  hr |= peff->GetDesc(&effDescr);
	  if FAILED(hr)
	  {
		  throw std::runtime_error("operation failed");
	  }

	  for(int c=0; c<(int)effDescr.Parameters; c++)
	  {
	    const Parameter& par = params[c];
		if(par.semanticid == 0) continue;

		// set params  //

		// float
		if(fc)
		{
		if( (par.descr.Class==D3DXPC_SCALAR) && (par.descr.Type==D3DXPT_FLOAT)  )
		{
			gb::fmath::context::float_context_type_e::e _type = (gb::fmath::context::float_context_type_e::e)par.semanticid;
			hr |= peff->SetFloat( par.handle, fc->getValue_by_context_type(_type)  );

		}
		}

		// vector4
		if(gc)
		{
		if( (par.descr.Class == D3DXPC_VECTOR) && (par.descr.Type == D3DXPT_FLOAT) && 
		    (par.descr.Columns==4) )
		{
			gb::fmath::context::vector_context_type_e::e _type = (gb::fmath::context::vector_context_type_e::e)par.semanticid;
			const gb::fmath::vec4* _vector = gc->get_vector4_by_context_type(_type);
			assert(_vector);
			hr |= peff->SetVector(par.handle ,  (D3DXVECTOR4*)_vector );

		}
		}


		// matrix 4x4
		if(gc)
		{
		if( ((par.descr.Class == D3DXPC_MATRIX_ROWS) || (par.descr.Class == D3DXPC_MATRIX_COLUMNS))
                  && (par.descr.Rows==4) && (par.descr.Columns==4) )
		{
			gb::fmath::context::matrix4x4_context_type_e::e _type = (gb::fmath::context::matrix4x4_context_type_e::e)par.semanticid;

			const gb::fmath::mat44* _matrix = gc->get_matrix_by_context_type(_type);
			assert(_matrix);

			if(0)
			{
			   hr |= peff->SetMatrixTranspose(par.handle , (D3DXMATRIX*)_matrix );
			}
			else
			{
			   hr |= peff->SetMatrix(par.handle , (D3DXMATRIX*)_matrix );
			}
			

		}
		}
		

		// texture

 


	    int _end =0;
	  }
	  // for

      return hr;
}








//======================================================================

}
}
}
}

#pragma warning(pop)

#endif
// end file