
#pragma once

#Include "../Sprite.h"



namespace gb
{
 namespace graphics
 {
  namespace opengl
  {
  
  
  class GLSprite : public SPrite {
  public:
  
  virtual ~GLSprite () {}
  
  
  		virtual void draw( Texture* texture,  
					const gb::base::Rectangle& rec_screen,  
					const gb::base::Rectangle& rec_texture)
		{
		assert(false);
		
		}


		virtual void draw_multiply(Texture*, const std::vector<sprite_mult_draw_data>&)
		{
		assert(false);
		
		
		}
  
  
  
  };
  
  
  
  
  
  
  
  }
 }
}
