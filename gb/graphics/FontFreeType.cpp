
#include "FontFreeType.h"
#include <gb/fs/Helpers.h>
#include <gb/base/Logger.h>

#include <ft2build.h>

#include FT_FREETYPE_H
#include FT_GLYPH_H

namespace
{
                       
	#undef __FTERRORS_H__
	#define FT_ERRORDEF( e, v, s )  { e, s },
	#define FT_ERROR_START_LIST     {
	#define FT_ERROR_END_LIST       { 0, 0 } };

	const struct
	{                                                        
		int          err_code;
		const char*  err_msg;
	} ft_errors[] =
	#include FT_ERRORS_H
	
	class FontImpl : public gb::graphics2d::Font
	{
	public:
		FontImpl(FT_Face face_)
		{
			face = face_;
			info.font_name = face->family_name;
			info.height = face->height;
		}
		
		bool getGlyph(wctype_t ch, FT_Glyph &glyph)
		{
			FT_UInt glyph_index = FT_Get_Char_Index(face, (FT_ULong) ch);
			
			if (!glyph_index)
				return false;
			
			FT_Error error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
			if (error)
			{
				ERROR_LOG(ft_errors[error].err_msg);
				return false;
			}
			
			error = FT_Get_Glyph(face->glyph, &glyph);
			if (error)
			{
				ERROR_LOG(ft_errors[error].err_msg);
				return false;
			}
			return true;
		}
		
		bool getGlyphInfo(wchar_t ch, GlyphInfo &out)
		{
			FT_Glyph glyph = NULL;
			
			if (!getGlyph(ch, glyph))
				return false;
			
			FT_BBox bbox;
			FT_Glyph_Get_CBox(glyph, FT_GLYPH_BBOX_PIXELS, &bbox);
  
			out.width = bbox.xMax - bbox.xMin;
			out.height = bbox.yMax - bbox.yMin;
			out.advance = face->glyph->advance.x;
			out.origin = gb::math::ivec2(face->glyph->metrics.horiBearingX, face->glyph->metrics.horiBearingY);
			
			FT_Done_Glyph(glyph);
			return true;
		}
		
		bool render(wchar_t ch, gb::containers::Image &image, int subpixel_offset = 0)
		{
			bool result = false;
			
			FT_Glyph glyph = NULL;
			
			if (!getGlyph(ch, glyph))
				return false;
			
			FT_Vector origin;
			origin.x = subpixel_offset;
			origin.y = 0;
			
			FT_Error error = FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, &origin, 1);
			
			FT_BitmapGlyphRec *new_glyph = reinterpret_cast<FT_BitmapGlyphRec *>(glyph);
			gb::containers::Image im;
			im.width = new_glyph->bitmap.width;
			im.height = new_glyph->bitmap.rows;
			
			if (new_glyph->bitmap.pixel_mode == FT_PIXEL_MODE_GRAY)
				im.pixel_format = gb::containers::ePixelFormat::GRAYSCALE8;
			else if (new_glyph->bitmap.pixel_mode == FT_PIXEL_MODE_LCD)
				im.pixel_format = gb::containers::ePixelFormat::RGB_888;
			else goto at_error;
			
			im.calculateDataSize();
			im.pitch = new_glyph->bitmap.pitch;
			im.data = reinterpret_cast<char *>(new_glyph->bitmap.buffer);
			
			gb::containers::convert(im, image);
			
			result = true;
			
		at_error:
			if (glyph)
				FT_Done_Glyph(glyph);
			return result;
		}
		
		int kerning(wchar_t left, wchar_t right)
		{
			FT_UInt glyph_index_left = FT_Get_Char_Index(face, (FT_ULong) left);
			if (!glyph_index_left)
				return 0;
			
			FT_UInt glyph_index_right = FT_Get_Char_Index(face, (FT_ULong) right);
			if (!glyph_index_right)
				return 0;
			
			FT_Vector kerning;
			FT_Error error = FT_Get_Kerning(face, glyph_index_left, glyph_index_right, FT_KERNING_DEFAULT, &kerning);
			if (error)
			{
				ERROR_LOG(ft_errors[error].err_msg);
				return 0;
			}
			
			return kerning.x;
		}
		
		const FontInfo *getFontInfo() const
		{
			return &info;
		}
		
	private:
		FT_Face face;
		FontInfo info;
	};
}

namespace gb
{
	namespace graphics2d
	{
		
		class FontFreeType::FontFreeTypeImpl
		{
		public:
			FontFreeTypeImpl()
			{
				library = NULL;
			}
			
			~FontFreeTypeImpl()
			{
				if (library)
				{
					FT_Done_FreeType(library);
				}
			}
			
			bool init()
			{
				FT_Error error = FT_Init_FreeType( &library );
				if (error)
				{
					ERROR_LOG(ft_errors[error].err_msg);
					return false;
				}
				
				return true;
			}
			
			Font *create(fs::InputStream &input, int height, int width)
			{
				fs::readEntireFile(input, face_data);
				
				FT_Face face = NULL;
				FT_Error error = FT_New_Memory_Face(library, (const FT_Byte *) face_data.c_str(), face_data.size(), 0, &face);
				
				if (error)
				{
					ERROR_LOG(ft_errors[error].err_msg);
					goto at_error;
				}
				
				error = FT_Set_Char_Size(face, width, height, 96, 96);
				
				if (error)
				{
					ERROR_LOG(ft_errors[error].err_msg);
					goto at_error;
				}
			
				return new FontImpl(face);
				
			at_error:
				face_data.clear();
				
				if (face)
					FT_Done_Face(face);
				
				return NULL;
			}
			
		private:
			FT_Library library;
			std::string face_data;
		};
		
		
		FontFreeType::FontFreeType()
		{
			pimpl = new FontFreeTypeImpl;
		}
		
		FontFreeType::~FontFreeType()
		{
			delete pimpl;
		}
		
		bool FontFreeType::init()
		{
			return pimpl->init();
		}
		
		Font *FontFreeType::create(fs::InputStream &input, int height, int width)
		{
			return pimpl->create(input, height, width);
		}
	}
}
