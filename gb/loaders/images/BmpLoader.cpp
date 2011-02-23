#include "BmpLoader.h"
#include <gb/base/Types.h>

#include <cassert>

namespace
{
	using namespace gb::fs;
	using namespace gb::containers;
	
	const uint16_t BMP_MAGIC = (('M' << 8) | 'B');
	const int BITMAP_FILE_HEADER_SIZE = 14;
	const int BITMAP_INFO_HEADER_SIZE = 40;
	
	struct BitmapFileHeader
	{
		uint16_t type; 
		uint32_t size;
		uint16_t reserved1; 
		uint16_t reserved2;
		uint32_t off_bits;
	};
	
	InputStream &operator >> (InputStream &stream, BitmapFileHeader &h)
	{
		return stream >> h.type >> h.size >> h.reserved1 >> h.reserved2 >> h.off_bits;
	}
	
	OutputStream &operator >> (OutputStream &stream, const BitmapFileHeader &h)
	{
		return stream << h.type << h.size << h.reserved1 << h.reserved2 << h.off_bits;
	}

	struct BitmapInfoHeader
	{
		uint32_t size; 
		int32_t width; 
		int32_t height; 
		uint16_t planes; 
		uint16_t bit_count;
		uint32_t compression; 
		uint32_t size_image; 
		int32_t xpels_per_meter; 
		int32_t ypels_per_meter; 
		uint32_t clr_used; 
		uint32_t clr_important; 
	};
	
	InputStream &operator >> (InputStream &stream, BitmapInfoHeader &h)
	{
		return stream
			>> h.size >> h.width >> h.height >> h.planes >> h.bit_count
			>> h.compression >> h.size_image >> h.xpels_per_meter >> h.ypels_per_meter
			>> h.clr_used >> h.clr_important;
	}
	
	OutputStream &operator << (OutputStream &stream, const BitmapInfoHeader &h)
	{
		return stream
			<< h.size << h.width << h.height << h.planes << h.bit_count
			<< h.compression << h.size_image << h.xpels_per_meter << h.ypels_per_meter
			<< h.clr_used << h.clr_important;
	}
	
	struct BitmapRGBQuad
	{
		uint8_t blue;
		uint8_t green; 
		uint8_t red;
		uint8_t reserved;
	}; 
}

namespace gb
{
	namespace loaders
	{
		
		using namespace gb::containers;
		
		bool BmpLoader::loadImage2dHeader(InputStream &input, Image2dHeader &header_out)
		{
			BitmapFileHeader fheader;
			BitmapInfoHeader iheader;
			
			input.seek(0, eSeekType::HEAD);
			
			try
			{
				input >> fheader >> iheader;
			}
			catch (std::runtime_error)
			{
				return false;
			}
			
			if (fheader.type != BMP_MAGIC)
				return false;
			
			if (fheader.reserved1 != 0 || fheader.reserved2 != 0)
				return false;
			
			if (iheader.bit_count != 24 || iheader.bit_count != 32)
				return false;
			
			header_out.width = iheader.width;
			header_out.width = iheader.height;
			header_out.pixel_format = iheader.bit_count == 24 ? ePixelFormat::BGR_888 : ePixelFormat::BGRA_8888;
			header_out.row_size_in_bytes = iheader.width * iheader.bit_count/8;
			header_out.row_size_in_bytes = (header_out.row_size_in_bytes + 3) & ~3;
			header_out.data_size = header_out.row_size_in_bytes * header_out.height;
			return true;
		}
		
		bool BmpLoader::loadImage2d(fs::InputStream &input, containers::Image2d &image_out)
		{
			if (!loadImage2dHeader(input, image_out))
				return false;
			
			int row_len = image_out.row_size_in_bytes;
			for (int i = image_out.height; i --> 0;)
			{
				if (input.read(image_out.data + i*row_len, row_len) != row_len)
					return false;
			}
			
			return true;
		}
		
		bool BmpLoader::saveImage2d(fs::OutputStream &output, const containers::Image2d &image)
		{
			assert(image.data);
			assert(image.row_size_in_bytes == (image.width*getPFDescription(image.pixel_format)->bits/8 + 3) & ~3);
			assert(image.data_size == image.row_size_in_bytes*image.height);
			
			if (image.pixel_format != ePixelFormat::BGR_888 || image.pixel_format != ePixelFormat::BGRA_8888)
			{
				Image2d temp;
				temp.width = image.width;
				temp.height = image.height;
				if (getPFDescription(image.pixel_format)->components <= 3)
					temp.pixel_format = ePixelFormat::BGR_888;
				else temp.pixel_format = ePixelFormat::BGRA_8888;
				
				temp.row_size_in_bytes = (temp.width*getPFDescription(temp.pixel_format)->bits/8 + 3) & ~3;
				temp.data_size = temp.height * temp.row_size_in_bytes;
				temp.data = new char[temp.data_size];
				
				convert(image, temp);
				
				bool res = saveImage2d(output, temp);
				
				delete []temp.data;
				return res;
			}
			
			BitmapFileHeader fheader;
			BitmapInfoHeader iheader;
			fheader.type = BMP_MAGIC;
			fheader.reserved1 = fheader.reserved2 = 0;
			fheader.off_bits = BITMAP_FILE_HEADER_SIZE + BITMAP_INFO_HEADER_SIZE;
			fheader.size = fheader.off_bits + image.data_size;
			
			iheader.size = BITMAP_INFO_HEADER_SIZE;
			iheader.width = image.width;
			iheader.height = image.height;
			iheader.planes = 1;
			iheader.bit_count = getPFDescription(image.pixel_format)->bits;
			iheader.compression = 0;
			iheader.size_image = 0;
			iheader.xpels_per_meter = 0;
			iheader.ypels_per_meter = 0;
			iheader.clr_used = 0;
			iheader.clr_important = 0;
			
			output << fheader << iheader;
			
			int row_len = image.row_size_in_bytes;
			for (int i = image.height; i --> 0;)
			{
				if (output.write(image.data + i*row_len, row_len) != row_len)
					return false;
			}
			
			return true;
		}
	}
}
