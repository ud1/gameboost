#pragma once

#include <gb/containers/Image.h>
#include <gb/base/IRefCountable.h>
#include <gb/base/Rectangle.h>

namespace gb
{
	namespace graphics
	{
		struct ImageBlock : public containers::AutoImage, public base::Rectangle, public base::IRefCountable {};
	}
}
