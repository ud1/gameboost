#include "DDSParser.h"
//#include <windows.h>

using namespace gb::io;
bool gb::io::loadDDSTexture2D(gb::containers::Texture2DDesc &tex, gb::io::IFile *file)
{
    dds::Header ddsd;
    if(file->read((void*)&ddsd, sizeof(ddsd)) != sizeof(dds::Header))
        return false;
    if(ddsd.Magic != dds::MAGIC) 
		return false;
	tex.bufsize = file->size() - sizeof(dds::Header);
	tex.pixels = new uint8_t[tex.bufsize];
    if(file->read(tex.pixels, tex.bufsize) != tex.bufsize)
        return false;

	tex.width = ddsd.Width;
	tex.height = ddsd.Height;
	tex.nMipmaps = ddsd.MipMapCount;
	switch(ddsd.ddpf.FourCC)
	{
    case dds::DXT1:
        tex.format = gb::containers::eTexturePixelFmt::PIXELFMT_DXT1;
		break;
	case dds::DXT3:
		tex.format = gb::containers::eTexturePixelFmt::PIXELFMT_DXT3;
		break;
	case dds::DXT5:
		tex.format = gb::containers::eTexturePixelFmt::PIXELFMT_DXT5;
		break;
	default:
		_ASSERT_EXPR(0, L"Загрузка всяких разных DDS еще не готова!");
	};
    tex.components = gb::containers::textureGetComponentsCount(tex.format);

	return true;
};
