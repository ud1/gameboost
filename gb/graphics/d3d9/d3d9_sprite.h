


#pragma once

#include "../Sprite.h"

namespace gb
{

 namespace graphics
 {

  namespace d3d9
  {
  
  
	  class d3d9_sprite : public Sprite {
	  public:
	  
		virtual ~d3d9_sprite() {}

		virtual void draw( Texture* texture,  
					const gb::base::Rectangle& rec_screen,  
					const gb::base::Rectangle& rec_texture);


		virtual void draw_multiply(Texture*, const std::vector<sprite_mult_draw_data>&);		

	  
	  };
  
  
  
 
  
  }
 }
}
