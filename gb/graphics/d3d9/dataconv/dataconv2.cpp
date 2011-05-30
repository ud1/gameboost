#include "d3d9pch.h"
//#include "pch.h"

#if ( defined(GB_D3D9) && defined(WIN32) )

  #include <gb/graphics/d3d9/dataconv/dataconv.h>

  #include <gb/str/String.h>

  #include <string>
  #include <string.h>


  #pragma warning(push)
  #pragma warning(disable : 4996)



  namespace gb
  {
  namespace graphics
  {
  namespace d3d9
  {
  namespace dataconv
  {


  //=======================================================================




  //=====================================================
  static const char *RenderStateColor_toCstr(D3DCOLOR val)
  {
    static char ss[16];
    ss[0] = 0;

    sprintf(ss, "%X", (unsigned long)val);

    return ss;
  };

  //=================================================================
  static bool RenderStateColor_fromCstr(D3DCOLOR &val, const char *s)
  {
    unsigned long ul_val = 0;
    const int NSRES = sscanf(s, "%u", &ul_val);
    if (NSRES != 1)
    {
      return false;
    }


    val = (D3DCOLOR)ul_val;


    return true;
  };


  //=================================================================
  static std::string RenderStateFloat_tostr(const DWORD val)
  {
    union __uni_fldw
    {
      DWORD dw;
      float fl;
    };

    __uni_fldw un;
    un.dw = val;

    float fval = un.fl;

	  char buf[16];
      buf[0] = 0;
    sprintf(buf, "%f", val);

	std::string res = buf;
    return   res;
  };

  //=========================================================================
  static bool RenderStateFloat_fromstr(DWORD &val, const std::string& s)
  {

    float fval = 0.0f;
    const int NSCANRES = sscanf(s.c_str(), "%f", &fval);
    if (NSCANRES != 1)
    {
      return false;
    }

    union __uni_fldw
    {
      DWORD dw;
      float fl;
    };

    __uni_fldw un;
    un.fl = fval;
    val = un.dw;


    return true;
  };


  //=========================================================================
  static const char *RenderStateDwordHex_toCstr(DWORD val)
  {
    static char ss[16];
    ss[0] = 0;

    sprintf(ss, "%X", val);
    return ss;
  };

  //=========================================================================
  static bool __RenderStateDwordHex_fromCstr(DWORD &val, const char *s)
  {
    unsigned long ulng = 0;
    const int NSCANRES = sscanf(s, "%X", &ulng);
    val = (DWORD)ulng;
    if (NSCANRES != 1)
    {
      return false;
    }
    return true;
  };

  //========================================================================= 
  static bool __RenderStateBoolean_fromCstr(DWORD val, const char *s)
  {
    if (strcmp(s, "1") == 0)
    {
      val = 1;
      return true;
    }

    if (strcmp(s, "0") == 0)
    {
      val = 0;
      return true;
    }

    return false;
  }





  //=========================================================
GB_D3D9_API   std::string D3DMATERIALCOLORSOURCE_tostr(const D3DMATERIALCOLORSOURCE val,
													   bool bShortWord )
  {
    std::string s;

    switch (val)
    {

      case D3DMCS_MATERIAL:
        {
          s = "D3DMCS_MATERIAL";
        }
        break;
      case D3DMCS_COLOR1:
        {
          s = "D3DMCS_COLOR1";
        }
        break;
      case D3DMCS_COLOR2:
        {
          s = "D3DMCS_COLOR2";
        }
        break;

      default:
        {

        }

    } // switch


	std::string res;
	if(bShortWord)
	{
	  res = s.c_str() + 7; // D3DMCS_
	}
	else
	{
	  res = s;
	}

    return res;
  };

  //=========================================================
 GB_D3D9_API  bool D3DMATERIALCOLORSOURCE_fromstr(D3DMATERIALCOLORSOURCE &val, 
												  const std::string &strarg,
												  bool bShortWord )
  {

	  std::string str;
	  if(bShortWord)
	  {
		  str = "D3DMCS_";
		  str += strarg;
	  }
	  else
	  {
		  str = strarg;
	  }



    if (str == "D3DMCS_MATERIAL")
    {
      val = D3DMCS_MATERIAL;
      return true;
    }

    if (str == "D3DMCS_COLOR1")
    {
      val = D3DMCS_COLOR1;
      return true;
    }

    if (str == "D3DMCS_COLOR2")
    {
      val = D3DMCS_COLOR2;
      return true;
    }

    return false;
  }

  //======================================================
GB_D3D9_API   std::string D3DVERTEXBLENDFLAGS_tostr(const D3DVERTEXBLENDFLAGS val,
													bool bShortWord )
  {
    std::string s;

    switch (val)
    {

      case D3DVBF_DISABLE:
        {
          s = "D3DVBF_DISABLE";
        }
        break;

      case D3DVBF_1WEIGHTS:
        {
          s = "D3DVBF_1WEIGHTS";
        }
        break;

      case D3DVBF_2WEIGHTS:
        {
          s = "D3DVBF_2WEIGHTS";
        }
        break;

      case D3DVBF_3WEIGHTS:
        {
          s = "D3DVBF_3WEIGHTS";
        }
        break;

      case D3DVBF_TWEENING:
        {
          s = "D3DVBF_TWEENING";
        }
        break;

      case D3DVBF_0WEIGHTS:
        {
          s = "D3DVBF_0WEIGHTS";
        }
        break;

      default:
        {

        }

    } // switch

	if(!s.length())
	{
		return s;
	}

	std::string res;
	if(bShortWord)
	{
		res = s.c_str() + 7; // D3DVBF_
	}
	else
	{
		res = s;
	}
 
    return  res;
  };

  //=============================================================
 GB_D3D9_API  bool D3DVERTEXBLENDFLAGS_fromstr(D3DVERTEXBLENDFLAGS &val, 
											const std::string& strarg,
											bool bShortWord)
  {

	  std::string str;
	  if(bShortWord)
	  {
		  str = "D3DVBF_";
		  str += strarg;
	  }
	  else
	  {
		  str = strarg;
	  }


    if (str == "D3DVBF_DISABLE")
    {
      val = D3DVBF_DISABLE;
      return true;
    }

    if (str == "D3DVBF_1WEIGHTS")
    {
      val = D3DVBF_1WEIGHTS;
      return true;
    }

    if (str == "D3DVBF_2WEIGHTS")
    {
      val = D3DVBF_2WEIGHTS;
      return true;
    };

    if (str == "D3DVBF_3WEIGHTS")
    {
      val = D3DVBF_3WEIGHTS;
      return true;
    }

    if (str == "D3DVBF_TWEENING")
    {
      val = D3DVBF_TWEENING;
      return true;
    }

    if (str == "D3DVBF_0WEIGHTS")
    {
      val = D3DVBF_0WEIGHTS;
      return true;
    }

    return false;
  }

  //======================================================
  GB_D3D9_API  std::string D3DDEGREETYPE_tostr(const D3DDEGREETYPE val, bool bShortWord)
  {
    std::string s;

    switch (val)
    {
      case D3DDEGREE_LINEAR:
        {
          s = "D3DDEGREE_LINEAR";
        }
        break;
      case D3DDEGREE_QUADRATIC:
        {
          s = "D3DDEGREE_QUADRATIC";
        }
        break;
      case D3DDEGREE_CUBIC:
        {
          s = "D3DDEGREE_CUBIC";
        }
        break;
      case D3DDEGREE_QUINTIC:
        {
          s = "D3DDEGREE_QUINTIC";
        }
        break;

      default:
        {

        }

    } // switch

    return s;
  };

  //=====================================================
  GB_D3D9_API   bool D3DDEGREETYPE_fromstr(D3DDEGREETYPE &val, 
										  const std::string &s,
										  bool bShortWord)
  {
    if (s == "D3DDEGREE_LINEAR")
    {
      val = D3DDEGREE_LINEAR;
      return true;
    };
    if (s == "D3DDEGREE_QUADRATIC")
    {
      val = D3DDEGREE_QUADRATIC;
      return true;
    };
    if (s == "D3DDEGREE_CUBIC")
    {
      val = D3DDEGREE_CUBIC;
      return true;
    };
    if (s == "D3DDEGREE_QUINTIC")
    {
      val = D3DDEGREE_QUINTIC;
      return true;
    };

    return false;
  };



  //=====================================================
   GB_D3D9_API  std::string D3DPATCHEDGESTYLE_tostr(const D3DPATCHEDGESTYLE val,
													 bool bShortWord)
  {
    std::string s;

    switch (val)
    {
      case D3DPATCHEDGE_DISCRETE:
        {
          s = "D3DPATCHEDGE_DISCRETE";
        }
        break;
      case D3DPATCHEDGE_CONTINUOUS:
        {
          s = "D3DPATCHEDGE_CONTINUOUS";
        }
        break;

      default:
        {

        }

    } // switch

    return s;
  };

  //===============================================
  GB_D3D9_API   bool D3DPATCHEDGESTYLE_fromstr(D3DPATCHEDGESTYLE &val, 
											   const std::string &s,
											   bool bShortWord)
  {
    if (s == "D3DPATCHEDGE_DISCRETE")
    {
      val = D3DPATCHEDGE_DISCRETE;
      return true;
    };
    if (s == "D3DPATCHEDGE_CONTINUOUS")
    {
      val = D3DPATCHEDGE_CONTINUOUS;
      return true;
    };

    return false;
  }

  //======================================================
  GB_D3D9_API   std::string D3DDEBUGMONITORTOKENS_tostr(
							const D3DDEBUGMONITORTOKENS val,
							bool bShortWord)
  {
    std::string s;
    switch (val)
    {

      case D3DDMT_ENABLE:
        {
          s = "D3DDMT_ENABLE";
        }
        break;

      case D3DDMT_DISABLE:
        {
          s = "D3DDMT_DISABLE";
        }
        break;

      default:
        {

        }

    } // switch

    if(!s.length())
  {
	  return s;
  }

	std::string res;
	if(bShortWord)
	{								 
	 res = s.c_str() +  7; //  D3DDMT_
	}
	else
	{
	 res = s;
	}

	return res;


    return s;
  };

  //============================================
  GB_D3D9_API   bool D3DDEBUGMONITORTOKENS_fromstr(D3DDEBUGMONITORTOKENS &val, 
										const std::string &strarg,
										bool bShortWord)
  {

  	std::string str;
  if(bShortWord)
  {
    str = "D3DDMT_";
    str += strarg;
  }
  else
  {
    str = strarg;
  }

    if (str == "D3DDMT_ENABLE")
    {
      val = D3DDMT_ENABLE;
      return true;
    }

    if (str == "D3DDMT_DISABLE")
    {
      val = D3DDMT_DISABLE;
      return true;
    }

    return false;
  };




  //=========================================================================
GB_D3D9_API   std::string D3DRENDERSTATEVALUE_tostr(
					const D3DRENDERSTATETYPE state, 
					const DWORD val,
					bool bShortWord )
  {
    std::string ss;
    ss.reserve(64);

    switch (state)
    {


      case D3DRS_ZENABLE:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
          ;
        }
        break;


      case D3DRS_FILLMODE:
        {
          ss = D3DFILLMODE_tostr((D3DFILLMODE)val, bShortWord);
        }
        break;


      case D3DRS_SHADEMODE:
        {
          ss = D3DSHADEMODE_tostr((D3DSHADEMODE)val, bShortWord);
        }
        break;


      case D3DRS_ZWRITEENABLE:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
          ;
        }
        break;

      case D3DRS_ALPHATESTENABLE:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
          ;
        }
        break;

      case D3DRS_LASTPIXEL:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
          ;
        }
        break;


      case D3DRS_SRCBLEND:
        {
          ss = D3DBLEND_tostr((D3DBLEND)val, bShortWord);
        }
        break;

      case D3DRS_DESTBLEND:
        {
          ss = D3DBLEND_tostr((D3DBLEND)val, bShortWord);
        }
        break;


      case D3DRS_CULLMODE:
        {
          ss = D3DCULL_tostr((D3DCULL)val, bShortWord);
        }
        break;


      case D3DRS_ZFUNC:
        {
          ss = D3DCMPFUNC_tostr((D3DCMPFUNC)val, bShortWord);
        }
        break;



      case D3DRS_ALPHAREF:
        {
          ss = gb::str::uintToStr((UINT)val, true);
        }
        break;


      case D3DRS_ALPHAFUNC:
        {
          ss = D3DCMPFUNC_tostr((D3DCMPFUNC)val, bShortWord);
        }
        break;

      case D3DRS_DITHERENABLE:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
          ;
        }
        break;

      case D3DRS_ALPHABLENDENABLE:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
          ;
        }
        break;

      case D3DRS_FOGENABLE:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
          ;
        }
        break;

      case D3DRS_SPECULARENABLE:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
          ;
        }
        break;

      case D3DRS_FOGCOLOR:
        {
          ss = RenderStateColor_toCstr( (D3DCOLOR)val );
        }
        break;

      case D3DRS_FOGTABLEMODE:
        {
          ss = D3DFOGMODE_tostr((D3DFOGMODE)val, bShortWord);
        }
        break;

      case D3DRS_FOGSTART:
        {
          ss = RenderStateFloat_tostr(val);
        }
        break;

      case D3DRS_FOGEND:
        {
          ss = RenderStateFloat_tostr(val);
        }
        break;

      case D3DRS_FOGDENSITY:
        {
          ss = RenderStateFloat_tostr(val);
        }
        break;

      case D3DRS_RANGEFOGENABLE:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
 
        }
        break;



      case D3DRS_STENCILENABLE:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
 
        }
        break;

      case D3DRS_STENCILFAIL:
        {
          ss = D3DSTENCILOP_tostr((D3DSTENCILOP)val, bShortWord);
        }
        break;

      case D3DRS_STENCILZFAIL:
        {
          ss = D3DSTENCILOP_tostr((D3DSTENCILOP)val, bShortWord);
        }
        break;


      case D3DRS_STENCILPASS:
        {
          ss = D3DSTENCILOP_tostr((D3DSTENCILOP)val, bShortWord);
        }
        break;

      case D3DRS_STENCILFUNC:
        {
          ss = D3DCMPFUNC_tostr((D3DCMPFUNC)val, bShortWord);
        }
        break;


      case D3DRS_STENCILREF:
        {
          ss = gb::str::uintToStr(val, false);
        }
        break;



      case D3DRS_STENCILMASK:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;
		
      case D3DRS_STENCILWRITEMASK:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;


      case D3DRS_TEXTUREFACTOR:
        {
          ss = RenderStateColor_toCstr((D3DCOLOR)val);
        }
        break;


      case D3DRS_WRAP0:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;
		
      case D3DRS_WRAP1:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;
		
      case D3DRS_WRAP2:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;
		
      case D3DRS_WRAP3:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;
		
      case D3DRS_WRAP4:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;
		
      case D3DRS_WRAP5:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;
		
      case D3DRS_WRAP6:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;
		
      case D3DRS_WRAP7:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;




      case D3DRS_CLIPPING:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
          ;
        }
        break;
		
      case D3DRS_LIGHTING:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
 
        }
        break;


      case D3DRS_AMBIENT:
        {
          ss = RenderStateColor_toCstr((D3DCOLOR)val);
        }
        break;

      case D3DRS_FOGVERTEXMODE:
        {
          ss = D3DFOGMODE_tostr((D3DFOGMODE)val, bShortWord);
        }
        break;

      case D3DRS_COLORVERTEX:
        {
          ss = RenderStateColor_toCstr((D3DCOLOR)val);
        }
        break;

      case D3DRS_LOCALVIEWER:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
 
        }
        break;
		
      case D3DRS_NORMALIZENORMALS:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
 
        }
        break;


      case D3DRS_DIFFUSEMATERIALSOURCE:
        {
          ss = D3DMATERIALCOLORSOURCE_tostr((D3DMATERIALCOLORSOURCE)val, bShortWord );
        }
        break;
      case D3DRS_SPECULARMATERIALSOURCE:
        {
          ss = D3DMATERIALCOLORSOURCE_tostr((D3DMATERIALCOLORSOURCE)val, bShortWord );
        }
        break;
		
      case D3DRS_AMBIENTMATERIALSOURCE:
        {
          ss = D3DMATERIALCOLORSOURCE_tostr((D3DMATERIALCOLORSOURCE)val, bShortWord );
        }
        break;
		
      case D3DRS_EMISSIVEMATERIALSOURCE:
        {
          ss = D3DMATERIALCOLORSOURCE_tostr((D3DMATERIALCOLORSOURCE)val, bShortWord );
        }
        break;

      case D3DRS_VERTEXBLEND:
        {
          ss = D3DVERTEXBLENDFLAGS_tostr((D3DVERTEXBLENDFLAGS)val, bShortWord );
        }
        break;



      case D3DRS_CLIPPLANEENABLE:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;


      case D3DRS_POINTSIZE:
        {
          ss = RenderStateFloat_tostr(val);
        }
        break;
		
      case D3DRS_POINTSIZE_MIN:
        {
          ss = RenderStateFloat_tostr(val);
        }
        break;


      case D3DRS_POINTSPRITEENABLE:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
 
        }
        break;

      case D3DRS_POINTSCALEENABLE:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
 
        }
        break;


      case D3DRS_POINTSCALE_A:
        {
          ss = RenderStateFloat_tostr(val);
        }
        break;
		
      case D3DRS_POINTSCALE_B:
        {
          ss = RenderStateFloat_tostr(val);
        }
        break;
		
      case D3DRS_POINTSCALE_C:
        {
          ss = RenderStateFloat_tostr(val);
        }
        break;


      case D3DRS_MULTISAMPLEANTIALIAS:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
 
        }
        break;
		
      case D3DRS_MULTISAMPLEMASK:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;
		
      case D3DRS_PATCHEDGESTYLE:
        {
          ss = D3DPATCHEDGESTYLE_tostr((D3DPATCHEDGESTYLE)val, bShortWord );
        }
        break;
		
      case D3DRS_DEBUGMONITORTOKEN:
        {
          ss = D3DDEBUGMONITORTOKENS_tostr((D3DDEBUGMONITORTOKENS)val, bShortWord );
        }
        break;

      case D3DRS_POINTSIZE_MAX:
        {
          ss = RenderStateFloat_tostr(val);
        }
        break;
		
      case D3DRS_INDEXEDVERTEXBLENDENABLE:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
 
        }
        break;

      case D3DRS_COLORWRITEENABLE:
        {
          ss = gb::str::uintToStr((UINT)val, false);
        }
        break;
		
      case D3DRS_TWEENFACTOR:
        {
          ss = RenderStateFloat_tostr(val);
        }
        break;


      case D3DRS_BLENDOP:
        {
          ss = D3DBLEND_tostr((D3DBLEND)val, bShortWord );
        }
        break;


      case D3DRS_POSITIONDEGREE:
        {
          ss = D3DDEGREETYPE_tostr((D3DDEGREETYPE)val, bShortWord );
        }
        break;
		
      case D3DRS_NORMALDEGREE:
        {
          ss = D3DDEGREETYPE_tostr((D3DDEGREETYPE)val, bShortWord );
        }
        break;

      case D3DRS_SCISSORTESTENABLE:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
 
        }
        break;
		
      case D3DRS_SLOPESCALEDEPTHBIAS:
        {
          ss = gb::str::uintToStr((UINT)val, true);
        }
        break;


      case D3DRS_ANTIALIASEDLINEENABLE:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
 
        }
        break;

      case D3DRS_MINTESSELLATIONLEVEL:
        {
          ss = RenderStateFloat_tostr(val);
        }
        break;
		
      case D3DRS_MAXTESSELLATIONLEVEL:
        {
          ss = RenderStateFloat_tostr(val);
        }
        break;


      case D3DRS_ADAPTIVETESS_X:
        {
          ss = RenderStateFloat_tostr(val);
        }
        break;
		
      case D3DRS_ADAPTIVETESS_Y:
        {
          ss = RenderStateFloat_tostr(val);
        }
        break;
		
      case D3DRS_ADAPTIVETESS_Z:
        {
          ss = RenderStateFloat_tostr(val);
        }
        break;
		
      case D3DRS_ADAPTIVETESS_W:
        {
          ss = RenderStateFloat_tostr(val);
        }
        break;


      case D3DRS_ENABLEADAPTIVETESSELLATION:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
 
        }
        break;
		
      case D3DRS_TWOSIDEDSTENCILMODE:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }
 
        }
        break;


      case D3DRS_CCW_STENCILFAIL:
        {
          ss = D3DSTENCILOP_tostr((D3DSTENCILOP)val, bShortWord );
        }
        break;
		
      case D3DRS_CCW_STENCILZFAIL:
        {
          ss = D3DSTENCILOP_tostr((D3DSTENCILOP)val, bShortWord );
        }
        break;
		
      case D3DRS_CCW_STENCILPASS:
        {
          ss = D3DSTENCILOP_tostr((D3DSTENCILOP)val, bShortWord );
        }
        break;


      case D3DRS_CCW_STENCILFUNC:
        {
          ss = D3DCMPFUNC_tostr((D3DCMPFUNC)val, bShortWord );
        }
        break;


      case D3DRS_COLORWRITEENABLE1:
        {
          ss = RenderStateDwordHex_toCstr(val  );
        }
        break;
		
      case D3DRS_COLORWRITEENABLE2:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;
		
      case D3DRS_COLORWRITEENABLE3:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;


      case D3DRS_BLENDFACTOR:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;
		
      case D3DRS_SRGBWRITEENABLE:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }

        }
        break;
		
      case D3DRS_DEPTHBIAS:
        {
          ss = RenderStateFloat_tostr(val);
        }
        break;


      case D3DRS_WRAP8:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;
		
      case D3DRS_WRAP9:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;
		
      case D3DRS_WRAP10:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;
		
      case D3DRS_WRAP11:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;
		
      case D3DRS_WRAP12:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;
		
      case D3DRS_WRAP13:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;
		
      case D3DRS_WRAP14:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;
		
      case D3DRS_WRAP15:
        {
          ss = RenderStateDwordHex_toCstr(val);
        }
        break;

      case D3DRS_SEPARATEALPHABLENDENABLE:
        {
          if (val)
          {
            ss = "1";
          }
          else
          {
            ss = "0";
          }

        }
        break;

      case D3DRS_SRCBLENDALPHA:
        {
          ss = D3DBLEND_tostr((D3DBLEND)val, bShortWord );
        }
        break;
		
      case D3DRS_DESTBLENDALPHA:
        {
          ss = D3DBLEND_tostr((D3DBLEND)val, bShortWord );
        }
        break;
		
      case D3DRS_BLENDOPALPHA:
        {
          ss = D3DBLEND_tostr((D3DBLEND)val, bShortWord );
        }
        break;



		default:
		{

		}


    } // switch



    return ss;
  };


  //============================================================
