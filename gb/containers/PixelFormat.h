/**	\file  PixelFormat.h
 *	\author ud1 (ud1@mail.ru)
*/

#include <gb/base/Types.h>
#include <cstdlib>

#pragma once

namespace gb
{
	namespace containers
	{
		namespace ePixelFormat
		{
			/** \brief Форматы пиксела для изображений */
			enum PixelFormat
			{
				R_8,
				RGB_888,
				RGBA_8888,
				RGBA_16_16_16_16,
				
				BGR_888,
				BGRA_8888,
				
				RGB_332,
				RGB_565,
				
				RGBA_4444,
				RGBA_5551,
				RGBA_10_10_10_2,
				
				GRAYSCALE8,
				GRAYSCALE16,
				FGRAYSCALE,
				
				FR,
				FRGB,
				FRGBA,
				
				MAX_UNCOMPRESSED_FORMAT = FRGBA,
				
				COUNT
			};
		}
		
		/** \brief Описание формата пиксела для изображений */
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
		
		/** Возвращает описание формата пиксела по его коду */
		const PixelFormatDescription *getPFDescription(ePixelFormat::PixelFormat f);
	}
	
	namespace colors
	{
		/// @cond include_details
		namespace details
		{
			enum ColorType
			{
				RGBA_LIKE_TYPE,
				GRAYSCALE_TYPE,
			};
			
			template <typename ColorComponent>
			struct ColorComponentTraits;
			
			template <>
			struct ColorComponentTraits<uint8_t>
			{
				static uint8_t min_val() {return 0;}
				static uint8_t max_val() {return 255;}
			};
			
			template <>
			struct ColorComponentTraits<uint16_t>
			{
				static uint16_t min_val() {return 0;}
				static uint16_t max_val() {return 65535;}
			};
			
			template <>
			struct ColorComponentTraits<float>
			{
				static float min_val() {return 0.0f;}
				static float max_val() {return 1.0f;}
			};
			
			template <typename Type, containers::ePixelFormat::PixelFormat pf, size_t components_n>
			struct base_rgba_like_type
			{
				enum
				{
					components = components_n,
					pixel_format = pf,
					type = RGBA_LIKE_TYPE,
					rbits = components > 0 ? 8*sizeof(Type) : 0,
					gbits = components > 1 ? 8*sizeof(Type) : 0,
					bbits = components > 2 ? 8*sizeof(Type) : 0,
					abits = components > 3 ? 8*sizeof(Type) : 0,
				};
			};
			
			template <typename Type, containers::ePixelFormat::PixelFormat pf>
			struct r_type : public base_rgba_like_type<Type, pf, 1>
			{
				typedef Type value_type;
				value_type r;
				
				void set_zero()
				{
					r = ColorComponentTraits<Type>::min_val();
				}
			};
			
			template <typename Type, containers::ePixelFormat::PixelFormat pf>
			struct rg_type : public base_rgba_like_type<Type, pf, 2>
			{
				typedef Type value_type;
				value_type r, g;
				
				void set_zero()
				{
					r = g = ColorComponentTraits<Type>::min_val();
				}
			};
			
			template <typename Type, containers::ePixelFormat::PixelFormat pf>
			struct rgb_type : public base_rgba_like_type<Type, pf, 3>
			{
				typedef Type value_type;
				value_type r, g, b;
				
				void set_zero()
				{
					r = g = b = ColorComponentTraits<Type>::min_val();
				}
			};
			
			template <typename Type, containers::ePixelFormat::PixelFormat pf>
			struct rgba_type : public base_rgba_like_type<Type, pf, 4>
			{
				typedef Type value_type;
				value_type r, g, b, a;
				
				void set_zero()
				{
					r = g = b = ColorComponentTraits<Type>::min_val();
					a = ColorComponentTraits<Type>::max_val();
				}
			};
		}
		/// @endcond
		
