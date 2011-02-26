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
				rbits = 8,
				gbits = 8,
				bbits = 8,
				abits = 0,
			};
			typedef unsigned char value_type;
			value_type r, g, b;
			
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
				rbits = 8,
				gbits = 8,
				bbits = 8,
				abits = 8,
			};
			typedef unsigned char value_type;
			value_type r, g, b, a;
			
			void set_zero()
			{
				r = 0;
				g = 0;
				b = 0;
				a = (1 << abits) - 1;
			}
		};
		
		struct bgr
		{
			enum
			{
				components = 3,
				pixel_format = containers::ePixelFormat::BGR_888,
				rbits = 8,
				gbits = 8,
				bbits = 8,
				abits = 0,
			};
			typedef unsigned char value_type;
			value_type b, g, r;
			
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
				rbits = 8,
				gbits = 8,
				bbits = 8,
				abits = 8,
			};
			typedef unsigned char value_type;
			value_type b, g, r, a;
			
			void set_zero()
			{
				r = 0;
				g = 0;
				b = 0;
				a = (1 << abits) - 1;
			}
		};
		
		struct r_8
		{
			enum
			{
				components = 1,
				pixel_format = containers::ePixelFormat::R_8,
				rbits = 8,
				gbits = 0,
				bbits = 0,
				abits = 0,
			};
			typedef unsigned char value_type;
			value_type r;
			
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
				rbits = 8,
				gbits = 8,
				bbits = 0,
				abits = 0,
			};
			typedef unsigned value_type;
			value_type r, g;
			
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
				rbits = 3,
				gbits = 3,
				bbits = 2,
				abits = 0,
			};
			typedef unsigned value_type;
			value_type r : rbits;
			value_type g : gbits;
			value_type b : bbits;
			
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
				rbits = 2,
				gbits = 3,
				bbits = 3,
				abits = 0,
			};
			typedef unsigned char value_type;
			value_type r : rbits;
			value_type g : gbits;
			value_type b : bbits;
			
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
				rbits = 5,
				gbits = 6,
				bbits = 5,
				abits = 0,
			};
			typedef unsigned char value_type;
			value_type r : rbits;
			value_type g : gbits;
			value_type b : bbits;
			
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
				rbits = 4,
				gbits = 4,
				bbits = 4,
				abits = 4,
			};
			typedef unsigned char value_type;
			value_type r : rbits;
			value_type g : gbits;
			value_type b : bbits;
			value_type a : abits;
			
			void set_zero()
			{
				r = 0;
				g = 0;
				b = 0;
				a = (1 << abits) - 1;
			}
		};
		
		struct rgba_5551
		{
			enum
			{
				components = 4,
				pixel_format = containers::ePixelFormat::RGBA_5551,
				rbits = 5,
				gbits = 5,
				bbits = 5,
				abits = 1,
			};
			typedef unsigned char value_type;
			value_type r : rbits;
			value_type g : gbits;
			value_type b : bbits;
			value_type a : abits;
			
			void set_zero()
			{
				r = 0;
				g = 0;
				b = 0;
				a = (1 << abits) - 1;
			}
		};
		
		struct rgba_10_10_10_2
		{
			enum
			{
				components = 4,
				pixel_format = containers::ePixelFormat::RGBA_10_10_10_2,
				rbits = 10,
				gbits = 10,
				bbits = 10,
				abits = 2,
			};
			typedef unsigned short value_type;
			value_type r : 10;
			value_type g : 10;
			value_type b : 10;
			value_type a : 2;
			
			void set_zero()
			{
				r = 0;
				g = 0;
				b = 0;
				a = (1 << abits) - 1;
			}
		};
		
		struct fr
		{
			enum
			{
				components = 1,
				pixel_format = containers::ePixelFormat::FR,
				rbits = 8*sizeof(float),
				gbits = 0,
				bbits = 0,
				abits = 0,
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
				rbits = 8*sizeof(float),
				gbits = 8*sizeof(float),
				bbits = 0,
				abits = 0,
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
				rbits = 8*sizeof(float),
				gbits = 8*sizeof(float),
				bbits = 8*sizeof(float),
				abits = 0,
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
				rbits = 8*sizeof(float),
				gbits = 8*sizeof(float),
				bbits = 8*sizeof(float),
				abits = 8*sizeof(float),
			};
			typedef float value_type;
			float r, g, b, a;
			
			void set_zero()
			{
				r = g = b = 0.0f;
				a = 1.0f;
			}
		};
		
		namespace details
		{
			template <int s, bool positive_s, typename T>
			struct signedShift;
			
			template <int s, typename T>
			struct signedShift<s, true, T>
			{
				T leftShift(T t)
				{
					return t << s;
				}
			};
			
			template <int s, typename T>
			struct signedShift<s, false, T>
			{
				T leftShift(T t)
				{
					return t >> -s;
				}
			};
			
			template<int ls, int rs, typename L, typename R>
			struct convertColorComponent
			{
				L operator()(R r)
				{
					return signedShift<ls - rs, ((ls - rs) > 0), R>().leftShift(r);
				}
			};
			
			template<>
			struct convertColorComponent<8*sizeof(float), 8*sizeof(float), float, float>
			{
				float operator()(float r)
				{
					return r;
				}
			};
			
			template<int ls, typename L>
			struct convertColorComponent<ls, 8*sizeof(float), L, float>
			{
				L operator()(float r)
				{
					return (L) (r * ((1 << ls) - 1));
				}
			};
			
			template<int rs, typename R>
			struct convertColorComponent<8*sizeof(float), rs, float, R>
			{
				float operator()(R r)
				{
					return (float) r / (float) ((1 << rs) - 1);
				}
			};
			
			
			template <int lc, int rc, bool lc_less_rc, typename L, typename R>
			struct copy;
			
			template <int lc, typename L, typename R>
			struct copy<lc, 1, false, L, R>
			{
				L &operator()(L &l, const R &r)
				{
					l.set_zero();
					l.r = convertColorComponent<L::rbits, R::rbits, typename L::value_type, typename R::value_type>()(r.r);
					return l;
				}
			};
			
			template <int lc, typename L, typename R>
			struct copy<lc, 2, false, L, R>
			{
				L &operator()(L &l, const R &r)
				{
					l.set_zero();
					l.r = convertColorComponent<L::rbits, R::rbits, typename L::value_type, typename R::value_type>()(r.r);
					l.g = convertColorComponent<L::gbits, R::gbits, typename L::value_type, typename R::value_type>()(r.g);
					return l;
				}
			};
			
			template <int lc, typename L, typename R>
			struct copy<lc, 3, false, L, R>
			{
				L &operator()(L &l, const R &r)
				{
					l.set_zero();
					l.r = convertColorComponent<L::rbits, R::rbits, typename L::value_type, typename R::value_type>()(r.r);
					l.g = convertColorComponent<L::gbits, R::gbits, typename L::value_type, typename R::value_type>()(r.g);
					l.b = convertColorComponent<L::bbits, R::bbits, typename L::value_type, typename R::value_type>()(r.b);
					return l;
				}
			};
			
			template <int lc, typename L, typename R>
			struct copy<lc, 4, false, L, R>
			{
				L &operator()(L &l, const R &r)
				{
					l.r = convertColorComponent<L::rbits, R::rbits, typename L::value_type, typename R::value_type>()(r.r);
					l.g = convertColorComponent<L::gbits, R::gbits, typename L::value_type, typename R::value_type>()(r.g);
					l.b = convertColorComponent<L::bbits, R::bbits, typename L::value_type, typename R::value_type>()(r.b);
					l.a = convertColorComponent<L::abits, R::abits, typename L::value_type, typename R::value_type>()(r.a);
					return l;
				}
			};
			
			template <int rc, typename L, typename R>
			struct copy<1, rc, true, L, R>
			{
				L &operator()(L &l, const R &r)
				{
					l.r = convertColorComponent<L::rbits, R::rbits, typename L::value_type, typename R::value_type>()(r.r);
					return l;
				}
			};
			
			template <int rc, typename L, typename R>
			struct copy<2, rc, true, L, R>
			{
				L &operator()(L &l, const R &r)
				{
					l.r = convertColorComponent<L::rbits, R::rbits, typename L::value_type, typename R::value_type>()(r.r);
					l.g = convertColorComponent<L::gbits, R::gbits, typename L::value_type, typename R::value_type>()(r.g);
					return l;
				}
			};
			
			template <int rc, typename L, typename R>
			struct copy<3, rc, true, L, R>
			{
				L &operator()(L &l, const R &r)
				{
					l.r = convertColorComponent<L::rbits, R::rbits, typename L::value_type, typename R::value_type>()(r.r);
					l.g = convertColorComponent<L::gbits, R::gbits, typename L::value_type, typename R::value_type>()(r.g);
					l.b = convertColorComponent<L::bbits, R::bbits, typename L::value_type, typename R::value_type>()(r.b);
					return l;
				}
			};
			
			template <int rc, typename L, typename R>
			struct copy<4, rc, true, L, R>
			{
				L &operator()(L &l, const R &r)
				{
					l.r = convertColorComponent<L::rbits, R::rbits, typename L::value_type, typename R::value_type>()(r.r);
					l.g = convertColorComponent<L::gbits, R::gbits, typename L::value_type, typename R::value_type>()(r.g);
					l.b = convertColorComponent<L::bbits, R::bbits, typename L::value_type, typename R::value_type>()(r.b);
					l.a = convertColorComponent<L::abits, R::abits, typename L::value_type, typename R::value_type>()(r.a);
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
