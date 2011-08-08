#pragma once

#include <gb/containers/Image.h>
#include <gb/base/IRefCountable.h>
#include <gb/base/Rectangle.h>
#include <gb/base/Updatable.h>

namespace gb
{
	namespace graphics2d
	{
		struct ImageBlock : public containers::AutoImage, public base::Rectangle, public base::Updatable, public base::IRefCountable {};
		
		typedef base::RefCntHolder<const ImageBlock> PImageBlock;
	}
}
