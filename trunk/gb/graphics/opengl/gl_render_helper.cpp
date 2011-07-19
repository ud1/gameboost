

#include "gl_render_helper.h"

namespace gb
{
 namespace graphics
 {
  namespace opengl
  {
  
  
 
				void gl_render_helper::clear_deph()
				{
					glClear(GL_DEPTH_BUFFER_BIT); 
					GLenum err = glGetError();
					if(err != GL_NO_ERROR)
					{
						assert(false);
						throw std::runtime_error("operation error");
					}
				}

				void gl_render_helper::clear_surface(const color::color3<float>* color)
				{
					float _r = 0.0f;
					float _g = 0.0f;
					float _b = 0.0f;

					if(color)
					{
						_r = color->r;
						_g = color->g;
						_b = color->b;
					}

					glClearColor( _r, _g, _b, 1.0f );
					glClear(GL_COLOR_BUFFER_BIT);
					GLenum err = glGetError();
					if(err != GL_NO_ERROR)
					{
						assert(false);
						throw std::runtime_error("operation error");
					}
				}
 

				void gl_render_helper::set_matrix(const math::mat4* world, const math::mat4* view, const math::mat4* proj)
				{

				#pragma message( "  INSERT CHECK  CODE ! ....  "  )
					assert(false);

					// deprecated (holder)

					// safe matrix mode
					int mmode = 0;
					glGetIntegerv(GL_MATRIX_MODE , &mmode);

					// set new transform

					if(world)
					{
						glMatrixMode(GL_MODELVIEW  );
						math::mat4 modelview;
						if(view)
						{
							modelview = *world   *   *view;
						}
						else
						{
							math::mat4 mview = get_matrix_view();
							modelview = *world   *  mview;
						}

						glLoadMatrixf(  (GLfloat*)&modelview );
					}

					if(view)
					{
						glMatrixMode(GL_MODELVIEW  );
						math::mat4 modelview;
						if(world)
						{	
							modelview = *world   *   *view;
						}
						else
						{
							math::mat4 mworld = get_matrix_world();
							modelview = mworld   *   *view;
						}

						glLoadMatrixf(  (GLfloat*)&modelview );

					}

					if(proj)
					{
						glMatrixMode(GL_PROJECTION );
						glLoadMatrixf( (GLfloat*)proj );
					}

					// restore matrix mode 
					glMatrixMode(mmode);


				}

 
  

  
  
  
  
  
  }
 }
}