		struct r_8 : public details::r_type<uint8_t, containers::ePixelFormat::R_8> {};
		struct rgb : public details::rgb_type<uint8_t, containers::ePixelFormat::RGB_888> {};
		struct rgba : public details::rgba_type<uint8_t, containers::ePixelFormat::RGBA_8888> {};
		struct rgba_16_16_16_16 : public details::rgba_type<uint16_t, containers::ePixelFormat::RGBA_16_16_16_16> {};
		struct fr : public details::r_type<float, containers::ePixelFormat::FR> {};
		struct frgb : public details::rgb_type<float, containers::ePixelFormat::FRGB> {};
		struct frgba : public details::rgba_type<float, containers::ePixelFormat::FRGBA> {};
		
		struct bgr
		{
			enum
			{
				components = 3,
				pixel_format = containers::ePixelFormat::BGR_888,
				type = details::RGBA_LIKE_TYPE,
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
				type = details::RGBA_LIKE_TYPE,
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
		
		/// @cond include_details
		namespace details
		{
			template <typename Type, containers::ePixelFormat::PixelFormat pf, size_t rb, size_t gb, size_t bb>
			struct base_rgb_bit_field_type
			{
				enum
				{
					components = 3,
					pixel_format = pf,
					type = RGBA_LIKE_TYPE,
					rbits = rb,
					gbits = gb,
					bbits = bb,
					abits = 0,
				};
				typedef Type value_type;
				value_type r : rb;
				value_type g : gb;
				value_type b : bb;
				void set_zero()
				{
					r = g = b = 0;
				}
			};
		}
		/// @endcond
		
		struct rgb_332 : public details::base_rgb_bit_field_type<uint8_t, containers::ePixelFormat::RGB_332, 3, 3, 2> {};
		struct rgb_565 : public details::base_rgb_bit_field_type<uint8_t, containers::ePixelFormat::RGB_565, 5, 6, 5> {};

		/// @cond include_details
		namespace details
		{
			template <typename Type, containers::ePixelFormat::PixelFormat pf, size_t rb, size_t gb, size_t bb, size_t ab>
			struct base_rgba_bit_field_type
			{
				enum
				{
					components = 3,
					pixel_format = pf,
					type = RGBA_LIKE_TYPE,
					rbits = rb,
					gbits = gb,
					bbits = bb,
					abits = ab,
				};
				typedef Type value_type;
				value_type r : rb;
				value_type g : gb;
				value_type b : bb;
				value_type a : ab;
				void set_zero()
				{
					r = g = b = 0;
					a = (1 << abits) - 1;
				}
			};
		}
		/// @endcond
		
		struct rgba_4444 : public details::base_rgba_bit_field_type<uint8_t, containers::ePixelFormat::RGBA_4444, 4, 4, 4, 4> {};
		struct rgba_5551 : public details::base_rgba_bit_field_type<uint8_t, containers::ePixelFormat::RGBA_5551, 5, 5, 5, 1> {};
		struct rgba_10_10_10_2 : public details::base_rgba_bit_field_type<uint16_t, containers::ePixelFormat::RGBA_10_10_10_2, 10, 10, 10, 2> {};

		/// @cond include_details
		namespace details
		{
			template <typename Type, containers::ePixelFormat::PixelFormat pf>
			struct base_graysclae_type
			{
				enum
				{
					components = 1,
					pixel_format = pf,
					type = GRAYSCALE_TYPE,
					rbits = 0,
					gbits = 0,
					bbits = 0,
					abits = 0,
				};
				typedef Type value_type;
				value_type value;
				void set_zero()
				{
					value = ColorComponentTraits<Type>::min_val;
				}
			};
		}
		/// @endcond
		
		struct grayscale8 : public details::base_graysclae_type<uint8_t, containers::ePixelFormat::GRAYSCALE8> {};
		struct grayscale16 : public details::base_graysclae_type<uint16_t, containers::ePixelFormat::GRAYSCALE16> {};
		struct fgrayscale : public details::base_graysclae_type<float, containers::ePixelFormat::FGRAYSCALE> {};
		
		/// @cond include_details
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
			
			template <typename Grayscale>
			struct GrayscaleConvertionType;
			
			template <>
			struct GrayscaleConvertionType<grayscale8>
			{
				typedef rgba RGBAType;
			};
			
			template <>
			struct GrayscaleConvertionType<grayscale16>
			{
				typedef rgba_16_16_16_16 RGBAType;
			};
			
			template <>
			struct GrayscaleConvertionType<fgrayscale>
			{
				typedef frgba RGBAType;
			};
			
