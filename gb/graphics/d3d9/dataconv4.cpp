
//#include "stdafx.h" 

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

//=========================================================

	// static std::string __val_tohex(DWORD val)
	// {
		// std::string res = "";
		// char buf [32];
		// buf[0] = '\0';
		// sprintf(buf, "0x%.8X", value );
		// res = buf;
		// return res;
	// }


/***********************************************************

bool __RSVALUE_fromstr(DWORD& valOut, const D3DRENDERSTATETYPE rstype, const std::string& str)
{
 switch(rstype)
 {
 
  case XXXX :
  {
  
  }
  break;
  
  
  
  
  
  
	 
	  default:
	  {
       // not found
	   return false;
	  
	  }
	 
 }
 // end switch




 return false;
}

*************************************/

 
// std::string D3DRENDERSTATEVALUE_tostr(const D3DRENDERSTATETYPE  rs, const DWORD val)
// {
	// std::string res = "";

  // switch(rs)
  // {

  

    // D3DRS_STENCILENABLE = 52,
    // D3DRS_STENCILFAIL = 53,
    // D3DRS_STENCILZFAIL = 54,
    // D3DRS_STENCILPASS = 55,
    // D3DRS_STENCILFUNC = 56,
    // D3DRS_STENCILREF = 57,
    // D3DRS_STENCILMASK = 58,
    // D3DRS_STENCILWRITEMASK = 59,
    // D3DRS_TEXTUREFACTOR = 60,
    // D3DRS_WRAP0 = 128,
    // D3DRS_WRAP1 = 129,
    // D3DRS_WRAP2 = 130,
    // D3DRS_WRAP3 = 131,
    // D3DRS_WRAP4 = 132,
    // D3DRS_WRAP5 = 133,
    // D3DRS_WRAP6 = 134,
    // D3DRS_WRAP7 = 135,
    // D3DRS_CLIPPING = 136,
    // D3DRS_LIGHTING = 137,
    // D3DRS_AMBIENT = 139,
    // D3DRS_FOGVERTEXMODE = 140,
    // D3DRS_COLORVERTEX = 141,
    // D3DRS_LOCALVIEWER = 142,
    // D3DRS_NORMALIZENORMALS = 143,
    // D3DRS_DIFFUSEMATERIALSOURCE = 145,
    // D3DRS_SPECULARMATERIALSOURCE = 146,
    // D3DRS_AMBIENTMATERIALSOURCE = 147,
    // D3DRS_EMISSIVEMATERIALSOURCE = 148,
    // D3DRS_VERTEXBLEND = 151,
    // D3DRS_CLIPPLANEENABLE = 152,
    // D3DRS_POINTSIZE = 154,
    // D3DRS_POINTSIZE_MIN = 155,
    // D3DRS_POINTSPRITEENABLE = 156,
    // D3DRS_POINTSCALEENABLE = 157,
    // D3DRS_POINTSCALE_A = 158,
    // D3DRS_POINTSCALE_B = 159,
    // D3DRS_POINTSCALE_C = 160,
    // D3DRS_MULTISAMPLEANTIALIAS = 161,
    // D3DRS_MULTISAMPLEMASK = 162,
    // D3DRS_PATCHEDGESTYLE = 163,
    // D3DRS_DEBUGMONITORTOKEN = 165,
    // D3DRS_POINTSIZE_MAX = 166,
    // D3DRS_INDEXEDVERTEXBLENDENABLE = 167,
    // D3DRS_COLORWRITEENABLE = 168,
    // D3DRS_TWEENFACTOR = 170,
    // D3DRS_BLENDOP = 171,
    // D3DRS_POSITIONDEGREE = 172,
    // D3DRS_NORMALDEGREE = 173,
    // D3DRS_SCISSORTESTENABLE = 174,
    // D3DRS_SLOPESCALEDEPTHBIAS = 175,
    // D3DRS_ANTIALIASEDLINEENABLE = 176,
    // D3DRS_MINTESSELLATIONLEVEL = 178,
    // D3DRS_MAXTESSELLATIONLEVEL = 179,
    // D3DRS_ADAPTIVETESS_X = 180,
    // D3DRS_ADAPTIVETESS_Y = 181,
    // D3DRS_ADAPTIVETESS_Z = 182,
    // D3DRS_ADAPTIVETESS_W = 183,
    // D3DRS_ENABLEADAPTIVETESSELLATION = 184,
    // D3DRS_TWOSIDEDSTENCILMODE = 185,
    // D3DRS_CCW_STENCILFAIL = 186,
    // D3DRS_CCW_STENCILZFAIL = 187,
    // D3DRS_CCW_STENCILPASS = 188,
    // D3DRS_CCW_STENCILFUNC = 189,
    // D3DRS_COLORWRITEENABLE1 = 190,
    // D3DRS_COLORWRITEENABLE2 = 191,
    // D3DRS_COLORWRITEENABLE3 = 192,
    // D3DRS_BLENDFACTOR = 193,
    // D3DRS_SRGBWRITEENABLE = 194,
    // D3DRS_DEPTHBIAS = 195,
    // D3DRS_WRAP8 = 198,
    // D3DRS_WRAP9 = 199,
    // D3DRS_WRAP10 = 200,
    // D3DRS_WRAP11 = 201,
    // D3DRS_WRAP12 = 202,
    // D3DRS_WRAP13 = 203,
    // D3DRS_WRAP14 = 204,
    // D3DRS_WRAP15 = 205,
    // D3DRS_SEPARATEALPHABLENDENABLE = 206,
    // D3DRS_SRCBLENDALPHA = 207,
    // D3DRS_DESTBLENDALPHA = 208,
    // D3DRS_BLENDOPALPHA = 209,
 
 
  
  
  
  // case D3DRS_ZENABLE : 
  // {
    // if(val)	{ res = "1"	} else	 { res = "0"; }	;

  // }
  // break;
 

  // case D3DRS_FILLMODE : 
	// {
	  // res = D3DFILLMODE_tostr( (D3DFILLMODE)val  );
	// }
	// break;


  // case D3DRS_SHADEMODE : 
	  // {
 	  // res = D3DSHADEMODE_tostr(  (D3DSHADEMODE)val  );
	  // }
	  // break;

  // case D3DRS_ZWRITEENABLE : 
	  // {
      // if(val)	{ res = "1"	} else	 { res = "0"; }	;
	  // }
	  // break;


  // case D3DRS_ALPHATESTENABLE : 
	  // {
	    // if(val)	{ res = "1"	} else	 { res = "0"; }	;
	  // }
	  // break;

     //  *****************************************

    // case D3DRS_LASTPIXEL : 
	  // {
	    // if(val)	{ res = "1"	} else	 { res = "0"; }	;;
	  // }
	  // break;



     // case D3DRS_SRCBLEND : 
	  // {
		  // res = dataconv::D3DBLEND_tostr(  (D3DBLEND)val );
	  // }
	  // break;

    // case D3DRS_DESTBLEND : 
	  // {
		  // res = dataconv::D3DBLEND_tostr(  (D3DBLEND)val );
	  // }
	  // break;

    // case D3DRS_CULLMODE : 
	  // {
		  // res = dataconv::D3DCULL_tostr(  (D3DCULL)val );
	  // }
	  // break;


    // case D3DRS_ZFUNC : 
	  // {
		  // res = dataconv::D3DCMPFUNC_tostr( (D3DCMPFUNC)val );
	  // }
	  // break;

    // case D3DRS_ALPHAREF : 
	  // {

	    // res = __val_tohex(val);
	  // }
	  // break;

    // case D3DRS_ALPHAFUNC : 
	  // {
		  // res dataconv::D3DCMPFUNC_tostr(  (D3DCMPFUNC)val );
	  // }
	  // break;


     // = 26,
     // = 27,
     // = 28,
     // = 29,
     // = 34,
    // D3DRS_FOGTABLEMODE = 35,
    // D3DRS_FOGSTART = 36,
    // D3DRS_FOGEND = 37,
    // D3DRS_FOGDENSITY = 38,
    // D3DRS_RANGEFOGENABLE = 48,



    // case D3DRS_DITHERENABLE : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case D3DRS_ALPHABLENDENABLE : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case D3DRS_FOGENABLE : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case D3DRS_SPECULARENABLE : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case D3DRS_FOGCOLOR : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case XXXXXXXXXXXXXXXXXXXXXX : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case XXXXXXXXXXXXXXXXXXXXXX : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case XXXXXXXXXXXXXXXXXXXXXX : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case XXXXXXXXXXXXXXXXXXXXXX : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case XXXXXXXXXXXXXXXXXXXXXX : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case XXXXXXXXXXXXXXXXXXXXXX : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case XXXXXXXXXXXXXXXXXXXXXX : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case XXXXXXXXXXXXXXXXXXXXXX : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case XXXXXXXXXXXXXXXXXXXXXX : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case XXXXXXXXXXXXXXXXXXXXXX : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case XXXXXXXXXXXXXXXXXXXXXX : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case XXXXXXXXXXXXXXXXXXXXXX : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case XXXXXXXXXXXXXXXXXXXXXX : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case XXXXXXXXXXXXXXXXXXXXXX : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case XXXXXXXXXXXXXXXXXXXXXX : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case XXXXXXXXXXXXXXXXXXXXXX : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case XXXXXXXXXXXXXXXXXXXXXX : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case XXXXXXXXXXXXXXXXXXXXXX : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;

    // case XXXXXXXXXXXXXXXXXXXXXX : 
	  // {
	    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;
	  // }
	  // break;








 





  // default:
	  // {

	  // }


  // }





// }

 


//=========================================================

}
}
}
}



#endif // #if ( defined(GB_D3D9) && defined(WIN32) )
// end file