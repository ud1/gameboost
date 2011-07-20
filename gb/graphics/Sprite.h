/**  \file
 \brief draw sprites on screen
 
 
*/

// спрайт ...  просто проба.. набросок... 

#pragma once

#include "../base/Types.h"
#include "../base/Rectangle.h"

#include "../color/color4.h"

#include "Texture.h"
#include "Device.h"

#include <string.h>
#include <assert.h>

namespace gb
{
 namespace graphics
 {


class Sprite {
public:

	virtual ~Sprite() {}
	
 

	//! одиночная отрисовка спрайта
	virtual void draw( Texture* texture,  
						const gb::base::Rectangle& rec_screen,  
						const gb::base::Rectangle& rec_texture) =0;


		struct sprite_mult_draw_data 
		{
			gb::base::Rectangle   rec_screen; 
			gb::base::Rectangle   rec_texture;
			gb::color::color4<float>   color; // если в массиве ноль, то не принимается(не устанавливается)
		
		
			sprite_mult_draw_data() 
			{ 
				memset( &rec_screen, 0, sizeof(sprite_mult_draw_data) ); 
			}
		};
	
	//! множественная отрисовка экранных спрайтов	.
	virtual void draw_multiply(Texture*, const std::vector<sprite_mult_draw_data>&) =0;					

	};



 }
}