GB_D3D9_API   bool D3DRENDERSTATEVALUE_fromstr(DWORD &val, 
											   const D3DRENDERSTATETYPE state, 
											   const std::string &s, 
											   bool bShortWord )
  {
	  

    switch (state)
    {

      case D3DRS_ZENABLE:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_FILLMODE:
        {
          return D3DFILLMODE_fromstr((D3DFILLMODE &)val, s, bShortWord );
        }
        break;

      case D3DRS_SHADEMODE:
        {
          return D3DSHADEMODE_fromstr((D3DSHADEMODE &)val, s, bShortWord );
        }
        break;

      case D3DRS_ZWRITEENABLE:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_ALPHATESTENABLE:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_LASTPIXEL:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_SRCBLEND:
        {
          return D3DBLEND_fromstr((D3DBLEND &)val, s, bShortWord );
        }
        break;
      case D3DRS_DESTBLEND:
        {
          return D3DBLEND_fromstr((D3DBLEND &)val, s, bShortWord );
        }
        break;

      case D3DRS_CULLMODE:
        {
          return D3DCULL_fromstr((D3DCULL &)val, s, bShortWord );
        }
        break;

      case D3DRS_ZFUNC:
        {
          return D3DCMPFUNC_fromstr((D3DCMPFUNC &)val, s, bShortWord );
        }
        break;

      case D3DRS_ALPHAREF:
        {
          return gb::str::uintFromCstr((uint32_t &)val, s.c_str());
        }
        break;

      case D3DRS_ALPHAFUNC:
        {
          return D3DCMPFUNC_fromstr((D3DCMPFUNC &)val, s, bShortWord );
        }
        break;

      case D3DRS_DITHERENABLE:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_ALPHABLENDENABLE:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_FOGENABLE:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_SPECULARENABLE:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_FOGCOLOR:
        {
          return RenderStateColor_fromCstr((D3DCOLOR &)val, s.c_str());
        }
        break;



      case D3DRS_FOGTABLEMODE:
        {
          return D3DFOGMODE_fromstr((D3DFOGMODE &)val, s, bShortWord );
        }
        break;
      case D3DRS_FOGSTART:
        {
          return RenderStateFloat_fromstr(val, s );
        }
        break;
      case D3DRS_FOGEND:
        {
          return RenderStateFloat_fromstr(val, s );
        }
        break;
      case D3DRS_FOGDENSITY:
        {
          return RenderStateFloat_fromstr(val, s );
        }
        break;

      case D3DRS_RANGEFOGENABLE:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_STENCILENABLE:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_STENCILFAIL:
        {
          return D3DSTENCILOP_fromstr((D3DSTENCILOP &)val, s, bShortWord );
        }
        break;

      case D3DRS_STENCILZFAIL:
        {
          return D3DSTENCILOP_fromstr((D3DSTENCILOP &)val, s, bShortWord );
        }
        break;

      case D3DRS_STENCILPASS:
        {
          return D3DSTENCILOP_fromstr((D3DSTENCILOP &)val, s, bShortWord );
        }
        break;

      case D3DRS_STENCILFUNC:
        {
          return D3DCMPFUNC_fromstr((D3DCMPFUNC &)val, s, bShortWord );
        }
        break;

      case D3DRS_STENCILREF:
        {
          return gb::str::uintFromCstr((uint32_t &)val, s.c_str());
        }
        break;

      case D3DRS_STENCILMASK:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_STENCILWRITEMASK:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;


      case D3DRS_TEXTUREFACTOR:
        {
          return RenderStateColor_fromCstr((D3DCOLOR &)val, s.c_str());
        }
        break;

      case D3DRS_WRAP0:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_WRAP1:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_WRAP2:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_WRAP3:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_WRAP4:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_WRAP5:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str() );
        }
        break;

      case D3DRS_WRAP6:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str() );
        }
        break;

      case D3DRS_WRAP7:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str() );
        }
        break;


      case D3DRS_CLIPPING:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str() );
        }
        break;

      case D3DRS_LIGHTING:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str() );
        }
        break;

      case D3DRS_AMBIENT:
        {
          return RenderStateColor_fromCstr((D3DCOLOR &)val, s.c_str());
        }
        break;

      case D3DRS_FOGVERTEXMODE:
        {
          return D3DFOGMODE_fromstr((D3DFOGMODE &)val, s, bShortWord );
        }
        break;

      case D3DRS_COLORVERTEX:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_LOCALVIEWER:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_NORMALIZENORMALS:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_DIFFUSEMATERIALSOURCE:
        {
          return D3DMATERIALCOLORSOURCE_fromstr((D3DMATERIALCOLORSOURCE &)val, s, bShortWord );
        }
        break;

      case D3DRS_SPECULARMATERIALSOURCE:
        {
          return D3DMATERIALCOLORSOURCE_fromstr((D3DMATERIALCOLORSOURCE &)val, s, bShortWord );
        }
        break;

      case D3DRS_AMBIENTMATERIALSOURCE:
        {
          return D3DMATERIALCOLORSOURCE_fromstr((D3DMATERIALCOLORSOURCE &)val, s);
        }
        break;

      case D3DRS_EMISSIVEMATERIALSOURCE:
        {
          return D3DMATERIALCOLORSOURCE_fromstr((D3DMATERIALCOLORSOURCE &)val, s, bShortWord );
        }
        break;

      case D3DRS_VERTEXBLEND:
        {
          return D3DVERTEXBLENDFLAGS_fromstr((D3DVERTEXBLENDFLAGS &)val, s.c_str(), bShortWord );
        }
        break;

      case D3DRS_CLIPPLANEENABLE:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_POINTSIZE:
        {
          return RenderStateFloat_fromstr(val, s );
        }
        break;

      case D3DRS_POINTSIZE_MIN:
        {
          return RenderStateFloat_fromstr(val, s );
        }
        break;

      case D3DRS_POINTSPRITEENABLE:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_POINTSCALEENABLE:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_POINTSCALE_A:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_POINTSCALE_B:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_POINTSCALE_C:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_MULTISAMPLEANTIALIAS:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_MULTISAMPLEMASK:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_PATCHEDGESTYLE:
        {
          return D3DPATCHEDGESTYLE_fromstr((D3DPATCHEDGESTYLE &)val, s, bShortWord );
        }
        break;

      case D3DRS_DEBUGMONITORTOKEN:
        {
          return D3DDEBUGMONITORTOKENS_fromstr((D3DDEBUGMONITORTOKENS &)val, s, bShortWord );
        }
        break;

      case D3DRS_POINTSIZE_MAX:
        {
          return RenderStateFloat_fromstr(val, s );
        }
        break;

      case D3DRS_INDEXEDVERTEXBLENDENABLE:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_COLORWRITEENABLE:
        {
          return gb::str::uintFromCstr((uint32_t &)val, s.c_str());
        }
        break;

      case D3DRS_TWEENFACTOR:
        {
          return RenderStateFloat_fromstr(val, s );
        }
        break;

      case D3DRS_BLENDOP:
        {
          return D3DBLEND_fromstr((D3DBLEND &)val, s, bShortWord );
        }
        break;

      case D3DRS_POSITIONDEGREE:
        {
          return D3DDEGREETYPE_fromstr((D3DDEGREETYPE &)val, s, bShortWord );
        }
        break;

      case D3DRS_SCISSORTESTENABLE:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_SLOPESCALEDEPTHBIAS:
        {
          return gb::str::uintFromCstr((uint32_t &)val, s.c_str());
        }
        break;

      case D3DRS_ANTIALIASEDLINEENABLE:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_MINTESSELLATIONLEVEL:
        {
          return RenderStateFloat_fromstr(val, s );
        }
        break;

      case D3DRS_MAXTESSELLATIONLEVEL:
        {
          return RenderStateFloat_fromstr(val, s );
        }
        break;

      case D3DRS_ADAPTIVETESS_X:
        {
          return RenderStateFloat_fromstr(val, s );
        }
        break;

      case D3DRS_ADAPTIVETESS_Y:
        {
          return RenderStateFloat_fromstr(val, s );
        }
        break;

      case D3DRS_ADAPTIVETESS_Z:
        {
          return RenderStateFloat_fromstr(val, s );
        }
        break;

      case D3DRS_ADAPTIVETESS_W:
        {
          return RenderStateFloat_fromstr(val, s );
        }
        break;

      case D3DRS_ENABLEADAPTIVETESSELLATION:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_TWOSIDEDSTENCILMODE:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_CCW_STENCILFAIL:
        {
          return D3DSTENCILOP_fromstr((D3DSTENCILOP &)val, s, bShortWord );
        }
        break;

      case D3DRS_CCW_STENCILZFAIL:
        {
          return D3DSTENCILOP_fromstr((D3DSTENCILOP &)val, s, bShortWord );
        }
        break;

      case D3DRS_CCW_STENCILPASS:
        {
          return D3DSTENCILOP_fromstr((D3DSTENCILOP &)val, s, bShortWord );
        }
        break;

      case D3DRS_CCW_STENCILFUNC:
        {
          return D3DSTENCILOP_fromstr((D3DSTENCILOP &)val, s, bShortWord );
        }
        break;

      case D3DRS_COLORWRITEENABLE1:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_COLORWRITEENABLE2:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_COLORWRITEENABLE3:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_BLENDFACTOR:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_SRGBWRITEENABLE:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_DEPTHBIAS:
        {
          return RenderStateFloat_fromstr(val, s );
        }
        break;

      case D3DRS_WRAP8:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_WRAP9:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_WRAP10:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_WRAP11:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_WRAP12:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_WRAP13:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_WRAP14:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_WRAP15:
        {
          return __RenderStateDwordHex_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_SEPARATEALPHABLENDENABLE:
        {
          return __RenderStateBoolean_fromCstr(val, s.c_str());
        }
        break;

      case D3DRS_SRCBLENDALPHA:
        {
          return D3DBLEND_fromstr((D3DBLEND &)val, s, bShortWord );
        }
        break;

      case D3DRS_DESTBLENDALPHA:
        {
          return D3DBLEND_fromstr((D3DBLEND &)val, s, bShortWord );
        }
        break;

      case D3DRS_BLENDOPALPHA:
        {
          return D3DBLEND_fromstr((D3DBLEND &)val, s, bShortWord );
        }
        break;



      default:
        {

        }
 

    } // switch



    // not found
    return false;
  };




  #pragma warning(pop)

  //=======================================================================


  } // end namespace	 
  } // end namespace
  } // end namespace
  } // end namespace


#endif // #if ( defined(GB_D3D9) && defined(WIN32) )
// end file
