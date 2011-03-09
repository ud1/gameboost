#include <gb/fs/LocalFS.h>
#include <gb/loaders/images/BmpLoader.h>
#include <gb/containers/Image.h>
#include <gb/graphics/FontFreeType.h>
#include <gb/base/Atlas.h>

using namespace gb::fs;
using namespace gb::loaders;
using namespace gb::containers;
using namespace gb::graphics2d;
using namespace gb::base;

int main()
{
	const int im_size = 256;
	Image image;
	BmpLoader bmpLoader;
	LocalFS fs;
	Atlas atlas(im_size, im_size);
	
	InputStream *input = fs.getInputStream("../data/BaroqueScript.ttf");
	if (!input)
		return 0;
	
	FontFreeType free_type;
	if (!free_type.init())
		return 0;
	
	Font *font = free_type.create(*input, 16*64);
	if (!font)
		return 0;
	
	image.width = im_size;
	image.height = im_size;
	image.pixel_format = ePixelFormat::RGB_888;
	image.calculateDataSize();
	image.pitch = image.row_size + image.padding_bytes;
	image.data = new char[image.data_size];
	memset(image.data, 0, image.data_size);
	
	for (wchar_t ch = L'a'; ch <= L'z'; ++ch)
	{
		Font::GlyphInfo info;
		if (font->getGlyphInfo(ch, info))
		{
			Rectangle rec;
			Image sub_image;
			sub_image.width = rec.width = info.width;
			sub_image.height = rec.height = info.height;
			if(atlas.insert(rec))
			{
				image.subImage(sub_image, rec.left, rec.top);
				font->render(ch, sub_image);
			}
		}
	}
	
	OutputStream *file = fs.getOutputStream("../data/font_test.bmp", true);
	bmpLoader.saveImage(*file, image);
	file->release();
	delete []image.data;
	return 0;
}