			template <typename Grayscale>
			struct GrayscaleToRGBAConvertion
			{
				typedef typename GrayscaleConvertionType<Grayscale>::RGBAType RGBAType;
				RGBAType convert(Grayscale g)
				{
					RGBAType res;
					res.r = res.g = res.b = g.value;
					res.a = ColorComponentTraits<typename Grayscale::value_type>::max_val();
					return res;
				}
			};
			
			template <typename Grayscale>
			struct RGBAToGrayscaleConvertion;
			
			template <>
			struct RGBAToGrayscaleConvertion<grayscale8>
			{
				typedef GrayscaleConvertionType<grayscale8>::RGBAType RGBAType;
				grayscale8 convert(RGBAType v)
				{
					grayscale8 res;
					res.value = ((v.r*77 + v.g*150 + v.b*29)*v.a/255) >> 8;
					return res;
				}
			};
			
			template <>
			struct RGBAToGrayscaleConvertion<grayscale16>
			{
				typedef GrayscaleConvertionType<grayscale16>::RGBAType RGBAType;
				grayscale16 convert(RGBAType v)
				{
					grayscale16 res;
					res.value = (((v.r*15995 + v.g*38470 + v.b*7471) >> 16)*v.a)/65535;
					return res;
				}
			};
			
			template <>
			struct RGBAToGrayscaleConvertion<fgrayscale>
			{
				typedef GrayscaleConvertionType<fgrayscale>::RGBAType RGBAType;
				fgrayscale convert(RGBAType v)
				{
					fgrayscale res;
					res.value = (v.r*0.299f + v.g*0.587f + v.b*0.114f)*v.a;
					return res;
				}
			};
			
			template <typename L, typename R, int l_type, int r_type>
			struct copyPixel_s;
			
			template <typename L, typename R>
			struct copyPixel_s<L, R, RGBA_LIKE_TYPE, RGBA_LIKE_TYPE>
			{
				L &operator()(L &l, const R &r)
				{
					return copy<L::components, R::components, (L::components < R::components), L, R>()(l, r);
				}
			};
			
			template <typename L, typename R>
			struct copyPixel_s<L, R, GRAYSCALE_TYPE, RGBA_LIKE_TYPE>
			{
				L &operator()(L &l, const R &r)
				{
					typedef typename GrayscaleConvertionType<L>::RGBAType RGBAType;
					RGBAType temp;
					copy<RGBAType::components, R::components, (RGBAType::components < R::components), RGBAType, R>()(temp, r);
					return l = RGBAToGrayscaleConvertion<L>().convert(temp);
				}
			};
			
			template <typename L, typename R>
			struct copyPixel_s<L, R, RGBA_LIKE_TYPE, GRAYSCALE_TYPE>
			{
				L &operator()(L &l, const R &r)
				{
					typedef typename GrayscaleConvertionType<R>::RGBAType RGBAType;
					RGBAType temp;
					temp = GrayscaleToRGBAConvertion<R>().convert(r);
					return copy<L::components, RGBAType::components, (L::components < RGBAType::components), L, RGBAType>()(l, temp);
				}
			};
			
			template <typename L, typename R>
			struct copyPixel_s<L, R, GRAYSCALE_TYPE, GRAYSCALE_TYPE>
			{
				L &operator()(L &l, const R &r)
				{
					typedef typename GrayscaleConvertionType<L>::RGBAType LRGBAType;
					typedef typename GrayscaleConvertionType<R>::RGBAType RRGBAType;
					LRGBAType ltemp;
					RRGBAType rtemp;
					rtemp = GrayscaleToRGBAConvertion<R>().convert(r);
					copy<LRGBAType::components, RRGBAType::components, (LRGBAType::components < RRGBAType::components), LRGBAType, RRGBAType>()(ltemp, rtemp);
					return l = RGBAToGrayscaleConvertion<L>().convert(ltemp);
				}
			};
		}
		/// @endcond
		
		template <typename L, typename R>
		L &copyPixel(L &l, const R &r)
		{
			return details::copyPixel_s<L, R, L::type, R::type>()(l, r);
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
		struct color_type<containers::ePixelFormat::RGB_332>
		{
			typedef rgb_332 value_type;
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
