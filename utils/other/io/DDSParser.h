/*      \file FileStream.cpp
 *      \author -Eugene-, kozlov_eugene@list.ru
*/
#pragma once
#include "gb/base/Types.h"
#include "gb/containers/Texture2D.h"
#include "gb/io/IStream.h"

#ifndef FOURCC
#define FOURCC(ch0, ch1, ch2, ch3)                                                  \
                ((uint32_t)(uint8_t)(ch0)        | ((uint32_t)(uint8_t)(ch1) << 8) |    \
                ((uint32_t)(uint8_t)(ch2) << 16) | ((uint32_t)(uint8_t)(ch3) << 24 ))
#endif

namespace gb
{
    namespace io
    {
        namespace dds
        {
            const unsigned int DXT1             = FOURCC('D','X','T','1');
	        const unsigned int DXT3             = FOURCC('D','X','T','3');
	        const unsigned int DXT5             = FOURCC('D','X','T','5');
	        const unsigned int MAGIC            = FOURCC('D','D','S',' ');

            struct PixelFormat 
            {
	            uint32_t Size;
	            uint32_t Flags;
	            uint32_t FourCC;
	            uint32_t RGBBitCount;
	            uint32_t RBitMask;
	            uint32_t GBitMask;
	            uint32_t BBitMask;
	            uint32_t ABitMask;
            };
            struct Header
            {
	            uint32_t Magic;
	            uint32_t Size;
	            uint32_t Flags;
	            uint32_t Height;
	            uint32_t Width;
	            uint32_t LinearSize;
	            uint32_t Depth;
	            uint32_t MipMapCount;
	            uint32_t Reserved1[11];
	            PixelFormat ddpf;
	            uint32_t Caps;
	            uint32_t Caps2;
	            uint32_t Caps3;
	            uint32_t Caps4;
	            uint32_t Reserved2;
            };
        };

        bool loadDDSTexture2D(gb::containers::Texture2D &tex, gb::io::IStream *file);
    };
};
#undef FOURCC