#pragma once
#include "..\Config.h"
#include "..\base\types.h"

namespace gb
{
    namespace containers
    {
        struct eTexturePixelFmt
        {
            enum 
            {
                PIXELFMT_DXT1 = 0,
                PIXELFMT_DXT3 = 1,
                PIXELFMT_DXT5 = 2
            };
        };
	    struct Texture2DDesc
	    {
		    long	components;
		    long	bufsize;
		    long	width;
		    long	height;
		    long	nMipmaps;
		    uint8_t	*pixels;
		    int 	format;
	    };
        char textureGetBitsPerPixel(int pf);
        char textureGetComponentsCount(int pf);
	    void textureGetInfo(int width, int height, int fmt, int &numBytes, int &rowBytes, int &numRows);
    };
};