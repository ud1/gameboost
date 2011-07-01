// спрайт ...  просто проба.. набросок... 

#pragma once
#include <gb/base/Types.h>
#include <gb/base/Rectangle.h>


#include "Texture.h"
#include "Device.h"

class Sprite {


......

int32_t draw( Texture* texture, 
			  const gb::base::Rectangle& rec_screen,
			  const gb::base::Rectangle& rec_texture);



};

