#include <gb/fs/LocalFS.h>
#include <gb/loaders/images/BmpLoader.h>
#include <gb/loaders/images/JpegLoader.h>

using namespace gb::fs;
using namespace gb::loaders;
using namespace gb::containers;

int main()
{
	Image2d image;
	BmpLoader bmpLoader;
	JpegLoader jpegLoader;
	LocalFS fs;
	InputStream *file = fs.getInputStream("../data/gnom.jpg");
	if (!file)
		return 0;
	
	if (!jpegLoader.loadImage2dHeader(*file, image))
		return 0;
	
	image.data = new char[image.data_size];
	
	if (!jpegLoader.loadImage2d(*file, image))
		return 0;
		
	OutputStream *out = fs.getOutputStream("../data/gnom.bmp", true);
	if (!out)
		return 0;
	bmpLoader.saveImage2d(*out, image);
	
	delete []image.data;
	
	file->release();
	out->release();
	return 0;
}