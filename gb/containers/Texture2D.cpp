
/*      \file FileStream.cpp
 *      \author -Eugene-, kozlov_eugene@list.ru
*/

#include "gb/containers/Texture2D.h"
#include <algorithm>

using namespace gb::containers;

char gb::containers::textureGetBitsPerPixel(int pf)
{
    switch(pf)
    {
        case eTexturePixelFmt::DXT1:
            return 4;
        case eTexturePixelFmt::DXT3:
        case eTexturePixelFmt::DXT5:
            return 8;
        default:
            return 0;
    };
};

char gb::containers::textureGetComponentsCount(int pf)
{
    switch(pf)
    {
        case eTexturePixelFmt::DXT1:
            return 3;
        case eTexturePixelFmt::DXT3:
        case eTexturePixelFmt::DXT5:
            return 4;
        default:
            return 0;
    };
};

Texture2D::Texture2D() 
    : IResource(), width(0), height(0), components(0), format(0), row_bytes(0), num_rows(0) { };

Texture2D::~Texture2D()
{
    
};

bool Texture2D::init(const int _width, const int _height, const int _format, const int _components, const int _mipmaps)
{
    if(isExist())
        return false;
    width = _width;
    height = _height;
    format = _format;
    components = _components;
    groups_count = _mipmaps ? _mipmaps : 1;
    groups_sizes = new size_t[groups_count];
    groups_offsets = new size_t[groups_count];

    num_rows = new size_t[groups_count];
    row_bytes = new size_t[groups_count];
    total_size = 0;
    for(size_t i = 0; i < groups_count; i++)
    {
        int mip_width = width >> i;
        int mip_height = height >> i;
        if(format == eTexturePixelFmt::DXT1 || format == eTexturePixelFmt::DXT3 || format == eTexturePixelFmt::DXT5)
        {
            int numBlocksWide = 0;
            if(mip_width > 0)
                numBlocksWide = std::max(1, mip_width / 4);
            int numBlocksHigh = 0;
            if(mip_height > 0)
                numBlocksHigh = std::max(1, mip_height / 4);
            int numBytesPerBlock = (format == eTexturePixelFmt::DXT1 ? 8 : 16 );
            row_bytes[i] = numBlocksWide * numBytesPerBlock;
            num_rows[i] = numBlocksHigh;
        }
        else
        {
            char bpp = textureGetBitsPerPixel(format);
            row_bytes[i] = ( width * bpp + 7 ) / 8;
            num_rows[i] = height;
        };
        groups_sizes[i] = row_bytes[i] * num_rows[i];
        groups_offsets[i] = i ? (groups_offsets[i - 1] + groups_sizes[i - 1]) : 0;
    };
    return true;
};

bool Texture2D::isExist()
{
    return width && height && format && groups_count && components;   
};

