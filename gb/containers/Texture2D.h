/*      \file FileStream.cpp
 *      \author -Eugene-, kozlov_eugene@list.ru
*/
#pragma once
#include "gb/base/Types.h"
#include "gb/containers/IResource.h"

namespace gb
{
    namespace containers
    {
        /*
         * ������ �������. ������������ �� ������ ��� ��������, � ��� �����, ��� ���� 
         * ����������; ��������, ����� ������� � ������ ����.
         */
        namespace eTexturePixelFmt
        {
            enum 
            {
                UNKNOWN = 0x0000,
                DXT1    = 0x0001,
                DXT3    = 0x0002,
                DXT5    = 0x0003
            };
        };
        /*
         * GAPI-����������� ��������.
         * 
         * �����������: ������ � ������ ��� � ������(�� gb::io::MemoryStream) - 
         * �������� ������ ������, � num_bytes, row_bytes, num_rows - ����������� 
         * �� ������ ������� ������ � ������� ��������.
         */
        typedef class Texture2D : public gb::containers::IResource
        {
        protected:
            int	    width;
            int	    height;
            int 	format;
            int 	components;
            size_t *row_bytes;
            size_t *num_rows;
        protected:
            virtual bool isExist();
        public:
            Texture2D();
            virtual ~Texture2D();
            virtual bool init(const int width, const int height, const int format, const int components, const int mipmaps);

            int     getWidth()              { return width;       };
            int     getHeight()             { return height;      };
            int     getFormat()             { return format;      };
            int     getComponents()         { return components;  };
            size_t  getMipmapsCount()       { return groups_count;};
	    } CTexture2D;

        char textureGetBitsPerPixel(int pf);
        char textureGetComponentsCount(int pf);
    };
};