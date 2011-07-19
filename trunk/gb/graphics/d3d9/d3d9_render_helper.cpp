
#include "d3d9_render_helper.h"

namespace gb
{
 namespace graphics
 {
  namespace d3d9
  {
  
  	  //==============================================================
	  //  	d3d9_render_helper
	  //==============================================================

 		
			void d3d9_render_helper::clear_deph()		
			{
				HRESULT hr = m_pd3d9device->Clear( 0, NULL, D3DCLEAR_ZBUFFER, 0, 1.0f, 0 );
				if FAILED( hr )
				{
				throw std::runtime_error("failed operation");
				}
			}

			void d3d9_render_helper::clear_surface(const color::color3<float>* color) 
			{
				float _r = 0.0f;
				float _g = 0.0f;
				float _b = 0.0f;
				float _a = 1.0f;

				if(color)
				{
					_r = color->r;
					_g = color->g;
					_b = color->b;
				}

				HRESULT hr = m_pd3d9device->Clear( 0, NULL, D3DCLEAR_TARGET , D3DCOLOR_COLORVALUE(_r, _g, _b, _a), 1.0f, 0 );
				if FAILED( hr )
				{
					throw std::runtime_error("failed operation");
				}
			 
			}
 		
			void d3d9_render_helper::set_matrix(const math::mat4* world, const math::mat4* view, const math::mat4* proj)
			{
				assert(m_pd3d9device);
				assert( sizeof(math::mat4) == sizeof(D3DMATRIX)  ) ;

				HRESULT hr =0;
				if(world)
				{
					hr = m_pd3d9device->SetTransform( D3DTS_WORLD, (D3DMATRIX*)&world );
					if FAILED(hr) { throw std::runtime_error("failed operatiion"); }
				}

				if(view)
				{
					hr = m_pd3d9device->SetTransform( D3DTS_VIEW, (D3DMATRIX*)&view );
					if FAILED(hr) { throw std::runtime_error("failed operatiion"); }
				}

				if(proj)
				{
					hr = m_pd3d9device->SetTransform( D3DTS_PROJECTION, (D3DMATRIX*)&proj );
					if FAILED(hr) { throw std::runtime_error("failed operatiion"); }
				}

			}
		 
  
  




  
  
  }
 }
}
