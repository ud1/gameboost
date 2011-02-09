#include "TextureDesc.h"
#include <algorithm>

using namespace gb::containers;

char gb::containers::textureGetBitsPerPixel(int pf)
{
    switch(pf)
    {
        case eTexturePixelFmt::PIXELFMT_DXT1:
            return 4;
        case eTexturePixelFmt::PIXELFMT_DXT3:
        case eTexturePixelFmt::PIXELFMT_DXT5:
            return 8;
        default:
            return 0;
    };
};

char gb::containers::textureGetComponentsCount(int pf)
{
    switch(pf)
    {
        case eTexturePixelFmt::PIXELFMT_DXT1:
            return 3;
        case eTexturePixelFmt::PIXELFMT_DXT3:
        case eTexturePixelFmt::PIXELFMT_DXT5:
            return 4;
        default:
            return 0;
    };
};

void gb::containers::textureGetInfo(int width, int height, int fmt, int &numBytes, int &rowBytes, int &numRows)
{
    if(fmt == eTexturePixelFmt::PIXELFMT_DXT1 || fmt == eTexturePixelFmt::PIXELFMT_DXT3 || fmt == eTexturePixelFmt::PIXELFMT_DXT5)
    {
        int numBlocksWide = 0;
        if(width > 0)
            numBlocksWide = std::max(1, width / 4);
        int numBlocksHigh = 0;
        if(height > 0)
            numBlocksHigh = std::max(1, height / 4);
        int numBytesPerBlock = (fmt == eTexturePixelFmt::PIXELFMT_DXT1 ? 8 : 16 );
        rowBytes = numBlocksWide * numBytesPerBlock;
        numRows = numBlocksHigh;
    }
    else
    {
        char bpp = textureGetBitsPerPixel(fmt);
        rowBytes = ( width * bpp + 7 ) / 8; // round up to nearest byte
        numRows = height;
    };
    numBytes = rowBytes * numRows;
};

