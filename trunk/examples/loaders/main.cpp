#include <gb/fs/LocalFS.h>
#include <gb/loaders/images/JpegLoader.h>
#include <gb/containers/Image.h>

using namespace gb::fs;
using namespace gb::loaders;
using namespace gb::containers;

int main()
{
	AutoImage image, image_gr;
	JpegLoader jpegLoader;
	LocalFS fs;
	InputStream *file = fs.getInputStream("../data/gnom.jpg");
	if (!file)
		return 0;
	
	if (!image.load(jpegLoader, *file))
		return 0;
	
	image_gr.copyFrom(image, ePixelFormat::GRAYSCALE8);
	
	OutputStream *out = fs.getOutputStream("../data/gnom_gr.jpg", true);
	if (!out)
		return 0;
	
	image_gr.save(jpegLoader, *out);	
	file->release();
	out->release();
	return 0;
}