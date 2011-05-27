﻿#include "d3d9pch.h"
//#include "pch.h"

#if ( defined(GB_D3D9) && defined(WIN32) )

  #include <gb/graphics/d3d9/dataconv.h>

 
  namespace gb
  {
  namespace graphics
  {
  namespace d3d9
  {
  namespace dataconv
  {
 

  //=======================================================================



  //=======================================================================
  GB_D3D9_API std::string D3DFORMAT_tostr(const D3DFORMAT format)
  {
    std::string s;


    switch (format)
    {
      case D3DFMT_UNKNOWN:
        s = "D3DFMT_UNKNOWN";
        break; //    =  0,

      case D3DFMT_R8G8B8:
        s = "D3DFMT_R8G8B8";
        break; //        = 20,
      case D3DFMT_A8R8G8B8:
        s = "D3DFMT_A8R8G8B8";
        break; //            = 21,
      case D3DFMT_X8R8G8B8:
        s = "D3DFMT_X8R8G8B8";
        break; //            = 22,
      case D3DFMT_R5G6B5:
        s = "D3DFMT_R5G6B5";
        break; //           = 23,
      case D3DFMT_X1R5G5B5:
        s = "D3DFMT_X1R5G5B5";
        break; //            = 24,
      case D3DFMT_A1R5G5B5:
        s = "D3DFMT_A1R5G5B5";
        break; //             = 25,
      case D3DFMT_A4R4G4B4:
        s = "D3DFMT_A4R4G4B4";
        break; //             = 26,
      case D3DFMT_R3G3B2:
        s = "D3DFMT_R3G3B2";
        break; //              = 27,
      case D3DFMT_A8:
        s = "D3DFMT_A8";
        break; //              = 28,
      case D3DFMT_A8R3G3B2:
        s = "D3DFMT_A8R3G3B2";
        break; //             = 29,
      case D3DFMT_X4R4G4B4:
        s = "D3DFMT_X4R4G4B4";
        break; //           = 30,
      case D3DFMT_A2B10G10R10:
        s = "D3DFMT_A2B10G10R10";
        break; //         = 31,
      case D3DFMT_A8B8G8R8:
        s = "D3DFMT_A8B8G8R8";
        break; //           = 32,
      case D3DFMT_X8B8G8R8:
        s = "D3DFMT_X8B8G8R8";
        break; //            = 33,
      case D3DFMT_G16R16:
        s = "D3DFMT_G16R16";
        break; //              = 34,
      case D3DFMT_A2R10G10B10:
        s = "D3DFMT_A2R10G10B10";
        break; //         = 35,
      case D3DFMT_A16B16G16R16:
        s = "D3DFMT_A16B16G16R16";
        break; //        = 36,

      case D3DFMT_A8P8:
        s = "D3DFMT_A8P8";
        break; //                = 40,
      case D3DFMT_P8:
        s = "D3DFMT_P8";
        break; //                  = 41,

      case D3DFMT_L8:
        s = "D3DFMT_L8";
        break; //                  = 50,
      case D3DFMT_A8L8:
        s = "D3DFMT_A8L8";
        break; //                = 51,
      case D3DFMT_A4L4:
        s = "D3DFMT_A4L4";
        break; //                = 52,

      case D3DFMT_V8U8:
        s = "D3DFMT_V8U8";
        break; //                = 60,
      case D3DFMT_L6V5U5:
        s = "D3DFMT_L6V5U5";
        break; //             = 61,
      case D3DFMT_X8L8V8U8:
        s = "D3DFMT_X8L8V8U8";
        break; //            = 62,
      case D3DFMT_Q8W8V8U8:
        s = "D3DFMT_Q8W8V8U8";
        break; //            = 63,
      case D3DFMT_V16U16:
        s = "D3DFMT_V16U16";
        break; //           = 64,
      case D3DFMT_A2W10V10U10:
        s = "D3DFMT_A2W10V10U10";
        break; //         = 67,

      case D3DFMT_UYVY:
        s = "D3DFMT_UYVY";
        break; //             = MAKEFOURCC('U', 'Y', 'V', 'Y'),
      case D3DFMT_R8G8_B8G8:
        s = "D3DFMT_R8G8_B8G8";
        break; //          = MAKEFOURCC('R', 'G', 'B', 'G'),
      case D3DFMT_YUY2:
        s = "D3DFMT_YUY2";
        break; //           = MAKEFOURCC('Y', 'U', 'Y', '2'),
      case D3DFMT_G8R8_G8B8:
        s = "D3DFMT_G8R8_G8B8";
        break; //           = MAKEFOURCC('G', 'R', 'G', 'B'),
      case D3DFMT_DXT1:
        s = "D3DFMT_DXT1";
        break; //           = MAKEFOURCC('D', 'X', 'T', '1'),
      case D3DFMT_DXT2:
        s = "D3DFMT_DXT2";
        break; //           = MAKEFOURCC('D', 'X', 'T', '2'),
      case D3DFMT_DXT3:
        s = "D3DFMT_DXT3";
        break; //           = MAKEFOURCC('D', 'X', 'T', '3'),
      case D3DFMT_DXT4:
        s = "D3DFMT_DXT4";
        break; //           = MAKEFOURCC('D', 'X', 'T', '4'),
      case D3DFMT_DXT5:
        s = "D3DFMT_DXT5";
        break; //           = MAKEFOURCC('D', 'X', 'T', '5'),

      case D3DFMT_D16_LOCKABLE:
        s = "D3DFMT_D16_LOCKABLE";
        break; //        = 70,
      case D3DFMT_D32:
        s = "D3DFMT_D32";
        break; //        = 71,
      case D3DFMT_D15S1:
        s = "D3DFMT_D15S1";
        break; //        = 73,
      case D3DFMT_D24S8:
        s = "D3DFMT_D24S8";
        break; //        = 75,
      case D3DFMT_D24X8:
        s = "D3DFMT_D24X8";
        break; //        = 77,
      case D3DFMT_D24X4S4:
        s = "D3DFMT_D24X4S4";
        break; //        = 79,
      case D3DFMT_D16:
        s = "D3DFMT_D16";
        break; //        = 80,

      case D3DFMT_D32F_LOCKABLE:
        s = "D3DFMT_D32F_LOCKABLE";
        break; //      = 82,
      case D3DFMT_D24FS8:
        s = "D3DFMT_D24FS8";
        break; //      = 83,


      case D3DFMT_L16:
        s = "D3DFMT_L16";
        break; //       = 81,

      case D3DFMT_VERTEXDATA:
        s = "D3DFMT_VERTEXDATA";
        break; //       =100,
      case D3DFMT_INDEX16:
        s = "D3DFMT_INDEX16";
        break; //      =101,
      case D3DFMT_INDEX32:
        s = "D3DFMT_INDEX32";
        break; //      =102,

      case D3DFMT_Q16W16V16U16:
        s = "D3DFMT_Q16W16V16U16";
        break; //     =110,

      case D3DFMT_MULTI2_ARGB8:
        s = "D3DFMT_MULTI2_ARGB8";
        break; //    = MAKEFOURCC('M','E','T','1'),

        // Floating point surface formats

        // s10e5 formats (16-bits per channel)
      case D3DFMT_R16F:
        s = "D3DFMT_R16F";
        break; //     = 111,
      case D3DFMT_G16R16F:
        s = "D3DFMT_G16R16F";
        break; //     = 112,
      case D3DFMT_A16B16G16R16F:
        s = "D3DFMT_A16B16G16R16F";
        break; //    = 113,

        // IEEE s23e8 formats (32-bits per channel)
      case D3DFMT_R32F:
        s = "D3DFMT_R32F";
        break; //       = 114,
      case D3DFMT_G32R32F:
        s = "D3DFMT_G32R32F";
        break; //      = 115,
      case D3DFMT_A32B32G32R32F:
        s = "D3DFMT_A32B32G32R32F";
        break; //      = 116,

      case D3DFMT_CxV8U8:
        s = "D3DFMT_CxV8U8";
        break; //      = 117,

      default:
        {
          // not found
        }

    }




    return s;
  };

  //=======================================================================
  GB_D3D9_API bool D3DFORMAT_fromstr(D3DFORMAT &fOut, const std::string &str)
  {
    if (str.length() == 0)
    {
      return false;
    }
    // D3DFMT_UNKNOWN;

    //            =  0,
    if (str == "D3DFMT_UNKNOWN")
    {
      fOut = D3DFMT_UNKNOWN;
      return true;
    }

    //             = 20,
    if (str == "D3DFMT_R8G8B8")
    {
      fOut = D3DFMT_R8G8B8;
      return true;
    }

    //            = 21,
    if (str == "D3DFMT_A8R8G8B8")
    {
      fOut = D3DFMT_A8R8G8B8;
      return true;
    }

    //            = 22,
    if (str == "D3DFMT_X8R8G8B8")
    {
      fOut = D3DFMT_X8R8G8B8;
      return true;
    }

    //           = 23,
    if (str == "D3DFMT_R5G6B5")
    {
      fOut = D3DFMT_R5G6B5;
      return true;
    }

    //            = 24,
    if (str == "D3DFMT_X1R5G5B5")
    {
      fOut = D3DFMT_X1R5G5B5;
      return true;
    }

    //             = 25,
    if (str == "D3DFMT_A1R5G5B5")
    {
      fOut = D3DFMT_A1R5G5B5;
      return true;
    }

    //             = 26,
    if (str == "D3DFMT_A4R4G4B4")
    {
      fOut = D3DFMT_A4R4G4B4;
      return true;
    }

    //              = 27,
    if (str == "D3DFMT_R3G3B2")
    {
      fOut = D3DFMT_R3G3B2;
      return true;
    }

    //              = 28,
    if (str == "D3DFMT_A8")
    {
      fOut = D3DFMT_A8;
      return true;
    }

    //             = 29,
    if (str == "D3DFMT_A8R3G3B2")
    {
      fOut = D3DFMT_A8R3G3B2;
      return true;
    }

    //           = 30,
    if (str == "D3DFMT_X4R4G4B4")
    {
      fOut = D3DFMT_X4R4G4B4;
      return true;
    }

    //         = 31,
    if (str == "D3DFMT_A2B10G10R10")
    {
      fOut = D3DFMT_A2B10G10R10;
      return true;
    }

    //           = 32,
    if (str == "D3DFMT_A8B8G8R8")
    {
      fOut = D3DFMT_A8B8G8R8;
      return true;
    }

    //            = 33,
    if (str == "D3DFMT_X8B8G8R8")
    {
      fOut = D3DFMT_X8B8G8R8;
      return true;
    }

    //              = 34,
    if (str == "D3DFMT_G16R16")
    {
      fOut = D3DFMT_G16R16;
      return true;
    }

    //         = 35,
    if (str == "D3DFMT_A2R10G10B10")
    {
      fOut = D3DFMT_A2R10G10B10;
      return true;
    }

    //        = 36,
    if (str == "D3DFMT_A16B16G16R16")
    {
      fOut = D3DFMT_A16B16G16R16;
      return true;
    }

    //                = 40,
    if (str == "D3DFMT_A8P8")
    {
      fOut = D3DFMT_A8P8;
      return true;
    }

    //                  = 41,
    if (str == "D3DFMT_P8")
    {
      fOut = D3DFMT_P8;
      return true;
    }

    //                  = 50,
    if (str == "D3DFMT_L8")
    {
      fOut = D3DFMT_L8;
      return true;
    }

    //                = 51,
    if (str == "D3DFMT_A8L8")
    {
      fOut = D3DFMT_A8L8;
      return true;
    }

    //                = 52,
    if (str == "D3DFMT_A4L4")
    {
      fOut = D3DFMT_A4L4;
      return true;
    }

    //                = 60,
    if (str == "D3DFMT_V8U8")
    {
      fOut = D3DFMT_V8U8;
      return true;
    }

    //             = 61,
    if (str == "D3DFMT_L6V5U5")
    {
      fOut = D3DFMT_L6V5U5;
      return true;
    }

    //            = 62,
    if (str == "D3DFMT_X8L8V8U8")
    {
      fOut = D3DFMT_X8L8V8U8;
      return true;
    }

    //            = 63,
    if (str == "D3DFMT_Q8W8V8U8")
    {
      fOut = D3DFMT_Q8W8V8U8;
      return true;
    }

    //           = 64,
    if (str == "D3DFMT_V16U16")
    {
      fOut = D3DFMT_V16U16;
      return true;
    }

    //         = 67,
    if (str == "D3DFMT_A2W10V10U10")
    {
      fOut = D3DFMT_A2W10V10U10;
      return true;
    }

    //             = MAKEFOURCC('U', 'Y', 'V', 'Y'),
    if (str == "D3DFMT_UYVY")
    {
      fOut = D3DFMT_UYVY;
      return true;
    }

    //          = MAKEFOURCC('R', 'G', 'B', 'G'),
    if (str == "D3DFMT_R8G8_B8G8")
    {
      fOut = D3DFMT_R8G8_B8G8;
      return true;
    }

    //           = MAKEFOURCC('Y', 'U', 'Y', '2'),
    if (str == "D3DFMT_YUY2")
    {
      fOut = D3DFMT_YUY2;
      return true;
    }

    //           = MAKEFOURCC('G', 'R', 'G', 'B'),
    if (str == "D3DFMT_G8R8_G8B8")
    {
      fOut = D3DFMT_G8R8_G8B8;
      return true;
    }

    //           = MAKEFOURCC('D', 'X', 'T', '1'),
    if (str == "D3DFMT_DXT1")
    {
      fOut = D3DFMT_DXT1;
      return true;
    }

    //           = MAKEFOURCC('D', 'X', 'T', '2'),
    if (str == "D3DFMT_DXT2")
    {
      fOut = D3DFMT_DXT2;
      return true;
    }

    //           = MAKEFOURCC('D', 'X', 'T', '3'),
    if (str == "D3DFMT_DXT3")
    {
      fOut = D3DFMT_DXT3;
      return true;
    }



    //           = MAKEFOURCC('D', 'X', 'T', '4'),
    if (str == "D3DFMT_DXT4")
    {
      fOut = D3DFMT_DXT4;
      return true;
    }

    //           = MAKEFOURCC('D', 'X', 'T', '5'),
    if (str == "D3DFMT_DXT5")
    {
      fOut = D3DFMT_DXT5;
      return true;
    }

    //        = 70,
    if (str == "D3DFMT_D16_LOCKABLE")
    {
      fOut = D3DFMT_D16_LOCKABLE;
      return true;
    }

    //        = 71,
    if (str == "D3DFMT_D32")
    {
      fOut = D3DFMT_D32;
      return true;
    }

    //        = 73,
    if (str == "D3DFMT_D15S1")
    {
      fOut = D3DFMT_D15S1;
      return true;
    }

    //        = 75,
    if (str == "D3DFMT_D24S8")
    {
      fOut = D3DFMT_D24S8;
      return true;
    }

    //        = 77,
    if (str == "D3DFMT_D24X8")
    {
      fOut = D3DFMT_D24X8;
      return true;
    }

    //        = 79,
    if (str == "D3DFMT_D24X4S4")
    {
      fOut = D3DFMT_D24X4S4;
      return true;
    }

    //        = 80,
    if (str == "D3DFMT_D16")
    {
      fOut = D3DFMT_D16;
      return true;
    }

    //      = 82,
    if (str == "D3DFMT_D32F_LOCKABLE")
    {
      fOut = D3DFMT_D32F_LOCKABLE;
      return true;
    }

    //      = 83,
    if (str == "D3DFMT_D24FS8")
    {
      fOut = D3DFMT_D24FS8;
      return true;
    }

    //       = 81,
    if (str == "D3DFMT_L16")
    {
      fOut = D3DFMT_L16;
      return true;
    }

    //       =100,
    if (str == "D3DFMT_VERTEXDATA")
    {
      fOut = D3DFMT_VERTEXDATA;
      return true;
    }

    //      =101,
    if (str == "D3DFMT_INDEX16")
    {
      fOut = D3DFMT_INDEX16;
      return true;
    }

    //      =102,
    if (str == "D3DFMT_INDEX32")
    {
      fOut = D3DFMT_INDEX32;
      return true;
    }

    //     =110,
    if (str == "D3DFMT_Q16W16V16U16")
    {
      fOut = D3DFMT_Q16W16V16U16;
      return true;
    }

    //    = MAKEFOURCC('M','E','T','1'),
    if (str == "D3DFMT_MULTI2_ARGB8")
    {
      fOut = D3DFMT_MULTI2_ARGB8;
      return true;
    }




    // Floating point surface formats
    //

    // s10e5 formats (16-bits per channel)
    //     = 111,
    if (str == "D3DFMT_R16F")
    {
      fOut = D3DFMT_R16F;
      return true;
    }

    //     = 112,
    if (str == "D3DFMT_G16R16F")
    {
      fOut = D3DFMT_G16R16F;
      return true;
    }

    //    = 113,
    if (str == "D3DFMT_A16B16G16R16F")
    {
      fOut = D3DFMT_A16B16G16R16F;
      return true;
    }


    // IEEE s23e8 formats (32-bits per channel)
    //       = 114,
    if (str == "D3DFMT_R32F")
    {
      fOut = D3DFMT_R32F;
      return true;
    }

    //      = 115,
    if (str == "D3DFMT_G32R32F")
    {
      fOut = D3DFMT_G32R32F;
      return true;
    }

    //      = 116,
    if (str == "D3DFMT_A32B32G32R32F")
    {
      fOut = D3DFMT_A32B32G32R32F;
      return true;
    }

    //      = 117,
    if (str == "D3DFMT_CxV8U8")
    {
      fOut = D3DFMT_CxV8U8;
      return true;
    }


    return false;
  };

  //=========================================================================
  GB_D3D9_API std::string D3DRESOURCETYPE_tostr(const D3DRESOURCETYPE val)
  {

    std::string s;

    switch (val)
    {
      case D3DRTYPE_SURFACE:
        {
          s = "D3DRTYPE_SURFACE";
        }
        break;
      case D3DRTYPE_VOLUME:
        {
          s = "D3DRTYPE_VOLUME";
        }
        break;
      case D3DRTYPE_TEXTURE:
        {
          s = "D3DRTYPE_TEXTURE";
        }
        break;
      case D3DRTYPE_VOLUMETEXTURE:
        {
          s = "D3DRTYPE_VOLUMETEXTURE";
        }
        break;
      case D3DRTYPE_CUBETEXTURE:
        {
          s = "D3DRTYPE_CUBETEXTURE";
        }
        break;
      case D3DRTYPE_VERTEXBUFFER:
        {
          s = "D3DRTYPE_VERTEXBUFFER";
        }
        break;
      case D3DRTYPE_INDEXBUFFER:
        {
          s = "D3DRTYPE_INDEXBUFFER";
        }
        break;

      default:
        {
          // none

        }
        ;


    };

    return s;
  };

  //=========================================================================
  GB_D3D9_API bool D3DRESOURCETYPE_fromstr(D3DRESOURCETYPE &rOut, const std
    ::string &str)
  {
    if (str == "D3DRTYPE_SURFACE")
    {
      rOut = D3DRTYPE_SURFACE;
      return true;
    };
    if (str == "D3DRTYPE_VOLUME")
    {
      rOut = D3DRTYPE_VOLUME;
      return true;
    };
    if (str == "D3DRTYPE_TEXTURE")
    {
      rOut = D3DRTYPE_TEXTURE;
      return true;
    };
    if (str == "D3DRTYPE_VOLUMETEXTURE")
    {
      rOut = D3DRTYPE_VOLUMETEXTURE;
      return true;
    };
    if (str == "D3DRTYPE_CUBETEXTURE")
    {
      rOut = D3DRTYPE_CUBETEXTURE;
      return true;
    };
    if (str == "D3DRTYPE_VERTEXBUFFER")
    {
      rOut = D3DRTYPE_VERTEXBUFFER;
      return true;
    };
    if (str == "D3DRTYPE_INDEXBUFFER")
    {
      rOut = D3DRTYPE_INDEXBUFFER;
      return true;
    };


    return false;
  };


  #pragma warning(push)
  #pragma warning(disable : 4996)


  //=========================================================================
  GB_D3D9_API std::string D3DRENDERSTATETYPE_tostr(const D3DRENDERSTATETYPE val)
  {

    std::string s;
    char ss[64];
    ss[0] = 0;

    switch (val)
    {

      case D3DRS_ZENABLE:
        {
          strcpy(ss, "D3DRS_ZENABLE");
        }
        break;
      case D3DRS_FILLMODE:
        {
          strcpy(ss, "D3DRS_FILLMODE");
        }
        break;
      case D3DRS_SHADEMODE:
        {
          strcpy(ss, "D3DRS_SHADEMODE");
        }
        break;
      case D3DRS_ZWRITEENABLE:
        {
          strcpy(ss, "D3DRS_ZWRITEENABLE");
        }
        break;
      case D3DRS_ALPHATESTENABLE:
        {
          strcpy(ss, "D3DRS_ALPHATESTENABLE");
        }
        break;
      case D3DRS_LASTPIXEL:
        {
          strcpy(ss, "D3DRS_LASTPIXEL");
        }
        break;

      case D3DRS_SRCBLEND:
        {
          strcpy(ss, "D3DRS_SRCBLEND");
        }
        break;
      case D3DRS_DESTBLEND:
        {
          strcpy(ss, "D3DRS_DESTBLEND");
        }
        break;
      case D3DRS_CULLMODE:
        {
          strcpy(ss, "D3DRS_CULLMODE");
        }
        break;
      case D3DRS_ZFUNC:
        {
          strcpy(ss, "D3DRS_ZFUNC");
        }
        break;
      case D3DRS_ALPHAREF:
        {
          strcpy(ss, "D3DRS_ALPHAREF");
        }
        break;


      case D3DRS_ALPHAFUNC:
        {
          strcpy(ss, "D3DRS_ALPHAFUNC");
        }
        break;
      case D3DRS_DITHERENABLE:
        {
          strcpy(ss, "D3DRS_DITHERENABLE");
        }
        break;
      case D3DRS_ALPHABLENDENABLE:
        {
          strcpy(ss, "D3DRS_ALPHABLENDENABLE");
        }
        break;
      case D3DRS_FOGENABLE:
        {
          strcpy(ss, "D3DRS_FOGENABLE");
        }
        break;

      case D3DRS_SPECULARENABLE:
        {
          strcpy(ss, "D3DRS_SPECULARENABLE");
        }
        break;
      case D3DRS_FOGCOLOR:
        {
          strcpy(ss, "D3DRS_FOGCOLOR");
        }
        break;
      case D3DRS_FOGTABLEMODE:
        {
          strcpy(ss, "D3DRS_FOGTABLEMODE");
        }
        break;
      case D3DRS_FOGSTART:
        {
          strcpy(ss, "D3DRS_FOGSTART");
        }
        break;
      case D3DRS_FOGEND:
        {
          strcpy(ss, "D3DRS_FOGEND");
        }
        break;
      case D3DRS_FOGDENSITY:
        {
          strcpy(ss, "D3DRS_FOGDENSITY");
        }
        break;
      case D3DRS_RANGEFOGENABLE:
        {
          strcpy(ss, "D3DRS_RANGEFOGENABLE");
        }
        break;


      case D3DRS_STENCILENABLE:
        {
          strcpy(ss, "D3DRS_STENCILENABLE");
        }
        break;
      case D3DRS_STENCILFAIL:
        {
          strcpy(ss, "D3DRS_STENCILFAIL");
        }
        break;
      case D3DRS_STENCILZFAIL:
        {
          strcpy(ss, "D3DRS_STENCILZFAIL");
        }
        break;
      case D3DRS_STENCILPASS:
        {
          strcpy(ss, "D3DRS_STENCILPASS");
        }
        break;
      case D3DRS_STENCILFUNC:
        {
          strcpy(ss, "D3DRS_STENCILFUNC");
        }
        break;
      case D3DRS_STENCILREF:
        {
          strcpy(ss, "D3DRS_STENCILREF");
        }
        break;
      case D3DRS_STENCILMASK:
        {
          strcpy(ss, "D3DRS_STENCILMASK");
        }
        break;
      case D3DRS_STENCILWRITEMASK:
        {
          strcpy(ss, "D3DRS_STENCILWRITEMASK");
        }
        break;


      case D3DRS_TEXTUREFACTOR:
        {
          strcpy(ss, "D3DRS_TEXTUREFACTOR");
        }
        break;

      case D3DRS_WRAP0:
        {
          strcpy(ss, "D3DRS_WRAP0");
        }
        break;
      case D3DRS_WRAP1:
        {
          strcpy(ss, "D3DRS_WRAP1");
        }
        break;
      case D3DRS_WRAP2:
        {
          strcpy(ss, "D3DRS_WRAP2");
        }
        break;
      case D3DRS_WRAP3:
        {
          strcpy(ss, "D3DRS_WRAP3");
        }
        break;
      case D3DRS_WRAP4:
        {
          strcpy(ss, "D3DRS_WRAP4");
        }
        break;
      case D3DRS_WRAP5:
        {
          strcpy(ss, "D3DRS_WRAP5");
        }
        break;
      case D3DRS_WRAP6:
        {
          strcpy(ss, "D3DRS_WRAP6");
        }
        break;
      case D3DRS_WRAP7:
        {
          strcpy(ss, "D3DRS_WRAP7");
        }
        break;


      case D3DRS_CLIPPING:
        {
          strcpy(ss, "D3DRS_CLIPPING");
        }
        break;
      case D3DRS_LIGHTING:
        {
          strcpy(ss, "D3DRS_LIGHTING");
        }
        break;
      case D3DRS_AMBIENT:
        {
          strcpy(ss, "D3DRS_AMBIENT");
        }
        break;
      case D3DRS_FOGVERTEXMODE:
        {
          strcpy(ss, "D3DRS_FOGVERTEXMODE");
        }
        break;


      case D3DRS_COLORVERTEX:
        {
          strcpy(ss, "D3DRS_COLORVERTEX");
        }
        break;
      case D3DRS_LOCALVIEWER:
        {
          strcpy(ss, "D3DRS_LOCALVIEWER");
        }
        break;
      case D3DRS_NORMALIZENORMALS:
        {
          strcpy(ss, "D3DRS_NORMALIZENORMALS");
        }
        break;
      case D3DRS_DIFFUSEMATERIALSOURCE:
        {
          strcpy(ss, "D3DRS_DIFFUSEMATERIALSOURCE");
        }
        break;
      case D3DRS_SPECULARMATERIALSOURCE:
        {
          strcpy(ss, "D3DRS_SPECULARMATERIALSOURCE");
        }
        break;
      case D3DRS_AMBIENTMATERIALSOURCE:
        {
          strcpy(ss, "D3DRS_AMBIENTMATERIALSOURCE");
        }
        break;
      case D3DRS_EMISSIVEMATERIALSOURCE:
        {
          strcpy(ss, "D3DRS_EMISSIVEMATERIALSOURCE");
        }
        break;


      case D3DRS_VERTEXBLEND:
        {
          strcpy(ss, "D3DRS_VERTEXBLEND");
        }
        break;
      case D3DRS_CLIPPLANEENABLE:
        {
          strcpy(ss, "D3DRS_CLIPPLANEENABLE");
        }
        break;


      case D3DRS_POINTSIZE:
        {
          strcpy(ss, "D3DRS_POINTSIZE");
        }
        break;
      case D3DRS_POINTSIZE_MIN:
        {
          strcpy(ss, "D3DRS_POINTSIZE_MIN");
        }
        break;
      case D3DRS_POINTSPRITEENABLE:
        {
          strcpy(ss, "D3DRS_POINTSPRITEENABLE");
        }
        break;
      case D3DRS_POINTSCALEENABLE:
        {
          strcpy(ss, "D3DRS_POINTSCALEENABLE");
        }
        break;

      case D3DRS_POINTSCALE_A:
        {
          strcpy(ss, "D3DRS_POINTSCALE_A");
        }
        break;
      case D3DRS_POINTSCALE_B:
        {
          strcpy(ss, "D3DRS_POINTSCALE_B");
        }
        break;
      case D3DRS_POINTSCALE_C:
        {
          strcpy(ss, "D3DRS_POINTSCALE_C");
        }
        break;


      case D3DRS_MULTISAMPLEANTIALIAS:
        {
          strcpy(ss, "D3DRS_MULTISAMPLEANTIALIAS");
        }
        break;
      case D3DRS_MULTISAMPLEMASK:
        {
          strcpy(ss, "D3DRS_MULTISAMPLEMASK");
        }
        break;
      case D3DRS_PATCHEDGESTYLE:
        {
          strcpy(ss, "D3DRS_PATCHEDGESTYLE");
        }
        break;
      case D3DRS_DEBUGMONITORTOKEN:
        {
          strcpy(ss, "D3DRS_DEBUGMONITORTOKEN");
        }
        break;
      case D3DRS_POINTSIZE_MAX:
        {
          strcpy(ss, "D3DRS_POINTSIZE_MAX");
        }
        break;
      case D3DRS_INDEXEDVERTEXBLENDENABLE:
        {
          strcpy(ss, "D3DRS_INDEXEDVERTEXBLENDENABLE");
        }
        break;
      case D3DRS_COLORWRITEENABLE:
        {
          strcpy(ss, "D3DRS_COLORWRITEENABLE");
        }
        break;
      case D3DRS_TWEENFACTOR:
        {
          strcpy(ss, "D3DRS_TWEENFACTOR");
        }
        break;


      case D3DRS_BLENDOP:
        {
          strcpy(ss, "D3DRS_BLENDOP");
        }
        break;
      case D3DRS_POSITIONDEGREE:
        {
          strcpy(ss, "D3DRS_POSITIONDEGREE");
        }
        break;
      case D3DRS_NORMALDEGREE:
        {
          strcpy(ss, "D3DRS_NORMALDEGREE");
        }
        break;
      case D3DRS_SCISSORTESTENABLE:
        {
          strcpy(ss, "D3DRS_SCISSORTESTENABLE");
        }
        break;
      case D3DRS_SLOPESCALEDEPTHBIAS:
        {
          strcpy(ss, "D3DRS_SLOPESCALEDEPTHBIAS");
        }
        break;
      case D3DRS_ANTIALIASEDLINEENABLE:
        {
          strcpy(ss, "D3DRS_ANTIALIASEDLINEENABLE");
        }
        break;
      case D3DRS_MINTESSELLATIONLEVEL:
        {
          strcpy(ss, "D3DRS_MINTESSELLATIONLEVEL");
        }
        break;
      case D3DRS_MAXTESSELLATIONLEVEL:
        {
          strcpy(ss, "D3DRS_MAXTESSELLATIONLEVEL");
        }
        break;


      case D3DRS_ADAPTIVETESS_X:
        {
          strcpy(ss, "D3DRS_ADAPTIVETESS_X");
        }
        break;
      case D3DRS_ADAPTIVETESS_Y:
        {
          strcpy(ss, "D3DRS_ADAPTIVETESS_Y");
        }
        break;
      case D3DRS_ADAPTIVETESS_Z:
        {
          strcpy(ss, "D3DRS_ADAPTIVETESS_Z");
        }
        break;
      case D3DRS_ADAPTIVETESS_W:
        {
          strcpy(ss, "D3DRS_ADAPTIVETESS_W");
        }
        break;


      case D3DRS_ENABLEADAPTIVETESSELLATION:
        {
          strcpy(ss, "D3DRS_ENABLEADAPTIVETESSELLATION");
        }
        break;
      case D3DRS_TWOSIDEDSTENCILMODE:
        {
          strcpy(ss, "D3DRS_TWOSIDEDSTENCILMODE");
        }
        break;


      case D3DRS_CCW_STENCILFAIL:
        {
          strcpy(ss, "D3DRS_CCW_STENCILFAIL");
        }
        break;
      case D3DRS_CCW_STENCILZFAIL:
        {
          strcpy(ss, "D3DRS_CCW_STENCILZFAIL");
        }
        break;
      case D3DRS_CCW_STENCILPASS:
        {
          strcpy(ss, "D3DRS_CCW_STENCILPASS");
        }
        break;
      case D3DRS_CCW_STENCILFUNC:
        {
          strcpy(ss, "D3DRS_CCW_STENCILFUNC");
        }
        break;
      case D3DRS_COLORWRITEENABLE1:
        {
          strcpy(ss, "D3DRS_COLORWRITEENABLE1");
        }
        break;
      case D3DRS_COLORWRITEENABLE2:
        {
          strcpy(ss, "D3DRS_COLORWRITEENABLE2");
        }
        break;
      case D3DRS_COLORWRITEENABLE3:
        {
          strcpy(ss, "D3DRS_COLORWRITEENABLE3");
        }
        break;



      case D3DRS_BLENDFACTOR:
        {
          strcpy(ss, "D3DRS_BLENDFACTOR");
        }
        break;
      case D3DRS_SRGBWRITEENABLE:
        {
          strcpy(ss, "D3DRS_SRGBWRITEENABLE");
        }
        break;
      case D3DRS_DEPTHBIAS:
        {
          strcpy(ss, "D3DRS_DEPTHBIAS");
        }
        break;


      case D3DRS_WRAP8:
        {
          strcpy(ss, "D3DRS_WRAP8");
        }
        break;
      case D3DRS_WRAP9:
        {
          strcpy(ss, "D3DRS_WRAP9");
        }
        break;
      case D3DRS_WRAP10:
        {
          strcpy(ss, "D3DRS_WRAP10");
        }
        break;
      case D3DRS_WRAP11:
        {
          strcpy(ss, "D3DRS_WRAP11");
        }
        break;
      case D3DRS_WRAP12:
        {
          strcpy(ss, "D3DRS_WRAP12");
        }
        break;
      case D3DRS_WRAP13:
        {
          strcpy(ss, "D3DRS_WRAP13");
        }
        break;
      case D3DRS_WRAP14:
        {
          strcpy(ss, "D3DRS_WRAP14");
        }
        break;
      case D3DRS_WRAP15:
        {
          strcpy(ss, "D3DRS_WRAP15");
        }
        break;


      case D3DRS_SEPARATEALPHABLENDENABLE:
        {
          strcpy(ss, "D3DRS_SEPARATEALPHABLENDENABLE");
        }
        break;
      case D3DRS_SRCBLENDALPHA:
        {
          strcpy(ss, "D3DRS_SRCBLENDALPHA");
        }
        break;
      case D3DRS_DESTBLENDALPHA:
        {
          strcpy(ss, "D3DRS_DESTBLENDALPHA");
        }
        break;
      case D3DRS_BLENDOPALPHA:
        {
          strcpy(ss, "D3DRS_BLENDOPALPHA");
        }
        break;


      default:
        {
          // none

        }
        ;

    }; // switch

    if (ss[0])
    {
      s = ss;
    }

    return s;
  };

  //=======================================================================
  GB_D3D9_API bool D3DRENDERSTATETYPE_fromstr(D3DRENDERSTATETYPE &val, std
    ::string &str)
  {
    if (str.length() == 0)
    {
      return false;
    }

    const char *s = str.c_str();
    const size_t ns = str.length();


    if (strncmp(s, "D3DRS_ZENABLE", ns) == 0)
    {
      val = D3DRS_ZENABLE;
      return true;
    };
    if (strncmp(s, "D3DRS_FILLMODE", ns) == 0)
    {
      val = D3DRS_FILLMODE;
      return true;
    };
    if (strncmp(s, "D3DRS_SHADEMODE", ns) == 0)
    {
      val = D3DRS_SHADEMODE;
      return true;
    };
    if (strncmp(s, "D3DRS_ZWRITEENABLE", ns) == 0)
    {
      val = D3DRS_ZWRITEENABLE;
      return true;
    };
    if (strncmp(s, "D3DRS_ALPHATESTENABLE", ns) == 0)
    {
      val = D3DRS_ALPHATESTENABLE;
      return true;
    };
    if (strncmp(s, "D3DRS_LASTPIXEL", ns) == 0)
    {
      val = D3DRS_LASTPIXEL;
      return true;
    };
    if (strncmp(s, "D3DRS_SRCBLEND", ns) == 0)
    {
      val = D3DRS_SRCBLEND;
      return true;
    };
    if (strncmp(s, "D3DRS_DESTBLEND", ns) == 0)
    {
      val = D3DRS_DESTBLEND;
      return true;
    };
    if (strncmp(s, "D3DRS_CULLMODE", ns) == 0)
    {
      val = D3DRS_CULLMODE;
      return true;
    };
    if (strncmp(s, "D3DRS_ZFUNC", ns) == 0)
    {
      val = D3DRS_ZFUNC;
      return true;
    };


    if (strncmp(s, "D3DRS_ALPHAREF", ns) == 0)
    {
      val = D3DRS_ALPHAREF;
      return true;
    };
    if (strncmp(s, "D3DRS_ALPHAFUNC", ns) == 0)
    {
      val = D3DRS_ALPHAFUNC;
      return true;
    };
    if (strncmp(s, "D3DRS_DITHERENABLE", ns) == 0)
    {
      val = D3DRS_DITHERENABLE;
      return true;
    };
    if (strncmp(s, "D3DRS_ALPHABLENDENABLE", ns) == 0)
    {
      val = D3DRS_ALPHABLENDENABLE;
      return true;
    };
    if (strncmp(s, "D3DRS_FOGENABLE", ns) == 0)
    {
      val = D3DRS_FOGENABLE;
      return true;
    };
    if (strncmp(s, "D3DRS_SPECULARENABLE", ns) == 0)
    {
      val = D3DRS_SPECULARENABLE;
      return true;
    };
    if (strncmp(s, "D3DRS_FOGCOLOR", ns) == 0)
    {
      val = D3DRS_FOGCOLOR;
      return true;
    };
    if (strncmp(s, "D3DRS_FOGTABLEMODE", ns) == 0)
    {
      val = D3DRS_FOGTABLEMODE;
      return true;
    };
    if (strncmp(s, "D3DRS_FOGSTART", ns) == 0)
    {
      val = D3DRS_FOGSTART;
      return true;
    };
    if (strncmp(s, "D3DRS_FOGEND", ns) == 0)
    {
      val = D3DRS_FOGEND;
      return true;
    };
    if (strncmp(s, "D3DRS_FOGDENSITY", ns) == 0)
    {
      val = D3DRS_FOGDENSITY;
      return true;
    };

    if (strncmp(s, "D3DRS_RANGEFOGENABLE", ns) == 0)
    {
      val = D3DRS_RANGEFOGENABLE;
      return true;
    };
    if (strncmp(s, "D3DRS_STENCILENABLE", ns) == 0)
    {
      val = D3DRS_STENCILENABLE;
      return true;
    };
    if (strncmp(s, "D3DRS_STENCILFAIL", ns) == 0)
    {
      val = D3DRS_STENCILFAIL;
      return true;
    };
    if (strncmp(s, "D3DRS_STENCILZFAIL", ns) == 0)
    {
      val = D3DRS_STENCILZFAIL;
      return true;
    };
    if (strncmp(s, "D3DRS_STENCILPASS", ns) == 0)
    {
      val = D3DRS_STENCILPASS;
      return true;
    };
    if (strncmp(s, "D3DRS_STENCILFUNC", ns) == 0)
    {
      val = D3DRS_STENCILFUNC;
      return true;
    };
    if (strncmp(s, "D3DRS_STENCILREF", ns) == 0)
    {
      val = D3DRS_STENCILREF;
      return true;
    };
    if (strncmp(s, "D3DRS_STENCILMASK", ns) == 0)
    {
      val = D3DRS_STENCILMASK;
      return true;
    };
    if (strncmp(s, "D3DRS_STENCILWRITEMASK", ns) == 0)
    {
      val = D3DRS_STENCILWRITEMASK;
      return true;
    };


    if (strncmp(s, "D3DRS_TEXTUREFACTOR", ns) == 0)
    {
      val = D3DRS_TEXTUREFACTOR;
      return true;
    };
    if (strncmp(s, "D3DRS_WRAP0", ns) == 0)
    {
      val = D3DRS_WRAP0;
      return true;
    };
    if (strncmp(s, "D3DRS_WRAP1", ns) == 0)
    {
      val = D3DRS_WRAP1;
      return true;
    };
    if (strncmp(s, "D3DRS_WRAP2", ns) == 0)
    {
      val = D3DRS_WRAP2;
      return true;
    };
    if (strncmp(s, "D3DRS_WRAP3", ns) == 0)
    {
      val = D3DRS_WRAP3;
      return true;
    };
    if (strncmp(s, "D3DRS_WRAP4", ns) == 0)
    {
      val = D3DRS_WRAP4;
      return true;
    };
    if (strncmp(s, "D3DRS_WRAP5", ns) == 0)
    {
      val = D3DRS_WRAP5;
      return true;
    };
    if (strncmp(s, "D3DRS_WRAP6", ns) == 0)
    {
      val = D3DRS_WRAP6;
      return true;
    };
    if (strncmp(s, "D3DRS_WRAP7", ns) == 0)
    {
      val = D3DRS_WRAP7;
      return true;
    };



    if (strncmp(s, "D3DRS_CLIPPING", ns) == 0)
    {
      val = D3DRS_CLIPPING;
      return true;
    };
    if (strncmp(s, "D3DRS_LIGHTING", ns) == 0)
    {
      val = D3DRS_LIGHTING;
      return true;
    };
    if (strncmp(s, "D3DRS_AMBIENT", ns) == 0)
    {
      val = D3DRS_AMBIENT;
      return true;
    };
    if (strncmp(s, "D3DRS_FOGVERTEXMODE", ns) == 0)
    {
      val = D3DRS_FOGVERTEXMODE;
      return true;
    };
    if (strncmp(s, "D3DRS_COLORVERTEX", ns) == 0)
    {
      val = D3DRS_COLORVERTEX;
      return true;
    };
    if (strncmp(s, "D3DRS_LOCALVIEWER", ns) == 0)
    {
      val = D3DRS_LOCALVIEWER;
      return true;
    };
    if (strncmp(s, "D3DRS_NORMALIZENORMALS", ns) == 0)
    {
      val = D3DRS_NORMALIZENORMALS;
      return true;
    };
    if (strncmp(s, "D3DRS_DIFFUSEMATERIALSOURCE", ns) == 0)
    {
      val = D3DRS_DIFFUSEMATERIALSOURCE;
      return true;
    };
    if (strncmp(s, "D3DRS_SPECULARMATERIALSOURCE", ns) == 0)
    {
      val = D3DRS_SPECULARMATERIALSOURCE;
      return true;
    };
    if (strncmp(s, "D3DRS_AMBIENTMATERIALSOURCE", ns) == 0)
    {
      val = D3DRS_AMBIENTMATERIALSOURCE;
      return true;
    };
    if (strncmp(s, "D3DRS_EMISSIVEMATERIALSOURCE", ns) == 0)
    {
      val = D3DRS_EMISSIVEMATERIALSOURCE;
      return true;
    };
    if (strncmp(s, "D3DRS_VERTEXBLEND", ns) == 0)
    {
      val = D3DRS_VERTEXBLEND;
      return true;
    };
    if (strncmp(s, "D3DRS_CLIPPLANEENABLE", ns) == 0)
    {
      val = D3DRS_CLIPPLANEENABLE;
      return true;
    };



    if (strncmp(s, "D3DRS_POINTSIZE", ns) == 0)
    {
      val = D3DRS_POINTSIZE;
      return true;
    };
    if (strncmp(s, "D3DRS_POINTSIZE_MIN", ns) == 0)
    {
      val = D3DRS_POINTSIZE_MIN;
      return true;
    };
    if (strncmp(s, "D3DRS_POINTSPRITEENABLE", ns) == 0)
    {
      val = D3DRS_POINTSPRITEENABLE;
      return true;
    };
    if (strncmp(s, "D3DRS_POINTSCALEENABLE", ns) == 0)
    {
      val = D3DRS_POINTSCALEENABLE;
      return true;
    };
    if (strncmp(s, "D3DRS_POINTSCALE_A", ns) == 0)
    {
      val = D3DRS_POINTSCALE_A;
      return true;
    };
    if (strncmp(s, "D3DRS_POINTSCALE_B", ns) == 0)
    {
      val = D3DRS_POINTSCALE_B;
      return true;
    };
    if (strncmp(s, "D3DRS_POINTSCALE_C", ns) == 0)
    {
      val = D3DRS_POINTSCALE_C;
      return true;
    };


    if (strncmp(s, "D3DRS_MULTISAMPLEANTIALIAS", ns) == 0)
    {
      val = D3DRS_MULTISAMPLEANTIALIAS;
      return true;
    };
    if (strncmp(s, "D3DRS_MULTISAMPLEMASK", ns) == 0)
    {
      val = D3DRS_MULTISAMPLEMASK;
      return true;
    };
    if (strncmp(s, "D3DRS_PATCHEDGESTYLE", ns) == 0)
    {
      val = D3DRS_PATCHEDGESTYLE;
      return true;
    };
    if (strncmp(s, "D3DRS_DEBUGMONITORTOKEN", ns) == 0)
    {
      val = D3DRS_DEBUGMONITORTOKEN;
      return true;
    };
    if (strncmp(s, "D3DRS_POINTSIZE_MAX", ns) == 0)
    {
      val = D3DRS_POINTSIZE_MAX;
      return true;
    };
    if (strncmp(s, "D3DRS_INDEXEDVERTEXBLENDENABLE", ns) == 0)
    {
      val = D3DRS_INDEXEDVERTEXBLENDENABLE;
      return true;
    };
    if (strncmp(s, "D3DRS_COLORWRITEENABLE", ns) == 0)
    {
      val = D3DRS_COLORWRITEENABLE;
      return true;
    };



    if (strncmp(s, "D3DRS_TWEENFACTOR", ns) == 0)
    {
      val = D3DRS_TWEENFACTOR;
      return true;
    };
    if (strncmp(s, "D3DRS_BLENDOP", ns) == 0)
    {
      val = D3DRS_BLENDOP;
      return true;
    }
    if (strncmp(s, "D3DRS_POSITIONDEGREE", ns) == 0)
    {
      val = D3DRS_POSITIONDEGREE;
      return true;
    }
    if (strncmp(s, "D3DRS_NORMALDEGREE", ns) == 0)
    {
      val = D3DRS_NORMALDEGREE;
      return true;
    }
    if (strncmp(s, "D3DRS_SCISSORTESTENABLE", ns) == 0)
    {
      val = D3DRS_SCISSORTESTENABLE;
      return true;
    }
    if (strncmp(s, "D3DRS_SLOPESCALEDEPTHBIAS", ns) == 0)
    {
      val = D3DRS_SLOPESCALEDEPTHBIAS;
      return true;
    }
    if (strncmp(s, "D3DRS_ANTIALIASEDLINEENABLE", ns) == 0)
    {
      val = D3DRS_ANTIALIASEDLINEENABLE;
      return true;
    }
    if (strncmp(s, "D3DRS_MINTESSELLATIONLEVEL", ns) == 0)
    {
      val = D3DRS_MINTESSELLATIONLEVEL;
      return true;
    }
    if (strncmp(s, "D3DRS_MAXTESSELLATIONLEVEL", ns) == 0)
    {
      val = D3DRS_MAXTESSELLATIONLEVEL;
      return true;
    }


    if (strncmp(s, "D3DRS_ADAPTIVETESS_X", ns) == 0)
    {
      val = D3DRS_ADAPTIVETESS_X;
      return true;
    }
    if (strncmp(s, "D3DRS_ADAPTIVETESS_Y", ns) == 0)
    {
      val = D3DRS_ADAPTIVETESS_Y;
      return true;
    }
    if (strncmp(s, "D3DRS_ADAPTIVETESS_Z", ns) == 0)
    {
      val = D3DRS_ADAPTIVETESS_Z;
      return true;
    }
    if (strncmp(s, "D3DRS_ADAPTIVETESS_W", ns) == 0)
    {
      val = D3DRS_ADAPTIVETESS_W;
      return true;
    }
    if (strncmp(s, "D3DRS_ENABLEADAPTIVETESSELLATION", ns) == 0)
    {
      val = D3DRS_ENABLEADAPTIVETESSELLATION;
      return true;
    }
    if (strncmp(s, "D3DRS_TWOSIDEDSTENCILMODE", ns) == 0)
    {
      val = D3DRS_TWOSIDEDSTENCILMODE;
      return true;
    }


    if (strncmp(s, "D3DRS_CCW_STENCILFAIL", ns) == 0)
    {
      val = D3DRS_CCW_STENCILFAIL;
      return true;
    }
    if (strncmp(s, "D3DRS_CCW_STENCILZFAIL", ns) == 0)
    {
      val = D3DRS_CCW_STENCILZFAIL;
      return true;
    }
    if (strncmp(s, "D3DRS_CCW_STENCILPASS", ns) == 0)
    {
      val = D3DRS_CCW_STENCILPASS;
      return true;
    }
    if (strncmp(s, "D3DRS_CCW_STENCILFUNC", ns) == 0)
    {
      val = D3DRS_CCW_STENCILFUNC;
      return true;
    }

    if (strncmp(s, "D3DRS_COLORWRITEENABLE1", ns) == 0)
    {
      val = D3DRS_COLORWRITEENABLE1;
      return true;
    }
    if (strncmp(s, "D3DRS_COLORWRITEENABLE2", ns) == 0)
    {
      val = D3DRS_COLORWRITEENABLE2;
      return true;
    }
    if (strncmp(s, "D3DRS_COLORWRITEENABLE3", ns) == 0)
    {
      val = D3DRS_COLORWRITEENABLE3;
      return true;
    }


    if (strncmp(s, "D3DRS_BLENDFACTOR", ns) == 0)
    {
      val = D3DRS_BLENDFACTOR;
      return true;
    }
    if (strncmp(s, "D3DRS_SRGBWRITEENABLE", ns) == 0)
    {
      val = D3DRS_SRGBWRITEENABLE;
      return true;
    }
    if (strncmp(s, "D3DRS_DEPTHBIAS", ns) == 0)
    {
      val = D3DRS_DEPTHBIAS;
      return true;
    }


    if (strncmp(s, "D3DRS_WRAP8", ns) == 0)
    {
      val = D3DRS_WRAP8;
      return true;
    }
    if (strncmp(s, "D3DRS_WRAP9", ns) == 0)
    {
      val = D3DRS_WRAP9;
      return true;
    }
    if (strncmp(s, "D3DRS_WRAP10", ns) == 0)
    {
      val = D3DRS_WRAP10;
      return true;
    }
    if (strncmp(s, "D3DRS_WRAP11", ns) == 0)
    {
      val = D3DRS_WRAP11;
      return true;
    }
    if (strncmp(s, "D3DRS_WRAP12", ns) == 0)
    {
      val = D3DRS_WRAP12;
      return true;
    }
    if (strncmp(s, "D3DRS_WRAP13", ns) == 0)
    {
      val = D3DRS_WRAP13;
      return true;
    }
    if (strncmp(s, "D3DRS_WRAP14", ns) == 0)
    {
      val = D3DRS_WRAP14;
      return true;
    }
    if (strncmp(s, "D3DRS_WRAP15", ns) == 0)
    {
      val = D3DRS_WRAP15;
      return true;
    }

    if (strncmp(s, "D3DRS_SEPARATEALPHABLENDENABLE", ns) == 0)
    {
      val = D3DRS_SEPARATEALPHABLENDENABLE;
      return true;
    }

    if (strncmp(s, "D3DRS_SRCBLENDALPHA", ns) == 0)
    {
      val = D3DRS_SRCBLENDALPHA;
      return true;
    }
    if (strncmp(s, "D3DRS_DESTBLENDALPHA", ns) == 0)
    {
      val = D3DRS_DESTBLENDALPHA;
      return true;
    }
    if (strncmp(s, "D3DRS_BLENDOPALPHA", ns) == 0)
    {
      val = D3DRS_BLENDOPALPHA;
      return true;
    }


    // not found !
    return false;
  };

  #pragma warning( pop )


  //=======================================================================
  GB_D3D9_API std::string D3DPOOL_tostr(const D3DPOOL val)
  {
    std::string s;

    switch (val)
    {
      case D3DPOOL_DEFAULT:
        {
          s = "D3DPOOL_DEFAULT";
        }
        break;
      case D3DPOOL_MANAGED:
        {
          s = "D3DPOOL_MANAGED";
        }
        break;
      case D3DPOOL_SYSTEMMEM:
        {
          s = "D3DPOOL_SYSTEMMEM";
        }
        break;
      case D3DPOOL_SCRATCH:
        {
          s = "D3DPOOL_SCRATCH";
        }
        break;


      default:
        {
          // none
        }

    }; // switch


    return s;
  };

  //=======================================================================
  GB_D3D9_API bool D3DPOOL_fromstr(D3DPOOL &val, const std::string &str)
  {
    if (str == "D3DPOOL_DEFAULT")
    {
      val = D3DPOOL_DEFAULT;
      return true;
    };
    if (str == "D3DPOOL_MANAGED")
    {
      val = D3DPOOL_MANAGED;
      return true;
    };
    if (str == "D3DPOOL_SYSTEMMEM")
    {
      val = D3DPOOL_SYSTEMMEM;
      return true;
    };
    if (str == "D3DPOOL_SCRATCH")
    {
      val = D3DPOOL_SCRATCH;
      return true;
    };


    return false;
  };

  //=======================================================================
  GB_D3D9_API std::string D3DFILLMODE_tostr(const D3DFILLMODE val)
  {
    std::string s;

    switch (val)
    {

      case D3DFILL_POINT:
        {
          s = "D3DFILL_POINT";
        }
        break;
      case D3DFILL_WIREFRAME:
        {
          s = "D3DFILL_WIREFRAME";
        }
        break;
      case D3DFILL_SOLID:
        {
          s = "D3DFILL_SOLID";
        }
        break;

      default:
        {
          // not found !
        }
        ;
    }

    return s;
  };

  //===============================================
  GB_D3D9_API bool D3DFILLMODE_fromstr(D3DFILLMODE &valOut, const std::string
                                       &str)
  {

    if (str == "D3DFILL_POINT")
    {
      valOut = D3DFILL_POINT;
      return true;
    };
    if (str == "D3DFILL_WIREFRAME")
    {
      valOut = D3DFILL_WIREFRAME;
      return true;
    };
    if (str == "D3DFILL_SOLID")
    {
      valOut = D3DFILL_SOLID;
      return true;
    };

    return false;
  };


  //==============================================
  GB_D3D9_API std::string D3DSHADEMODE_tostr(const D3DSHADEMODE val)
  {
    std::string s;

    switch (val)
    {

      case D3DSHADE_FLAT:
        {
          s = "D3DSHADE_FLAT";
        }
        break;
      case D3DSHADE_GOURAUD:
        {
          s = "D3DSHADE_GOURAUD";
        }
        break;
      case D3DSHADE_PHONG:
        {
          s = "D3DSHADE_PHONG";
        }
        break;

      default:
        {
          // not found !		   
        }
        ;
    };

    return s;
  };

  //=========================================================
  GB_D3D9_API bool D3DSHADEMODE_fromstr(D3DSHADEMODE &valOut, const std::string
                                        &str)
  {
    if (str == "D3DSHADE_FLAT")
    {
      valOut = D3DSHADE_FLAT;
      return true;
    };
    if (str == "D3DSHADE_GOURAUD")
    {
      valOut = D3DSHADE_GOURAUD;
      return true;
    };
    if (str == "D3DSHADE_PHONG")
    {
      valOut = D3DSHADE_PHONG;
      return true;
    };

    return false;
  };


  #pragma warning(push)  
  #pragma warning(disable : 4996)

  //================================================
  GB_D3D9_API std::string D3DBLEND_tostr(const D3DBLEND val)
  {
    std::string s;

    char ss[32];
    ss[0] = 0;

    switch (val)
    {
      case D3DBLEND_ZERO:
        {
          strcpy(ss, "D3DBLEND_ZERO");
        }
        break;
      case D3DBLEND_ONE:
        {
          strcpy(ss, "D3DBLEND_ONE");
        }
        break;
      case D3DBLEND_SRCCOLOR:
        {
          strcpy(ss, "D3DBLEND_SRCCOLOR");
        }
        break;
      case D3DBLEND_INVSRCCOLOR:
        {
          strcpy(ss, "D3DBLEND_INVSRCCOLOR");
        }
        break;
      case D3DBLEND_SRCALPHA:
        {
          strcpy(ss, "D3DBLEND_SRCALPHA");
        }
        break;
      case D3DBLEND_INVSRCALPHA:
        {
          strcpy(ss, "D3DBLEND_INVSRCALPHA");
        }
        break;
      case D3DBLEND_DESTALPHA:
        {
          strcpy(ss, "D3DBLEND_DESTALPHA");
        }
        break;
      case D3DBLEND_INVDESTALPHA:
        {
          strcpy(ss, "D3DBLEND_INVDESTALPHA");
        }
        break;
      case D3DBLEND_DESTCOLOR:
        {
          strcpy(ss, "D3DBLEND_DESTCOLOR");
        }
        break;
      case D3DBLEND_INVDESTCOLOR:
        {
          strcpy(ss, "D3DBLEND_INVDESTCOLOR");
        }
        break;
      case D3DBLEND_SRCALPHASAT:
        {
          strcpy(ss, "D3DBLEND_SRCALPHASAT");
        }
        break;
      case D3DBLEND_BOTHSRCALPHA:
        {
          strcpy(ss, "D3DBLEND_BOTHSRCALPHA");
        }
        break;
      case D3DBLEND_BOTHINVSRCALPHA:
        {
          strcpy(ss, "D3DBLEND_BOTHINVSRCALPHA");
        }
        break;
      case D3DBLEND_BLENDFACTOR:
        {
          strcpy(ss, "D3DBLEND_BLENDFACTOR");
        }
        break;
      case D3DBLEND_INVBLENDFACTOR:
        {
          strcpy(ss, "D3DBLEND_INVBLENDFACTOR");
        }
        break;


      default:
        {

        }
        ;
    };

    if (ss[0])
    {
      s = ss;
    }


    return s;
  };



  //======================================================
  GB_D3D9_API bool D3DBLEND_fromstr(D3DBLEND &valOut, const std::string &str)
  {
    if (str.length() == 0)
    {
      return false;
    }

    const char *s = str.c_str();
    const size_t NSLEN = str.length();

    if (strncmp(s, "D3DBLEND_ZERO", NSLEN) == 0)
    {
      valOut = D3DBLEND_ZERO;
      return true;
    };
    if (strncmp(s, "D3DBLEND_ONE", NSLEN) == 0)
    {
      valOut = D3DBLEND_ONE;
      return true;
    };
    if (strncmp(s, "D3DBLEND_SRCCOLOR", NSLEN) == 0)
    {
      valOut = D3DBLEND_SRCCOLOR;
      return true;
    };
    if (strncmp(s, "D3DBLEND_INVSRCCOLOR", NSLEN) == 0)
    {
      valOut = D3DBLEND_INVSRCCOLOR;
      return true;
    };
    if (strncmp(s, "D3DBLEND_SRCALPHA ", NSLEN) == 0)
    {
      valOut = D3DBLEND_SRCALPHA;
      return true;
    };
    if (strncmp(s, "D3DBLEND_INVSRCALPHA", NSLEN) == 0)
    {
      valOut = D3DBLEND_INVSRCALPHA;
      return true;
    };
    if (strncmp(s, "D3DBLEND_DESTALPHA", NSLEN) == 0)
    {
      valOut = D3DBLEND_DESTALPHA;
      return true;
    };
    if (strncmp(s, "D3DBLEND_INVDESTALPHA", NSLEN) == 0)
    {
      valOut = D3DBLEND_INVDESTALPHA;
      return true;
    };
    if (strncmp(s, "D3DBLEND_DESTCOLOR", NSLEN) == 0)
    {
      valOut = D3DBLEND_DESTCOLOR;
      return true;
    };
    if (strncmp(s, "D3DBLEND_INVDESTCOLOR", NSLEN) == 0)
    {
      valOut = D3DBLEND_INVDESTCOLOR;
      return true;
    };
    if (strncmp(s, "D3DBLEND_SRCALPHASAT", NSLEN) == 0)
    {
      valOut = D3DBLEND_SRCALPHASAT;
      return true;
    };
    if (strncmp(s, "D3DBLEND_BOTHSRCALPHA", NSLEN) == 0)
    {
      valOut = D3DBLEND_BOTHSRCALPHA;
      return true;
    };
    if (strncmp(s, "D3DBLEND_BOTHINVSRCALPHA", NSLEN) == 0)
    {
      valOut = D3DBLEND_BOTHINVSRCALPHA;
      return true;
    };
    if (strncmp(s, "D3DBLEND_BLENDFACTOR", NSLEN) == 0)
    {
      valOut = D3DBLEND_BLENDFACTOR;
      return true;
    };
    if (strncmp(s, "D3DBLEND_INVBLENDFACTOR", NSLEN) == 0)
    {
      valOut = D3DBLEND_INVBLENDFACTOR;
      return true;
    };


    return false;
  };

  #pragma warning(pop)


  //=====================================================
  GB_D3D9_API std::string D3DCULL_tostr(const D3DCULL val)
  {
    std::string s;

    switch (val)
    {

      case D3DCULL_NONE:
        {
          s = "D3DCULL_NONE";
        }
        break;
      case D3DCULL_CW:
        {
          s = "D3DCULL_CW";
        }
        break;
      case D3DCULL_CCW:
        {
          s = "D3DCULL_CCW";
        }
        break;

      default:
        {

        }
        ;

    };

    return s;
  };

  //========================================================
  GB_D3D9_API bool D3DCULL_fromstr(D3DCULL &valOut, const std::string &str)
  {

    if (str == "D3DCULL_NONE")
    {
      valOut = D3DCULL_NONE;
      return true;
    };
    if (str == "D3DCULL_CW")
    {
      valOut = D3DCULL_CW;
      return true;
    };
    if (str == "D3DCULL_CCW")
    {
      valOut = D3DCULL_CCW;
      return true;
    };

    return false;
  };


  //========================================================
  GB_D3D9_API std::string D3DCMPFUNC_tostr(const D3DCMPFUNC val)
  {
    std::string s;

    switch (val)
    {

      case D3DCMP_NEVER:
        {
          s = "D3DCMP_NEVER";
        }
        break;
      case D3DCMP_LESS:
        {
          s = "D3DCMP_LESS";
        }
        break;
      case D3DCMP_EQUAL:
        {
          s = "D3DCMP_EQUAL";
        }
        break;
      case D3DCMP_LESSEQUAL:
        {
          s = "D3DCMP_LESSEQUAL";
        }
        break;
      case D3DCMP_GREATER:
        {
          s = "D3DCMP_GREATER";
        }
        break;
      case D3DCMP_NOTEQUAL:
        {
          s = "D3DCMP_NOTEQUAL";
        }
        break;
      case D3DCMP_GREATEREQUAL:
        {
          s = "D3DCMP_GREATEREQUAL";
        }
        break;
      case D3DCMP_ALWAYS:
        {
          s = "D3DCMP_ALWAYS";
        }
        break;

      default:
        {
          //  not found !
        }
        ;

    };

    return s;
  };

  //=====================================================
  GB_D3D9_API bool D3DCMPFUNC_fromstr(D3DCMPFUNC &valOut, 
										const std::string &str)
  {
    if (str == "D3DCMP_NEVER")
    {
      valOut = D3DCMP_NEVER;
      return true;
    };
    if (str == "D3DCMP_LESS")
    {
      valOut = D3DCMP_LESS;
      return true;
    };
    if (str == "D3DCMP_EQUAL")
    {
      valOut = D3DCMP_EQUAL;
      return true;
    };
    if (str == "D3DCMP_LESSEQUAL")
    {
      valOut = D3DCMP_LESSEQUAL;
      return true;
    };
    if (str == "D3DCMP_GREATER")
    {
      valOut = D3DCMP_GREATER;
      return true;
    };
    if (str == "D3DCMP_NOTEQUAL")
    {
      valOut = D3DCMP_NOTEQUAL;
      return true;
    };
    if (str == "D3DCMP_GREATEREQUAL")
    {
      valOut = D3DCMP_GREATEREQUAL;
      return true;
    };
    if (str == "D3DCMP_ALWAYS")
    {
      valOut = D3DCMP_ALWAYS;
      return true;
    };

    return false;
  };


  //=================================================================
  GB_D3D9_API std::string D3DFOGMODE_tostr(const D3DFOGMODE val)
  {
    std::string s;

    switch (val)
    {
      case D3DFOG_NONE:
        {
          s = "D3DFOG_NONE";
        }
        break;
      case D3DFOG_EXP:
        {
          s = "D3DFOG_EXP";
        }
        break;
      case D3DFOG_EXP2:
        {
          s = "D3DFOG_EXP2";
        }
        break;
      case D3DFOG_LINEAR:
        {
          s = "D3DFOG_LINEAR";
        }
        break;


      default:
        {
          // not found .
        }
        ;

    }; // switch

    return s;
  };

  //=====================================================
  GB_D3D9_API bool D3DFOGMODE_fromstr(D3DFOGMODE &valOut, 
										 const std::string	 &str)
  {

    if (str == "D3DFOG_NONE")
    {
      valOut = D3DFOG_NONE;
      return true;
    };
    if (str == "D3DFOG_EXP")
    {
      valOut = D3DFOG_EXP;
      return true;
    };
    if (str == "D3DFOG_EXP2")
    {
      valOut = D3DFOG_EXP2;
      return true;
    };
    if (str == "D3DFOG_LINEAR")
    {
      valOut = D3DFOG_LINEAR;
      return true;
    };

    return false;
  };


  //=========================================================================
  GB_D3D9_API std::string D3DSTENCILOP_tostr(const D3DSTENCILOP val)
  {
    std::string s;

    switch (val)
    {

      case D3DSTENCILOP_KEEP:
        {
          s = "D3DSTENCILOP_KEEP";
        }
        break;
      case D3DSTENCILOP_ZERO:
        {
          s = "D3DSTENCILOP_ZERO";
        }
        break;
      case D3DSTENCILOP_REPLACE:
        {
          s = "D3DSTENCILOP_REPLACE";
        }
        break;
      case D3DSTENCILOP_INCRSAT:
        {
          s = "D3DSTENCILOP_INCRSAT";
        }
        break;
      case D3DSTENCILOP_DECRSAT:
        {
          s = "D3DSTENCILOP_DECRSAT";
        }
        break;
      case D3DSTENCILOP_INVERT:
        {
          s = "D3DSTENCILOP_INVERT";
        }
        break;
      case D3DSTENCILOP_INCR:
        {
          s = "D3DSTENCILOP_INCR";
        }
        break;
      case D3DSTENCILOP_DECR:
        {
          s = "D3DSTENCILOP_DECR";
        }
        break;


      default:
        {

        }
        ;

    }; // switch

    return s;
  };

  //=========================================================================
  GB_D3D9_API bool D3DSTENCILOP_fromstr(D3DSTENCILOP &valOut, const std::string
                                        &str)
  {
    if (str == "D3DSTENCILOP_KEEP")
    {
      valOut = D3DSTENCILOP_KEEP;
      return true;
    };
    if (str == "D3DSTENCILOP_ZERO")
    {
      valOut = D3DSTENCILOP_ZERO;
      return true;
    };
    if (str == "D3DSTENCILOP_REPLACE")
    {
      valOut = D3DSTENCILOP_REPLACE;
      return true;
    };
    if (str == "D3DSTENCILOP_INCRSAT")
    {
      valOut = D3DSTENCILOP_INCRSAT;
      return true;
    };
    if (str == "D3DSTENCILOP_DECRSAT")
    {
      valOut = D3DSTENCILOP_DECRSAT;
      return true;
    };
    if (str == "D3DSTENCILOP_INVERT")
    {
      valOut = D3DSTENCILOP_INVERT;
      return true;
    };
    if (str == "D3DSTENCILOP_INCR")
    {
      valOut = D3DSTENCILOP_INCR;
      return true;
    };
    if (str == "D3DSTENCILOP_DECR")
    {
      valOut = D3DSTENCILOP_DECR;
      return true;
    };

    return false;
  };












  //=======================================================================

 
  } // end namespace		 
  } // end namespace
  } // end namespace
  } // end namespace
 

#endif 
// end file