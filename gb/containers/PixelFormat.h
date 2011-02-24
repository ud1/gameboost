/**	\file  PixelFormat.h
 *	\author ud1 (ud1@mail.ru)
*/

#pragma once

namespace gb
{
	namespace containers
	{
		namespace ePixelFormat
		{
			enum PixelFormat
			{
				RGB_888,
				BGR_888,
				RGBA_8888,
				BGRA_8888,
				
				R_8,
				RG_88,
				
				RGB_332,
				RGB_233,
				RGB_565,
				
				RGBA_4444,
				RGBA_5551,
				RGBA_10_10_10_2,
				
				FR,
				FRG,
				FRGB,
				FRGBA,
				
				MAX_UNCOMPRESSED_FORMAT = FRGBA,
				
				COUNT
			};
		}
		
		struct PixelFormatDescription
		{
			const char *name;
			int bits;
			int red_bits;
			int green_bits;
			int blue_bits;
			int alpha_bits;
			int components;
			bool is_compressed;
			bool floationg_point;
		};
		
		const PixelFormatDescription *getPFDescription(ePixelFormat::PixelFormat f);
	}
	
	namespace colors
	{
		struct rgb
		{
			enum
			{
				components = 3,
				pixel_format = containers::ePixelFormat::RGB_888,
			};
			typedef char value_type;
			char r, g, b;
			
			void set_zero()
			{
				r = 0;
				g = 0;
				b = 0;
			}
		};
		
		struct rgba
		{
			enum
			{
				components = 4,
				pixel_format = containers::ePixelFormat::RGBA_8888,
			};
			typedef char value_type;
			char r, g, b, a;
			
			void set_zero()
			{
				r = 0;
				g = 0;
				b = 0;
				a = 0;
			}
		};
		
		struct bgr
		{
			enum
			{
				components = 3,
				pixel_format = containers::ePixelFormat::BGR_888,
			};
			typedef char value_type;
			char b, g, r;
			
			void set_zero()
			{
				r = 0;
				g = 0;
				b = 0;
			}
		};
		
		struct bgra
		{
			enum
			{
				components = 4,
				pixel_format = containers::ePixelFormat::BGRA_8888,
			};
			typedef char value_type;
			char b, g, r, a;
			
			void set_zero()
			{
				r = 0;
				g = 0;
				b = 0;
				a = 0;
			}
		};
		
		struct r_8
		{
			enum
			{
				components = 1,
				pixel_format = containers::ePixelFormat::R_8,
			};
			typedef char value_type;
			char r;
			
			void set_zero()
			{
				r = 0;
			}
		};
		
		struct rg_88
		{
			enum
			{
				components = 2,
				pixel_format = containers::ePixelFormat::RG_88,
			};
			typedef char value_type;
			char r, g;
			
			void set_zero()
			{
				r = 0;
				g = 0;
			}
		};
		
		struct rgb_332
		{
			enum
			{
				components = 3,
				pixel_format = containers::ePixelFormat::RGB_332,
			};
			typedef char value_type;
			char r : 3;
			char g : 3;
			char b : 2;
			
			void set_zero()
			{
				r = 0;
				g = 0;
				b = 0;
			}
		};
		
		struct rgb_233
		{
			enum
			{
				components = 3,
				pixel_format = containers::ePixelFormat::RGB_233,
			};
			typedef char value_type;
			char r : 2;
			char g : 3;
			char b : 3;
			
			void set_zero()
			{
				r = 0;
				g = 0;
				b = 0;
			}
		};
		
		struct rgb_565
		{
			enum
			{
				components = 3,
				pixel_format = containers::ePixelFormat::RGB_565,
			};
			typedef char value_type;
			char r : 5;
			char g : 6;
			char b : 5;
			
			void set_zero()
			{
				r = 0;
				g = 0;
				b = 0;
			}
		};
		
		struct rgba_4444
		{
			enum
			{
				components = 4,
				pixel_format = containers::ePixelFormat::RGBA_4444,
			};
			typedef char value_type;
			char r : 4;
			char g : 4;
			char b : 4;
			char a : 4;
			
			void set_zero()
			{
				r = 0;
				g = 0;
				b = 0;
				a = 0;
			}
		};
		
		struct rgba_5551
		{
			enum
			{
				components = 4,
				pixel_format = containers::ePixelFormat::RGBA_5551,
			};
			typedef char value_type;
			char r : 5;
			char g : 5;
			char b : 5;
			char a : 1;
			
			void set_zero()
			{
				r = 0;
				g = 0;
				b = 0;
				a = 0;
			}
		};
		
		struct rgba_10_10_10_2
		{
			enum
			{
				components = 4,
				pixel_format = containers::ePixelFormat::RGBA_10_10_10_2,
			};
			typedef short value_type;
			short r : 10;
			short g : 10;
			short b : 10;
			short a : 2;
			
			void set_zero()
			{
				r = 0;
				g = 0;
				b = 0;
				a = 0;
			}
		};
		
		struct fr
		{
			enum
			{
				components = 1,
				pixel_format = containers::ePixelFormat::FR,
			};
			typedef float value_type;
			float r;
			
			void set_zero()
			{
				r = 0.0f;
			}
		};
		
		struct frg
		{
			enum
			{
				components = 2,
				pixel_format = containers::ePixelFormat::FRG,
			};
			typedef float value_type;
			float r, g;
			
			void set_zero()
			{
				r = g = 0.0f;
			}
		};
		
