/*      \file FileStream.cpp
 *      \author -Eugene-, kozlov_eugene@list.ru
*/
#include "pch.h"
#include "gb/io/DDSParser.h"

using namespace gb::io;
bool gb::io::loadDDSTexture2D(gb::containers::Texture2D &tex, gb::io::IStream *file)
{
    dds::Header ddsd;
    if(file->read((void*)&ddsd, sizeof(ddsd)) != sizeof(dds::Header))
        return false;
    if(ddsd.Magic != dds::MAGIC) 
		return false;
    int format = 0;
	switch(ddsd.ddpf.FourCC)
	{
    case dds::DXT1:
        format = gb::containers::eTexturePixelFmt::DXT1;
		break;
	case dds::DXT3:
		format = gb::containers::eTexturePixelFmt::DXT3;
		break;
	case dds::DXT5:
		format = gb::containers::eTexturePixelFmt::DXT5;
		break;
	default:
		_ASSERT_EXPR(0, L"Загрузка всяких разных DDS еще не готова!");
	};

    if(!tex.init(ddsd.Width, ddsd.Height, format, gb::containers::textureGetComponentsCount(format), ddsd.MipMapCount))
        return false;
    tex.create((size_t) (file->size() - sizeof(dds::Header)) );
    return file->read(tex.getDataPointer(), tex.getTotalSize()) == tex.getTotalSize();
};
