/**  \file
* \brief  помощь в отрисовке кадра.
* 
* 
*
*/

#pragma once

#include "../math/math.h"
#include "../color/color3.h"
#include <stack>


#include <stdexcept>
#include <assert.h>


namespace gb
{

 namespace graphics
 {
 
 
  class render_helper {
  public:
  
  	 render_helper() {}
	 virtual ~render_helper() {}

		//   clear frame deph buffer
		virtual void clear_deph() =0;
		//* clear render surface. if parameter NULL, then will be black color.
		virtual void clear_surface(const color::color3<float>*) =0;


		void set_matrix_world(const math::mat4&);
		void set_matrix_view(const math::mat4&);
		void set_matrix_proj(const math::mat4&);

		const math::mat4& get_matrix_world() const;
		const math::mat4& get_matrix_view() const;
		const math::mat4& get_matrix_proj() const;


		void push_matrix_world();
		void push_matrix_view();
		void push_matrix_proj();

		void pop_matrix_world();
		void pop_matrix_view();
		void pop_matrix_proj();

	protected:

	//* постановка новой матрицы. если в аргументе NULL, то матрица не меняется.
	virtual void set_matrix(const math::mat4* world, const math::mat4* view, const math::mat4* proj) =0; 
  




  private:

	std::stack<math::mat4> _matstack_world;
	std::stack<math::mat4> _matstack_view;
	std::stack<math::mat4> _matstack_proj;

  
  };
 
 
 
 
 
 
 }
}
