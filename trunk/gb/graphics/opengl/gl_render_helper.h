/**   \file
 *   
 * 
 * 
 */


#pragma once

#include "../render_helper.h"

#include <GL/gl.h>
#include <GL3/gl3.h>

namespace gb
{
	namespace graphics
	{
		namespace opengl
		{
		
			class gl_render_helper : public render_helper {
			public:

				gl_render_helper()	{ }


				virtual void clear_deph() ;

				virtual void clear_surface(const color::color3<float>* color) ;

				virtual void set_matrix(const math::mat4* world, const math::mat4* view, const math::mat4* proj);


			
			};
		
		
		} // end namespace opengl
	}
}
