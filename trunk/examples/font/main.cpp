#include <gb/fs/LocalFS.h>
#include <gb/loaders/images/BmpLoader.h>
#include <gb/containers/Image.h>
#include <gb/graphics/FontFreeType.h>
#include <gb/base/Atlas.h>

#include <cstring>

using namespace gb;

int main()
{
	const int im_size = 256;
	containers::Image image;
	loaders::BmpLoader bmpLoader;
	fs::LocalFS fs;
	base::Atlas atlas(im_size, im_size);
	
	fs::InputStream *input = fs.getInputStream("../data/BaroqueScript.ttf");
	if (!input)
		return 0;
	
	graphics2d::FontFreeType free_type;
	if (!free_type.init())
		return 0;
	
	graphics2d::Font *font = free_type.create(*input, 16*64);
	if (!font)
		return 0;
	
	image.width = im_size;
	image.height = im_size;
	image.pixel_format = containers::ePixelFormat::RGB_888;
	image.calculateDataSize();
	image.pitch = image.row_size + image.padding_bytes;
	image.data = new char[image.data_size];
	memset(image.data, 0, image.data_size);
	
	for (wchar_t ch = L'a'; ch <= L'z'; ++ch)
	{
		graphics2d::Font::GlyphInfo info;
		if (font->getGlyphInfo(ch, info))
		{
			base::Rectangle rec;
			containers::Image sub_image;
			sub_image.width = rec.width = info.width;
			sub_image.height = rec.height = info.height;
			if(atlas.insert(rec))
			{
				image.subImage(sub_image, rec.left, rec.top);
				font->render(ch, sub_image);
			}
		}
	}
	
	fs::OutputStream *file = fs.getOutputStream("../data/font_test.bmp", true);
	bmpLoader.saveImage(*file, image);
	file->release();
	delete []image.data;
	return 0;
}