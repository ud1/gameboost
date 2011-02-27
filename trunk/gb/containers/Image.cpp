#include "Image.h"
#include <gb/containers/PixelFormat.h>

namespace
{
	using namespace gb::containers;
	using namespace gb::colors;
	
	// Создаем массив преобразований из одного формата пикселя в другой
	
	typedef void (*F) (const Image &from, Image &to);
	
	template<int cnt, int from, int to>
	struct conv_array : public conv_array<cnt, from, to - 1>
	{
		F f;
		conv_array()
		{
			f = &convert<from, to>;
		}
	};

	template<int cnt, int from>
	struct conv_array<cnt, from, 0> : public conv_array<cnt, from - 1, cnt>
	{
		F f;
		conv_array()
		{
			f = &convert<from, 0>;
		}
	};

	template<int cnt>
	struct conv_array<cnt, 0, 0>
	{
		F f;
		conv_array()
		{
			f = &convert<0, 0>;
		}
	};

	template<int cnt>
	struct conv_caller
	{
		F f[cnt*cnt];
		conv_caller()
		{
			new (reinterpret_cast<conv_array<cnt-1, cnt-1, cnt-1>*>(f)) conv_array<cnt-1, cnt-1, cnt-1>;
		}
		
		void call(const Image &im_from, Image &im_to)
		{
			f[im_from.pixel_format*cnt + im_to.pixel_format](im_from, im_to);
		}
	};
	
	conv_caller<ePixelFormat::COUNT> ConvCaller;
	
	// ------------------------------------------
	template <typename L, typename R>
	void copyImageData(L *l, R *r, int width, int height, int l_row_len, int r_row_len)
	{
		for (int i = 0; i < height; ++i)
		{
			L *l_row = reinterpret_cast<L *>(reinterpret_cast<char *>(l) + l_row_len * i);
			R *r_row = reinterpret_cast<R *>(reinterpret_cast<char *>(r) + r_row_len * i);
			for (int j = 0; j < width; ++j)
				copyPixel(l_row[j], r_row[j]);
		}
	}
	
	template <typename L, typename R>
	void copyImageData(const Image &from, Image &to)
	{
		L *f = reinterpret_cast<L *>(from.data);
		R *t = reinterpret_cast<R *>(to.data);
		copyImageData(t, f, from.width, from.height, to.row_size_in_bytes, from.row_size_in_bytes);
	}
}

namespace gb
{
	namespace containers
	{
		using namespace colors;

		// Специализация для базовых трансформаций
#include "colorConvert.h"
		
		// --------------------------------------------
		
		void convert(const Image &from, Image &to)
		{
			ConvCaller.call(from, to);
		}
		
		void AutoImage::copyFrom(const Image &o, ePixelFormat::PixelFormat pf)
		{
			width = o.width;
			height = o.height;
			pixel_format = pf;
			if (data)
				delete []data;
			calculateDataSize();
			data = new char[data_size];
			convert(o, *this);
		}
		
		bool AutoImage::load(loaders::ImageLoader &loader, fs::InputStream &input)
		{
			if (data)
				delete []data;
			data = NULL;
			
			if (!loader.loadImageHeader(input, *this))
				return false;
			
			data = new char[data_size];
			
			return loader.loadImage(input, *this);
		}
		
		bool AutoImage::save(loaders::ImageLoader &loader, fs::OutputStream &output)
		{
			if (!data)
				return false;
			
			return loader.saveImage(output, *this);
		}
	}
}