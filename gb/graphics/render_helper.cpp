
#include "render_helper.h"

namespace gb
{
 namespace graphics
 {



	 void render_helper::set_matrix_world(const math::mat4& m)
	 {
		   set_matrix(  &m , NULL  ,  NULL );
	 }

	 void render_helper::set_matrix_view(const math::mat4& m)
	 {
		   set_matrix(  NULL , &m  ,  NULL );
	 }

	 void render_helper::set_matrix_proj(const math::mat4& m)
	 {
		  set_matrix(  NULL , NULL  ,  &m );
	 }

	 const math::mat4& render_helper::get_matrix_world() const
	 {
		  assert(false); static  math::mat4 xxxxx;  return xxxxx;
	 }

	 const math::mat4& render_helper::get_matrix_view() const
	 {
		 assert(false);	 static  math::mat4 xxxxx;  return xxxxx;
	 }

	 const math::mat4& render_helper::get_matrix_proj() const
	 {
		 assert(false);	static  math::mat4 xxxxx;  return xxxxx;
	 }


	 void render_helper::push_matrix_world()
	 {
		 math::mat4 m = get_matrix_world();
		 _matstack_world.push(m);
	 }

	 void render_helper::push_matrix_view()
	 {
		 math::mat4 m = get_matrix_view();
		_matstack_view.push(m);
	 }
	 
	 void render_helper::push_matrix_proj()
	 {
		 math::mat4 m = get_matrix_proj();
		 _matstack_proj.push(m);
	 }

	 void render_helper::pop_matrix_world()
	 {
		 if(_matstack_world.empty())
		 {
			 // ????
			 return ;
		 }

		 _matstack_world.pop();
		 if(_matstack_world.empty())
		 {
			 //?????
			 return;
		 }

		 math::mat4 m = _matstack_world.top();
		set_matrix( &m , NULL, NULL );

	 }

	 void render_helper::pop_matrix_view()
	 {
	
		if(_matstack_view.empty())
		{
			// ????
			return ;
		}

		_matstack_view.pop();
		if(_matstack_view.empty())
		{
			//?????
			return;
		}

		math::mat4 m = _matstack_view.top();
		set_matrix( NULL, &m, NULL );	

	 }

	 void render_helper::pop_matrix_proj()
	 {
		 if(_matstack_proj.empty())
		 {
			 // ????
			 return ;
		 }

		 _matstack_proj.pop();
		 if(_matstack_proj.empty())
		 {
			 //?????
			 return;
		 }

		 math::mat4 m = _matstack_proj.top();
		 set_matrix( NULL, NULL, &m );	

	 }



 }
}