		struct frgb
		{
			enum
			{
				components = 3,
				pixel_format = containers::ePixelFormat::FRGB,
			};
			typedef float value_type;
			float r, g, b;
			
			void set_zero()
			{
				r = g = b = 0.0f;
			}
		};
		
		struct frgba
		{
			enum
			{
				components = 4,
				pixel_format = containers::ePixelFormat::FRGBA,
			};
			typedef float value_type;
			float r, g, b, a;
			
			void set_zero()
			{
				r = g = b = a = 0.0f;
			}
		};
		
		namespace details
		{
			template <int lc, int rc, bool lc_less_rc, typename L, typename R>
			struct copy;
			
			template <int lc, typename L, typename R>
			struct copy<lc, 1, false, L, R>
			{
				L &operator()(L &l, const R &r)
				{
					l.set_zero();
					l.r = (typename L::value_type) r.r;
					return l;
				}
			};
			
			template <int lc, typename L, typename R>
			struct copy<lc, 2, false, L, R>
			{
				L &operator()(L &l, const R &r)
				{
					l.set_zero();
					l.r = (typename L::value_type) r.r;
					l.g = (typename L::value_type) r.g;
					return l;
				}
			};
			
			template <int lc, typename L, typename R>
			struct copy<lc, 3, false, L, R>
			{
				L &operator()(L &l, const R &r)
				{
					l.set_zero();
					l.r = (typename L::value_type) r.r;
					l.g = (typename L::value_type) r.g;
					l.b = (typename L::value_type) r.b;
					return l;
				}
			};
			
			template <int lc, typename L, typename R>
			struct copy<lc, 4, false, L, R>
			{
				L &operator()(L &l, const R &r)
				{
					l.r = (typename L::value_type) r.r;
					l.g = (typename L::value_type) r.g;
					l.b = (typename L::value_type) r.b;
					l.a = (typename L::value_type) r.a;
					return l;
				}
			};
			
			template <int rc, typename L, typename R>
			struct copy<1, rc, true, L, R>
			{
				L &operator()(L &l, const R &r)
				{
					l.r = (typename L::value_type) r.r;
					return l;
				}
			};
			
			template <int rc, typename L, typename R>
			struct copy<2, rc, true, L, R>
			{
				L &operator()(L &l, const R &r)
				{
					l.r = (typename L::value_type) r.r;
					l.g = (typename L::value_type) r.g;
					return l;
				}
			};
			
			template <int rc, typename L, typename R>
			struct copy<3, rc, true, L, R>
			{
				L &operator()(L &l, const R &r)
				{
					l.r = (typename L::value_type) r.r;
					l.g = (typename L::value_type) r.g;
					l.b = (typename L::value_type) r.b;
					return l;
				}
			};
			
			template <int rc, typename L, typename R>
			struct copy<4, rc, true, L, R>
			{
				L &operator()(L &l, const R &r)
				{
					l.r = (typename L::value_type) r.r;
					l.g = (typename L::value_type) r.g;
					l.b = (typename L::value_type) r.b;
					l.a = (typename L::value_type) r.a;
					return l;
				}
			};
		}
		
		template <typename L, typename R>
		L &copyPixel(L &l, const R &r)
		{
			return details::copy<L::components, R::components, (L::components < R::components), L, R>()(l, r);
		}
		
		template <int PF>
		struct color_type;
		
		template <>
		struct color_type<containers::ePixelFormat::RGB_888>
		{
			typedef rgb value_type;
		};
		
		template <>
		struct color_type<containers::ePixelFormat::RGBA_8888>
		{
			typedef rgba value_type;
		};
		
		template <>
		struct color_type<containers::ePixelFormat::BGR_888>
		{
			typedef bgr value_type;
		};
		
		template <>
		struct color_type<containers::ePixelFormat::BGRA_8888>
		{
			typedef bgra value_type;
		};
		
		template <>
		struct color_type<containers::ePixelFormat::R_8>
		{
			typedef r_8 value_type;
		};
		
		template <>
		struct color_type<containers::ePixelFormat::RG_88>
		{
			typedef rg_88 value_type;
		};
		
		template <>
		struct color_type<containers::ePixelFormat::RGB_332>
		{
			typedef rgb_332 value_type;
		};
		
		template <>
		struct color_type<containers::ePixelFormat::RGB_233>
		{
			typedef rgb_233 value_type;
		};
		
		template <>
		struct color_type<containers::ePixelFormat::RGB_565>
		{
			typedef rgb_565 value_type;
		};
		
		template <>
		struct color_type<containers::ePixelFormat::RGBA_4444>
		{
			typedef rgba_4444 value_type;
		};
		
		template <>
		struct color_type<containers::ePixelFormat::RGBA_5551>
		{
			typedef rgba_5551 value_type;
		};
		
		template <>
		struct color_type<containers::ePixelFormat::RGBA_10_10_10_2>
		{
			typedef rgba_10_10_10_2 value_type;
		};
		
		template <>
		struct color_type<containers::ePixelFormat::FR>
		{
			typedef fr value_type;
		};
		
		template <>
		struct color_type<containers::ePixelFormat::FRG>
		{
			typedef frg value_type;
		};
		
		template <>
		struct color_type<containers::ePixelFormat::FRGB>
		{
			typedef frgb value_type;
		};
		
		template <>
		struct color_type<containers::ePixelFormat::FRGBA>
		{
			typedef frgba value_type;
		};
	}
}
