template <>
void convert<ePixelFormat::ALPHA8, ePixelFormat::RGBA_8888>(const Image &from, Image &to)
{
	for (int i = 0; i < from.height; ++i)
	{
		const char *frow = from.data + i * from.pitch;
		char *trow = to.data + i * to.pitch;
		for (int j = 0; j < from.width; ++j)
		{
			const colors::grayscale8 *from_texel = (const colors::grayscale8 *) frow + j;
			colors::rgba *to_texel = ((colors::rgba *) trow) + j;
			
			to_texel->r = to_texel->g = to_texel->b = 255;
			to_texel->a = from_texel->value;
		}
	}
}

template <>
void convert<ePixelFormat::ALPHA8, ePixelFormat::FRGBA>(const Image &from, Image &to)
{
	for (int i = 0; i < from.height; ++i)
	{
		const char *frow = from.data + i * from.pitch;
		char *trow = to.data + i * to.pitch;
		for (int j = 0; j < from.width; ++j)
		{
			const colors::grayscale8 *from_texel = (const colors::grayscale8 *) frow + j;
			colors::frgba *to_texel = (colors::frgba *) trow + j;
			
			to_texel->r = to_texel->g = to_texel->b = 1.0f;
			to_texel->a = from_texel->value/255.0f;
		}
	}
}

template <>
void convert<ePixelFormat::RGBA_8888, ePixelFormat::ALPHA8>(const Image &from, Image &to)
{
	convert<ePixelFormat::RGBA_8888, ePixelFormat::GRAYSCALE8>(from, to);
}

template <>
void convert<ePixelFormat::FRGBA, ePixelFormat::ALPHA8>(const Image &from, Image &to)
{
	convert<ePixelFormat::FRGBA, ePixelFormat::GRAYSCALE8>(from, to);
}

template <>
void convert<ePixelFormat::GRAYSCALE8, ePixelFormat::ALPHA8>(const Image &from, Image &to)
{
	convert<ePixelFormat::GRAYSCALE8, ePixelFormat::GRAYSCALE8>(from, to);
}

template <>
void convert<ePixelFormat::ALPHA8, ePixelFormat::GRAYSCALE8>(const Image &from, Image &to)
{
	convert<ePixelFormat::GRAYSCALE8, ePixelFormat::GRAYSCALE8>(from, to);
}

template <>
void convert<ePixelFormat::ALPHA8, ePixelFormat::ALPHA8>(const Image &from, Image &to)
{
	convert<ePixelFormat::GRAYSCALE8, ePixelFormat::GRAYSCALE8>(from, to);
}