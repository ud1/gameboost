#include "PixelFormat.h"

namespace
{
	using namespace gb::containers;
	
	const int FLOAT_BITS = 8*sizeof(float);
	
	PixelFormatDescription descrs[] = 
	{
		{"RGB_888",		24, 8, 8, 8, 0, 3, false, false},
		{"BGR_888",		24, 8, 8, 8, 0, 3, false, false},
		{"RGBA_8888",	32, 8, 8, 8, 8, 4, false, false},
		{"BGRA_8888",	32, 8, 8, 8, 8, 4, false, false},
		{"R_8",			 8, 8, 0, 0, 0, 1, false, false},
		{"RG_88",		16, 8, 8, 0, 0, 2, false, false},
		
		{"RGB_332",		 8, 3, 3, 2, 0, 3, false, false},
		{"RGB_233",		 8, 2, 3, 3, 0, 3, false, false},
		{"RGB_565",		16, 5, 6, 5, 0, 3, false, false},
		
		{"RGBA_4444",	16, 4, 4, 4, 4, 4, false, false},
		{"RGBA_5551",	16, 5, 5, 5, 1, 4, false, false},
		{"RGBA_10_10_10_2",	32, 10, 10, 10, 2, 4, false, false},
		
		{"FR", FLOAT_BITS, FLOAT_BITS, 0, 0, 0, 1, false, true},
		{"FRG", 2*FLOAT_BITS, FLOAT_BITS, FLOAT_BITS, 0, 0, 2, false, true},
		{"FRGB", 3*FLOAT_BITS, FLOAT_BITS, FLOAT_BITS, FLOAT_BITS, 0, 3, false, true},
		{"FRGBA", 4*FLOAT_BITS, FLOAT_BITS, FLOAT_BITS, FLOAT_BITS, FLOAT_BITS, 4, false, true}
	};
}

namespace gb
{
	namespace containers
	{
		const PixelFormatDescription *getPFDescription(ePixelFormat::PixelFormat f)
		{
			return &descrs[f];
		}
	}
}