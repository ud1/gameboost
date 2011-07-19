/**   \file
 *   
 * 
 * 
 */


#pragma once

#include "../render_helper.h"

#include <d3d9.h>

namespace gb
{

	namespace graphics
	{

		namespace d3d9
		{
		
			class d3d9_render_helper : public render_helper {
			public:
				IDirect3DDevice9* m_pd3d9device;
		
			d3d9_render_helper(IDirect3DDevice9* device) :  m_pd3d9device(device)
			{
				assert(m_pd3d9device);
			}
		
			virtual void clear_deph();

			virtual void clear_surface(const color::color3<float>* color);
 		
			virtual void set_matrix(const math::mat4* world, const math::mat4* view, const math::mat4* proj);
		
			};

		}
	}
}


