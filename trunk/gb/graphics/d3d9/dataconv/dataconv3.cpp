#include "d3d9pch.h"

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




/*
{   D3DTADDRESS_WRAP = 1,
    D3DTADDRESS_MIRROR = 2,
    D3DTADDRESS_CLAMP = 3,
    D3DTADDRESS_BORDER = 4,
    D3DTADDRESS_MIRRORONCE = 5,
	
} D3DTEXTUREADDRESS 
*/

static const char CSTR_D3DTADDRESS_WRAP        []   = "D3DTADDRESS_WRAP" ;
static const char CSTR_D3DTADDRESS_MIRROR      []   = "D3DTADDRESS_MIRROR" ;
static const char CSTR_D3DTADDRESS_CLAMP       []   = "D3DTADDRESS_CLAMP" ;
static const char CSTR_D3DTADDRESS_BORDER      []   = "D3DTADDRESS_BORDER" ;
static const char CSTR_D3DTADDRESS_MIRRORONCE  []   = "D3DTADDRESS_MIRRORONCE" ;


//=================================================================================
GB_D3D9_API  std::string  D3DTEXTUREADDRESS_tostr(const D3DTEXTUREADDRESS val)
{
   std::string res = "";

	switch(val)
	{
	
	case D3DTADDRESS_WRAP:  
	{
	  res = CSTR_D3DTADDRESS_WRAP;
 	
	} break;
	
	case D3DTADDRESS_MIRROR:  
	{
	  res = CSTR_D3DTADDRESS_MIRROR;
 
	} break;

	case D3DTADDRESS_CLAMP :  
	{
	  res = CSTR_D3DTADDRESS_CLAMP;
 
	} break;

	case D3DTADDRESS_BORDER:  
	{
	 res = CSTR_D3DTADDRESS_BORDER;
 
	} break;

	case D3DTADDRESS_MIRRORONCE:  
	{
	res = CSTR_D3DTADDRESS_MIRRORONCE;
 
	} break;	


	default: {
 
	}

	}// switch

	return res;
}; 

//=============================================================================
GB_D3D9_API bool D3DTEXTUREADDRESS_fromstr( D3DTEXTUREADDRESS& valOut, const std::string& str)
{
  if( str == CSTR_D3DTADDRESS_WRAP )
  {
   valOut = D3DTADDRESS_WRAP;
   return true;
  }

  if( str == CSTR_D3DTADDRESS_MIRROR )
  {
   valOut = D3DTADDRESS_MIRROR;
   return true;
  }

   if( str == CSTR_D3DTADDRESS_CLAMP )
  {
   valOut = D3DTADDRESS_CLAMP;
   return true;
  } 
  
  if( str == CSTR_D3DTADDRESS_BORDER )
  {
   valOut = D3DTADDRESS_BORDER;
   return true;
  }

  if( str == CSTR_D3DTADDRESS_MIRRORONCE )
  {
   valOut = D3DTADDRESS_MIRRORONCE;
   return true;
  }
 
  return false;
};

/*
D3DTEXTUREFILTERTYPE
{
    D3DTEXF_NONE = 0,
    D3DTEXF_POINT = 1,
    D3DTEXF_LINEAR = 2,
    D3DTEXF_ANISOTROPIC = 3,
    D3DTEXF_PYRAMIDALQUAD = 6,
    D3DTEXF_GAUSSIANQUAD = 7,
	
} D3DTEXTUREFILTERTYPE,
*/

static const char CSTR_D3DTEXF_NONE           []   = "D3DTEXF_NONE" ;
static const char CSTR_D3DTEXF_POINT          []   = "D3DTEXF_POINT" ;
static const char CSTR_D3DTEXF_LINEAR         []   = "D3DTEXF_LINEAR" ;
static const char CSTR_D3DTEXF_ANISOTROPIC    []   = "D3DTEXF_ANISOTROPIC" ;
static const char CSTR_D3DTEXF_PYRAMIDALQUAD  []   = "D3DTEXF_PYRAMIDALQUAD" ;
static const char CSTR_D3DTEXF_GAUSSIANQUAD   []   = "D3DTEXF_GAUSSIANQUAD" ;


//=============================================================================
GB_D3D9_API  std::string  D3DTEXTUREFILTERTYPE_tostr(const D3DTEXTUREFILTERTYPE val)
{
  std::string res;

  switch(val)
  {
    case D3DTEXF_NONE:
	{
	res = CSTR_D3DTEXF_NONE;
	return res;
	
	} break;
  
    case D3DTEXF_POINT:
	{
	res = CSTR_D3DTEXF_POINT;
	return res;

	}  break;
  
    case D3DTEXF_LINEAR:
	{
	res = CSTR_D3DTEXF_LINEAR;
	return res;
	
	} break;

    case D3DTEXF_ANISOTROPIC:
	{
	res = CSTR_D3DTEXF_ANISOTROPIC;
	return res;
	
	} break;

    case D3DTEXF_PYRAMIDALQUAD:
	{
	res = CSTR_D3DTEXF_PYRAMIDALQUAD;
	return res;
	
	}	break;
  
    case D3DTEXF_GAUSSIANQUAD:
	{
	res = CSTR_D3DTEXF_GAUSSIANQUAD;
	return res;
	
	} break;
 
   default:
   {
   
   } 
   
  }


    return res;
}; 


//=============================================================================
GB_D3D9_API bool D3DTEXTUREFILTERTYPE_fromstr( D3DTEXTUREFILTERTYPE& valOut, const std::string& str )
{
 
  if(str == CSTR_D3DTEXF_NONE)
  {
    valOut = D3DTEXF_NONE;
    return true;
  }

  
  if(str == CSTR_D3DTEXF_POINT)
  {
    valOut = D3DTEXF_POINT;
    return true;
  }
  

  if(str == CSTR_D3DTEXF_LINEAR)
  {
    valOut = D3DTEXF_LINEAR;
    return true;
  }  
  
 
  if(str == CSTR_D3DTEXF_ANISOTROPIC)
  {
    valOut = D3DTEXF_ANISOTROPIC;
    return true;
  }


  if(str == CSTR_D3DTEXF_PYRAMIDALQUAD)
  {
    valOut = D3DTEXF_PYRAMIDALQUAD;
    return true;
  }  

  if(str == CSTR_D3DTEXF_GAUSSIANQUAD)
  {
    valOut = D3DTEXF_GAUSSIANQUAD;
    return true;
  }  

 

    return false;
};


/*
typedef enum D3DTEXTUREOP
{

    D3DTOP_DISABLE = 1,
    D3DTOP_SELECTARG1 = 2,
    D3DTOP_SELECTARG2 = 3,
    D3DTOP_MODULATE = 4,
    D3DTOP_MODULATE2X = 5,
	
	
    D3DTOP_MODULATE4X = 6,
    D3DTOP_ADD = 7,
    D3DTOP_ADDSIGNED = 8,
    D3DTOP_ADDSIGNED2X = 9,
    D3DTOP_SUBTRACT = 10,
	
	
    D3DTOP_ADDSMOOTH = 11,
    D3DTOP_BLENDDIFFUSEALPHA = 12,
    D3DTOP_BLENDTEXTUREALPHA = 13,
    D3DTOP_BLENDFACTORALPHA = 14,
    D3DTOP_BLENDTEXTUREALPHAPM = 15,
	
	
    D3DTOP_BLENDCURRENTALPHA = 16,
    D3DTOP_PREMODULATE = 17,
    D3DTOP_MODULATEALPHA_ADDCOLOR = 18,
    D3DTOP_MODULATECOLOR_ADDALPHA = 19,
    D3DTOP_MODULATEINVALPHA_ADDCOLOR = 20,
	
    D3DTOP_MODULATEINVCOLOR_ADDALPHA = 21,
    D3DTOP_BUMPENVMAP = 22,
    D3DTOP_BUMPENVMAPLUMINANCE = 23,
    D3DTOP_DOTPRODUCT3 = 24,
    D3DTOP_MULTIPLYADD = 25,
	
    D3DTOP_LERP = 26,
 
} D3DTEXTUREOP 
*/
 
// 1
static const char C_STR_D3DTOP_DISABLE     []  = "D3DTOP_DISABLE" ;
static const char C_STR_D3DTOP_SELECTARG1   []  = "D3DTOP_SELECTARG1" ;
static const char C_STR_D3DTOP_SELECTARG2   []  = "D3DTOP_SELECTARG2" ;
static const char C_STR_D3DTOP_MODULATE     []  = "D3DTOP_MODULATE" ;
static const char C_STR_D3DTOP_MODULATE2X   []  = "D3DTOP_MODULATE2X" ;

 // 2
static const char C_STR_D3DTOP_MODULATE4X   []  = "D3DTOP_MODULATE4X" ;
static const char C_STR_D3DTOP_ADD          []  = "D3DTOP_ADD" ;
static const char C_STR_D3DTOP_ADDSIGNED    []  = "D3DTOP_ADDSIGNED" ;
static const char C_STR_D3DTOP_ADDSIGNED2X  []  = "D3DTOP_ADDSIGNED2X" ;
static const char C_STR_D3DTOP_SUBTRACT     []  = "D3DTOP_SUBTRACT" ;

 // 3
static const char C_STR_D3DTOP_ADDSMOOTH            []  = "D3DTOP_ADDSMOOTH" ;
static const char C_STR_D3DTOP_BLENDDIFFUSEALPHA    []  = "D3DTOP_BLENDDIFFUSEALPHA" ;
static const char C_STR_D3DTOP_BLENDTEXTUREALPHA    []  = "D3DTOP_BLENDTEXTUREALPHA" ;
static const char C_STR_D3DTOP_BLENDFACTORALPHA     []  = "D3DTOP_BLENDFACTORALPHA" ;
static const char C_STR_D3DTOP_BLENDTEXTUREALPHAPM  []  = "D3DTOP_BLENDTEXTUREALPHAPM" ;
 
 // 4
static const char C_STR_D3DTOP_BLENDCURRENTALPHA          []  = "D3DTOP_BLENDCURRENTALPHA" ;
static const char C_STR_D3DTOP_PREMODULATE                []  = "D3DTOP_PREMODULATE" ;
static const char C_STR_D3DTOP_MODULATEALPHA_ADDCOLOR     []  = "D3DTOP_MODULATEALPHA_ADDCOLOR" ;
static const char C_STR_D3DTOP_MODULATECOLOR_ADDALPHA     []  = "D3DTOP_MODULATECOLOR_ADDALPHA" ;
static const char C_STR_D3DTOP_MODULATEINVALPHA_ADDCOLOR  []  = "D3DTOP_MODULATEINVALPHA_ADDCOLOR" ;
 
 // 5
static const char C_STR_D3DTOP_MODULATEINVCOLOR_ADDALPHA  []  = "D3DTOP_MODULATEINVCOLOR_ADDALPHA" ;
static const char C_STR_D3DTOP_BUMPENVMAP                 []  = "D3DTOP_BUMPENVMAP" ;
static const char C_STR_D3DTOP_BUMPENVMAPLUMINANCE        []  = "D3DTOP_BUMPENVMAPLUMINANCE" ;
static const char C_STR_D3DTOP_DOTPRODUCT3                []  = "D3DTOP_DOTPRODUCT3" ;
static const char C_STR_D3DTOP_MULTIPLYADD                []  = "D3DTOP_MULTIPLYADD" ;


static const char C_STR_D3DTOP_LERP  []  = "D3DTOP_LERP" ;


//=================================================================
GB_D3D9_API  std::string  D3DTEXTUREOP_tostr(const D3DTEXTUREOP val)
{
  std::string res = "";
  
  switch(val)
  {
 
    // 1
	//
  
    case D3DTOP_DISABLE:
	{
	res = C_STR_D3DTOP_DISABLE;
	return res;
	} 
	break;
  
   
    case D3DTOP_SELECTARG1:
	{
	res = C_STR_D3DTOP_SELECTARG1;
	return res;
	} 
	break; 
  
  
    case D3DTOP_SELECTARG2:
	{
	res = C_STR_D3DTOP_SELECTARG2;
	return res;
	} 
	break;  
  
   
    case D3DTOP_MODULATE:
	{
	res = C_STR_D3DTOP_MODULATE;
	return res;
	} 
	break;

	  
    case D3DTOP_MODULATE2X:
	{
	res = C_STR_D3DTOP_MODULATE2X;
	return res;
	} 
	break;
	
	
	
 
    // 2
	//
  
    case D3DTOP_MODULATE4X:
	{
	res = C_STR_D3DTOP_MODULATE4X;
	return res;
	} 
	break;
  
   
    case D3DTOP_ADD:
	{
	res = C_STR_D3DTOP_ADD;
	return res;
	} 
	break; 
  
  
    case D3DTOP_ADDSIGNED:
	{
	res = C_STR_D3DTOP_ADDSIGNED;
	return res;
	} 
	break;  
  
   
    case D3DTOP_ADDSIGNED2X:
	{
	res = C_STR_D3DTOP_ADDSIGNED2X;
	return res;
	} 
	break;

	  
    case D3DTOP_SUBTRACT:
	{
	res = C_STR_D3DTOP_SUBTRACT;
	return res;
	} 
	break;
	
	
 
    // 3
	//
  
    case D3DTOP_ADDSMOOTH:
	{
	res = C_STR_D3DTOP_ADDSMOOTH;
	return res;
	} 
	break;
  
   
    case D3DTOP_BLENDDIFFUSEALPHA:
	{
	res = C_STR_D3DTOP_BLENDDIFFUSEALPHA;
	return res;
	} 
	break; 
  
  
    case D3DTOP_BLENDTEXTUREALPHA:
	{
	res = C_STR_D3DTOP_BLENDTEXTUREALPHA;
	return res;
	} 
	break;  
  
   
    case  D3DTOP_BLENDFACTORALPHA:
	{
	res = C_STR_D3DTOP_BLENDFACTORALPHA;
	return res;
	} 
	break;

	  
    case  D3DTOP_BLENDTEXTUREALPHAPM:
	{
	res =  C_STR_D3DTOP_BLENDTEXTUREALPHAPM;
	return res;
	} 
	break;
	
	
	
 
    // 4
	//
  
    case D3DTOP_BLENDCURRENTALPHA:
	{
	res = C_STR_D3DTOP_BLENDCURRENTALPHA;
	return res;
	} 
	break;
  
   
    case D3DTOP_PREMODULATE:
	{
	res = C_STR_D3DTOP_PREMODULATE;
	return res;
	} 
	break; 
  
  
    case D3DTOP_MODULATEALPHA_ADDCOLOR:
	{
	res = C_STR_D3DTOP_MODULATEALPHA_ADDCOLOR;
	return res;
	} 
	break;  
  
   
    case D3DTOP_MODULATECOLOR_ADDALPHA:
	{
	res = C_STR_D3DTOP_MODULATECOLOR_ADDALPHA;
	return res;
	} 
	break;

	  
    case D3DTOP_MODULATEINVALPHA_ADDCOLOR:
	{
	res = C_STR_D3DTOP_MODULATEINVALPHA_ADDCOLOR;
	return res;
	} 
	break;
	
 
 
    // 5
	//
  
    case D3DTOP_MODULATEINVCOLOR_ADDALPHA:
	{
	res = C_STR_D3DTOP_MODULATEINVCOLOR_ADDALPHA;
	return res;
	} 
	break;
  
   
    case D3DTOP_BUMPENVMAP:
	{
	res = C_STR_D3DTOP_BUMPENVMAP;
	return res;
	} 
	break; 
  
  
    case D3DTOP_BUMPENVMAPLUMINANCE:
	{
	res = C_STR_D3DTOP_BUMPENVMAPLUMINANCE;
	return res;
	} 
	break;  
  
   
    case  D3DTOP_DOTPRODUCT3:
	{
	res = C_STR_D3DTOP_DOTPRODUCT3;
	return res;
	} 
	break;

	  
    case D3DTOP_MULTIPLYADD :
	{
	res = C_STR_D3DTOP_MULTIPLYADD;
	return res;
	} 
	break;
	
	
	
 //  last  	
	
    case D3DTOP_LERP :
	{
	res = C_STR_D3DTOP_LERP;
	return res;
	} 
	break;	
	
	
   default :
   {
   
   }
	
  
  }
  // end switch


  return res;
}; 


//==============================================================
GB_D3D9_API bool D3DTEXTUREOP_fromstr( D3DTEXTUREOP& valOut, const std::string& str)
{

 
// 1

  if( str == C_STR_D3DTOP_DISABLE )
  {
   valOut = D3DTOP_DISABLE ;
   return true;
  }

  if( str == C_STR_D3DTOP_SELECTARG1 )
  {
   valOut = D3DTOP_SELECTARG1 ;
   return true;
  }
  
  if( str == C_STR_D3DTOP_SELECTARG2 )
  {
   valOut = D3DTOP_SELECTARG2 ;
   return true;
  }  
  
  if( str == C_STR_D3DTOP_MODULATE )
  {
   valOut = D3DTOP_MODULATE ;
   return true;
  }

  if( str == C_STR_D3DTOP_MODULATE2X )
  {
   valOut = D3DTOP_MODULATE2X ;
   return true;
  }
  
  
 
// 2

  if( str == C_STR_D3DTOP_MODULATE4X )
  {
   valOut = D3DTOP_MODULATE4X ;
   return true;
  }

  if( str == C_STR_D3DTOP_ADD )
  {
   valOut = D3DTOP_ADD ;
   return true;
  }
  
  if( str == C_STR_D3DTOP_ADDSIGNED )
  {
   valOut = D3DTOP_ADDSIGNED ;
   return true;
  }  
  
  if( str == C_STR_D3DTOP_ADDSIGNED2X )
  {
   valOut = D3DTOP_ADDSIGNED2X ;
   return true;
  }

  if( str == C_STR_D3DTOP_SUBTRACT )
  {
   valOut = D3DTOP_SUBTRACT ;
   return true;
  }
  
 
 
 
 
// 3

  if( str == C_STR_D3DTOP_ADDSMOOTH )
  {
   valOut = D3DTOP_ADDSMOOTH ;
   return true;
  }

  if( str == C_STR_D3DTOP_BLENDDIFFUSEALPHA )
  {
   valOut = D3DTOP_BLENDDIFFUSEALPHA ;
   return true;
  }
  
  if( str == C_STR_D3DTOP_BLENDTEXTUREALPHA )
  {
   valOut = D3DTOP_BLENDTEXTUREALPHA ;
   return true;
  }  
  
  if( str == C_STR_D3DTOP_BLENDFACTORALPHA )
  {
   valOut = D3DTOP_BLENDFACTORALPHA ;
   return true;
  }

  if( str == C_STR_D3DTOP_BLENDTEXTUREALPHAPM )
  {
   valOut = D3DTOP_BLENDTEXTUREALPHAPM ;
   return true;
  }
  
 

// 4

  if( str == C_STR_D3DTOP_BLENDCURRENTALPHA )
  {
   valOut = D3DTOP_BLENDCURRENTALPHA ;
   return true;
  }

  if( str == C_STR_D3DTOP_PREMODULATE )
  {
   valOut = D3DTOP_PREMODULATE ;
   return true;
  }
  
  if( str == C_STR_D3DTOP_MODULATEALPHA_ADDCOLOR )
  {
   valOut = D3DTOP_MODULATEALPHA_ADDCOLOR ;
   return true;
  }  
  
  if( str == C_STR_D3DTOP_MODULATECOLOR_ADDALPHA )
  {
   valOut = D3DTOP_MODULATECOLOR_ADDALPHA ;
   return true;
  }

  if( str == C_STR_D3DTOP_MODULATEINVALPHA_ADDCOLOR )
  {
   valOut = D3DTOP_MODULATEINVALPHA_ADDCOLOR ;
   return true;
  }
  
  
 
// 5

  if( str == C_STR_D3DTOP_MODULATEINVCOLOR_ADDALPHA )
  {
   valOut = D3DTOP_MODULATEINVCOLOR_ADDALPHA ;
   return true;
  }

  if( str == C_STR_D3DTOP_BUMPENVMAP )
  {
   valOut = D3DTOP_BUMPENVMAP ;
   return true;
  }
  
  if( str == C_STR_D3DTOP_BUMPENVMAPLUMINANCE )
  {
   valOut = D3DTOP_BUMPENVMAPLUMINANCE ;
   return true;
  }  
  
  if( str == C_STR_D3DTOP_DOTPRODUCT3 )
  {
   valOut = D3DTOP_DOTPRODUCT3 ;
   return true;
  }

  if( str == C_STR_D3DTOP_MULTIPLYADD )
  {
   valOut = D3DTOP_MULTIPLYADD ;
   return true;
  }
  
 // last  

  if( str == C_STR_D3DTOP_LERP )
  {
   valOut = D3DTOP_LERP ;
   return true;
  } 
  
 
  return false;
}; 


/*
typedef enum D3DTEXTURESTAGESTATETYPE
{
    D3DTSS_COLOROP = 1,
    D3DTSS_COLORARG1 = 2,
    D3DTSS_COLORARG2 = 3,
    D3DTSS_ALPHAOP = 4,
    D3DTSS_ALPHAARG1 = 5,
	
    D3DTSS_ALPHAARG2 = 6,
    D3DTSS_BUMPENVMAT00 = 7,
    D3DTSS_BUMPENVMAT01 = 8,
    D3DTSS_BUMPENVMAT10 = 9,
    D3DTSS_BUMPENVMAT11 = 10,
	
    D3DTSS_TEXCOORDINDEX = 11,
    D3DTSS_BUMPENVLSCALE = 22,
    D3DTSS_BUMPENVLOFFSET = 23,
    D3DTSS_TEXTURETRANSFORMFLAGS = 24,
    D3DTSS_COLORARG0 = 26,
	
    D3DTSS_ALPHAARG0 = 27,
    D3DTSS_RESULTARG = 28,
    D3DTSS_CONSTANT = 32,
 
}   
*/
 
// 1
static const char  CSTR_D3DTSS_COLOROP     []   =  "D3DTSS_COLOROP" ;
static const char  CSTR_D3DTSS_COLORARG1   []   =  "D3DTSS_COLORARG1" ;
static const char  CSTR_D3DTSS_COLORARG2   []   =  "D3DTSS_COLORARG2" ;
static const char  CSTR_D3DTSS_ALPHAOP     []   =  "D3DTSS_ALPHAOP" ;
static const char  CSTR_D3DTSS_ALPHAARG1   []   =  "D3DTSS_ALPHAARG1" ;

// 2
static const char  CSTR_D3DTSS_ALPHAARG2      []   =  "D3DTSS_ALPHAARG2" ;
static const char  CSTR_D3DTSS_BUMPENVMAT00   []   =  "D3DTSS_BUMPENVMAT00" ;
static const char  CSTR_D3DTSS_BUMPENVMAT01   []   =  "D3DTSS_BUMPENVMAT01" ;
static const char  CSTR_D3DTSS_BUMPENVMAT10   []   =  "D3DTSS_BUMPENVMAT10" ;
static const char  CSTR_D3DTSS_BUMPENVMAT11   []   =  "D3DTSS_BUMPENVMAT11" ;


// 3

static const char  CSTR_D3DTSS_TEXCOORDINDEX           []   =  "D3DTSS_TEXCOORDINDEX" ;
static const char  CSTR_D3DTSS_BUMPENVLSCALE           []   =  "D3DTSS_BUMPENVLSCALE" ;
static const char  CSTR_D3DTSS_BUMPENVLOFFSET          []   =  "D3DTSS_BUMPENVLOFFSET" ;
static const char  CSTR_D3DTSS_TEXTURETRANSFORMFLAGS   []   =  "D3DTSS_TEXTURETRANSFORMFLAGS" ;
static const char  CSTR_D3DTSS_COLORARG0               []   =  "D3DTSS_COLORARG0" ;

// last

static const char  CSTR_D3DTSS_ALPHAARG0   []   =  "D3DTSS_ALPHAARG0" ;
static const char  CSTR_D3DTSS_RESULTARG   []   =  "D3DTSS_RESULTARG" ;
static const char  CSTR_D3DTSS_CONSTANT    []   =  "D3DTSS_CONSTANT" ;


//========================================================================
GB_D3D9_API  std::string  D3DTEXTURESTAGESTATETYPE_tostr(const D3DTEXTURESTAGESTATETYPE val)
{
  std::string res;

  
  switch(val)
  {
  
  
  
  // 1
  case D3DTSS_COLOROP:
  {
    res = CSTR_D3DTSS_COLOROP;
    return res;
  }
  break;
  
  
  case D3DTSS_COLORARG1:
  {
    res = CSTR_D3DTSS_COLORARG1;
    return res;
  }
  break;
  
  
  case D3DTSS_COLORARG2:
  {
    res = CSTR_D3DTSS_COLORARG2;
    return res;
  }
  break;
  
  
  case D3DTSS_ALPHAOP:
  {
    res = CSTR_D3DTSS_ALPHAOP;
    return res;
  }
  break;
  
  
  case D3DTSS_ALPHAARG1:
  {
    res = CSTR_D3DTSS_ALPHAARG1;
    return res;
  }
  break;
  
 
 
 
 


// 2

  case D3DTSS_ALPHAARG2:
  {
    res = CSTR_D3DTSS_ALPHAARG2;
    return res;
  }
  break;


  case D3DTSS_BUMPENVMAT00:
  {
    res = CSTR_D3DTSS_BUMPENVMAT00;
    return res;
  }
  break;
  
  case D3DTSS_BUMPENVMAT01:
  {
    res = CSTR_D3DTSS_BUMPENVMAT01;
    return res;
  }
  break;
  
  case D3DTSS_BUMPENVMAT10:
  {
    res = CSTR_D3DTSS_BUMPENVMAT10;
    return res;
  }
  break;
  
  case D3DTSS_BUMPENVMAT11:
  {
    res = CSTR_D3DTSS_BUMPENVMAT11;
    return res;
  }
  break;



// 3

  case D3DTSS_TEXCOORDINDEX:
  {
    res = CSTR_D3DTSS_TEXCOORDINDEX;
    return res;
  }
  break;

  case D3DTSS_BUMPENVLSCALE:
  {
    res = CSTR_D3DTSS_BUMPENVLSCALE;
    return res;
  }
  break;
  
  case D3DTSS_BUMPENVLOFFSET:
  {
    res = CSTR_D3DTSS_BUMPENVLOFFSET;
    return res;
  }
  break;  
  
  case D3DTSS_TEXTURETRANSFORMFLAGS:
  {
    res = CSTR_D3DTSS_TEXTURETRANSFORMFLAGS;
    return res;
  }
  break;  

  case D3DTSS_COLORARG0:
  {
    res = CSTR_D3DTSS_COLORARG0;
    return res;
  }
  break;
  
  
  
  

// last

  case D3DTSS_ALPHAARG0:
  {
    res = CSTR_D3DTSS_ALPHAARG0;
    return res;
  }
  break; 
  
  case D3DTSS_RESULTARG:
  {
    res = CSTR_D3DTSS_RESULTARG;
    return res;
  }
  break;   
  
  case D3DTSS_CONSTANT:
  {
    res = CSTR_D3DTSS_CONSTANT;
    return res;
  }
  break;  
  
  
  
	  default: {
	  
	  }
  
  }
  // switch


  return res;
}; 

//========================================================================
GB_D3D9_API bool D3DTEXTURESTAGESTATETYPE_fromstr( D3DTEXTURESTAGESTATETYPE& valOut, 
												const std::string& str)
{
 
// 1
	 if(str == CSTR_D3DTSS_COLOROP)
	 {
	  valOut = D3DTSS_COLOROP;
	  return true;
	 }
 
 	 if(str == CSTR_D3DTSS_COLORARG1)
	 {
	  valOut = D3DTSS_COLORARG1;
	  return true;
	 }
 
 	 if(str == CSTR_D3DTSS_COLORARG2)
	 {
	  valOut = D3DTSS_COLORARG2;
	  return true;
	 }
 
 	 if(str == CSTR_D3DTSS_ALPHAOP)
	 {
	  valOut = D3DTSS_ALPHAOP;
	  return true;
	 }
 
 
 	 if(str == CSTR_D3DTSS_ALPHAARG1)
	 {
	  valOut = D3DTSS_ALPHAARG1;
	  return true;
	 }
 
	 
  
// 2

 if( str == CSTR_D3DTSS_ALPHAARG2 )	 
 {
    valOut = D3DTSS_ALPHAARG2 ;
    return true;
 }
 
  if( str == CSTR_D3DTSS_BUMPENVMAT00 )	 
 {
    valOut = D3DTSS_BUMPENVMAT00 ;
    return true;
 }
 
  if( str == CSTR_D3DTSS_BUMPENVMAT01 )	 
 {
    valOut = D3DTSS_BUMPENVMAT01 ;
    return true;
 }
 
  if( str == CSTR_D3DTSS_BUMPENVMAT10 )	 
 {
    valOut = D3DTSS_BUMPENVMAT10 ;
    return true;
 }
 
 if( str == CSTR_D3DTSS_BUMPENVMAT11 )	 
 {
    valOut = D3DTSS_BUMPENVMAT11 ;
    return true;
 }
	 
 
 // 3

 if( str == CSTR_D3DTSS_TEXCOORDINDEX )	 
 {
    valOut = D3DTSS_TEXCOORDINDEX ;
    return true;
 }
 
 if( str == CSTR_D3DTSS_BUMPENVLSCALE )	 
 {
    valOut = D3DTSS_BUMPENVLSCALE ;
    return true;
 } 
 
 if( str == CSTR_D3DTSS_BUMPENVLOFFSET )	 
 {
    valOut = D3DTSS_BUMPENVLOFFSET ;
    return true;
 }
 
 if( str == CSTR_D3DTSS_TEXTURETRANSFORMFLAGS )	 
 {
    valOut = D3DTSS_TEXTURETRANSFORMFLAGS ;
    return true;
 } 

 if( str == CSTR_D3DTSS_COLORARG0 )	 
 {
    valOut = D3DTSS_COLORARG0 ;
    return true;
 } 


// last
 
 if( str == CSTR_D3DTSS_ALPHAARG0 )	 
 {
    valOut = D3DTSS_ALPHAARG0 ;
    return true;
 }  
 
 if( str == CSTR_D3DTSS_RESULTARG )	 
 {
    valOut = D3DTSS_RESULTARG ;
    return true;
 } 
 
 if( str == CSTR_D3DTSS_CONSTANT )	 
 {
    valOut = D3DTSS_CONSTANT ;
    return true;
 }



 
  return false;
};

/*
 D3DTEXTURETRANSFORMFLAGS
{
    D3DTTFF_DISABLE = 0,
    D3DTTFF_COUNT1 = 1,
    D3DTTFF_COUNT2 = 2,
    D3DTTFF_COUNT3 = 3,
    D3DTTFF_COUNT4 = 4,
    D3DTTFF_PROJECTED = 256,
}
*/

static const char CSTR_D3DTTFF_DISABLE    []  = "D3DTTFF_DISABLE";
static const char CSTR_D3DTTFF_COUNT1     []  = "D3DTTFF_COUNT1";
static const char CSTR_D3DTTFF_COUNT2     []  = "D3DTTFF_COUNT2";
static const char CSTR_D3DTTFF_COUNT3     []  = "D3DTTFF_COUNT3";
static const char CSTR_D3DTTFF_COUNT4     []  = "D3DTTFF_COUNT4";
static const char CSTR_D3DTTFF_PROJECTED  []  = "D3DTTFF_PROJECTED";


//============================================================
GB_D3D9_API  std::string  D3DTEXTURETRANSFORMFLAGS_tostr(const D3DTEXTURETRANSFORMFLAGS val)
{
 std::string res;
 
switch(val)
{

	 case D3DTTFF_DISABLE :
	 {
	  res =  CSTR_D3DTTFF_DISABLE;
	 }
	 break;
	 
	 case D3DTTFF_COUNT1 :
	 {
	   res =  CSTR_D3DTTFF_COUNT1;
	 }
	 break;
	 
	 case D3DTTFF_COUNT2 :
	 {
	   res =  CSTR_D3DTTFF_COUNT2;
	 }
	 break;
	 
	 case D3DTTFF_COUNT3 :
	 {
	   res =  CSTR_D3DTTFF_COUNT3;
	 }
	 break;
	 
	 case D3DTTFF_COUNT4 :
	 {
	   res =  CSTR_D3DTTFF_COUNT4;
	 }
	 break;
	 
	 case D3DTTFF_PROJECTED :
	 {
	   res =  CSTR_D3DTTFF_PROJECTED;
	 }
	 break;	 
	 
	 
	 

   default: {

   }

} 
	 

 return res;
};

//============================================================ 
GB_D3D9_API bool D3DTEXTURETRANSFORMFLAGS_fromstr( D3DTEXTURETRANSFORMFLAGS& valOut, const std::string& str)
{
 
  if( str == CSTR_D3DTTFF_DISABLE )
  {
   valOut = D3DTTFF_DISABLE;
   return true;
  }

  
  if( str == CSTR_D3DTTFF_COUNT1 )
  {
   valOut = D3DTTFF_COUNT1;
   return true;
  } 
  
  
  if( str == CSTR_D3DTTFF_COUNT2 )
  {
   valOut = D3DTTFF_COUNT2;
   return true;
  }


  if( str == CSTR_D3DTTFF_COUNT3 )
  {
   valOut = D3DTTFF_COUNT3;
   return true;
  }

  if( str == CSTR_D3DTTFF_COUNT4 )
  {
   valOut = D3DTTFF_COUNT4;
   return true;
  }  
  
  if( str == CSTR_D3DTTFF_PROJECTED )
  {
   valOut = D3DTTFF_PROJECTED;
   return true;
  }    
  
  
  
  
   return false;
};

 
/*
typedef enum D3DTRANSFORMSTATETYPE
{
    D3DTS_VIEW = 2,
    D3DTS_PROJECTION = 3,
    D3DTS_TEXTURE0 = 16,
    D3DTS_TEXTURE1 = 17,
    D3DTS_TEXTURE2 = 18,
	
    D3DTS_TEXTURE3 = 19,
    D3DTS_TEXTURE4 = 20,
    D3DTS_TEXTURE5 = 21,
    D3DTS_TEXTURE6 = 22,
    D3DTS_TEXTURE7 = 23,
 
} D3DTRANSFORMSTATETYPE, 
*/

static  const char CSTR_D3DTS_VIEW          []   = "D3DTS_VIEW"  ;
static  const char CSTR_D3DTS_PROJECTION    []   = "D3DTS_PROJECTION"  ;
static  const char CSTR_D3DTS_TEXTURE0      []   = "D3DTS_TEXTURE0"  ;
static  const char CSTR_D3DTS_TEXTURE1      []   = "D3DTS_TEXTURE1"  ;
static  const char CSTR_D3DTS_TEXTURE2      []   = "D3DTS_TEXTURE2"  ;

static  const char CSTR_D3DTS_TEXTURE3      []   = "D3DTS_TEXTURE3"  ;
static  const char CSTR_D3DTS_TEXTURE4      []   = "D3DTS_TEXTURE4"  ;
static  const char CSTR_D3DTS_TEXTURE5      []   = "D3DTS_TEXTURE5"  ;
static  const char CSTR_D3DTS_TEXTURE6      []   = "D3DTS_TEXTURE6"  ;
static  const char CSTR_D3DTS_TEXTURE7      []   = "D3DTS_TEXTURE7"  ;


//==============================================================
GB_D3D9_API  std::string  D3DTRANSFORMSTATETYPE_tostr(const D3DTRANSFORMSTATETYPE val)
{
  std::string res;
  
  
  switch(val)
  {
 
 
	  case D3DTS_VIEW: 
	  {
	   res = CSTR_D3DTS_VIEW;
	  }
	  break;
  
	  case D3DTS_PROJECTION: 
	  {
	   res = CSTR_D3DTS_PROJECTION;
	  }
	  break;  
  
	  case D3DTS_TEXTURE0: 
	  {
	   res = CSTR_D3DTS_TEXTURE0;
	  }
	  break;  
  
	  case D3DTS_TEXTURE1: 
	  {
	   res = CSTR_D3DTS_TEXTURE1;
	  }
	  break;  
  
	  case D3DTS_TEXTURE2: 
	  {
	   res = CSTR_D3DTS_TEXTURE2;
	  }
	  break;  
  
  
	  case D3DTS_TEXTURE3: 
	  {
	   res = CSTR_D3DTS_TEXTURE3;
	  }
	  break;    
  
  
 	  case D3DTS_TEXTURE4: 
	  {
	   res = CSTR_D3DTS_TEXTURE4;
	  }
	  break;   
  
	  case D3DTS_TEXTURE5: 
	  {
	   res = CSTR_D3DTS_TEXTURE5;
	  }
	  break;    
  
	  case D3DTS_TEXTURE6: 
	  {
	   res = CSTR_D3DTS_TEXTURE6;
	  }
	  break;    
  
 	  case D3DTS_TEXTURE7: 
	  {
	   res = CSTR_D3DTS_TEXTURE7;
	  }
	  break;   
  
 
        default: 
        {
	
	    }
  }
  
  return res;
}; 

//==============================================================
GB_D3D9_API bool D3DTRANSFORMSTATETYPE_fromstr( D3DTRANSFORMSTATETYPE& valOut, const std::string& str)
{
 
  
  if( str == CSTR_D3DTS_VIEW )
  {
    valOut = D3DTS_VIEW;
    return true;
  }
 
 
  if( str == CSTR_D3DTS_PROJECTION )
  {
    valOut = D3DTS_PROJECTION;
    return true;
  } 
 
 
  if( str == CSTR_D3DTS_TEXTURE0 )
  {
    valOut = D3DTS_TEXTURE0;
    return true;
  }


  if( str == CSTR_D3DTS_TEXTURE1 )
  {
    valOut = D3DTS_TEXTURE1;
    return true;
  }
  
  if( str == CSTR_D3DTS_TEXTURE2 )
  {
    valOut = D3DTS_TEXTURE2;
    return true;
  } 
  
  if( str == CSTR_D3DTS_TEXTURE3 )
  {
    valOut = D3DTS_TEXTURE3;
    return true;
  } 
  
  if( str == CSTR_D3DTS_TEXTURE4 )
  {
    valOut = D3DTS_TEXTURE4;
    return true;
  }  
  
  if( str == CSTR_D3DTS_TEXTURE5 )
  {
    valOut = D3DTS_TEXTURE5;
    return true;
  }  
  
  if( str == CSTR_D3DTS_TEXTURE6 )
  {
    valOut = D3DTS_TEXTURE6;
    return true;
  } 
  
  if( str == CSTR_D3DTS_TEXTURE7 )
  {
    valOut = D3DTS_TEXTURE7;
    return true;
  }   


 
  return false;
};


//=================================================================================
//=================================================================================
//=================================================================================



/*
typedef enum D3DVERTEXBLENDFLAGS
{
    D3DVBF_DISABLE = 0,
    D3DVBF_1WEIGHTS = 1,
    D3DVBF_2WEIGHTS = 2,
    D3DVBF_3WEIGHTS = 3,
    D3DVBF_TWEENING = 255,
    D3DVBF_0WEIGHTS = 256,
	
} D3DVERTEXBLENDFLAGS, 
*/ 

static const char CTSR_D3DVBF_DISABLE  []   =  "D3DVBF_DISABLE" ; 
static const char CTSR_D3DVBF_1WEIGHTS []   =  "D3DVBF_1WEIGHTS" ; 
static const char CTSR_D3DVBF_2WEIGHTS []   =  "D3DVBF_2WEIGHTS" ; 
static const char CTSR_D3DVBF_3WEIGHTS []   =  "D3DVBF_3WEIGHTS" ; 
static const char CTSR_D3DVBF_TWEENING []   =  "D3DVBF_TWEENING" ; 
static const char CTSR_D3DVBF_0WEIGHTS []   =  "D3DVBF_0WEIGHTS" ; 


/**********************************************************************

//=====================================================
  GB_D3D9_API  std::string  D3DVERTEXBLENDFLAGS_tostr(const D3DVERTEXBLENDFLAGS val)
{
	std::string res;

	switch(val)
	{

	case D3DVBF_DISABLE :
		{
			res = CTSR_D3DVBF_DISABLE;
			return res;
		}
		break;


	case D3DVBF_1WEIGHTS :
		{
			res = CTSR_D3DVBF_1WEIGHTS;
			return res;
		}
		break;

	case D3DVBF_2WEIGHTS :
		{
			res = CTSR_D3DVBF_2WEIGHTS;
			return res;
		}
		break;

	case D3DVBF_3WEIGHTS :
		{
			res = CTSR_D3DVBF_3WEIGHTS;
			return res;
		}
		break;

	case D3DVBF_TWEENING :
		{
			res = CTSR_D3DVBF_TWEENING;
			return res;
		}
		break;

	case D3DVBF_0WEIGHTS :
		{
			res = CTSR_D3DVBF_0WEIGHTS;
			return res;
		}
		break;



	default: {
			 
			 }
	
	}
	// switch


   return res;
}; 

 

//=====================================================
GB_D3D9_API bool D3DVERTEXBLENDFLAGS_fromstr( D3DVERTEXBLENDFLAGS& valOut, 
											  const std::string& str)
{
	 
	if( str == CTSR_D3DVBF_DISABLE )
	{
		valOut = D3DVBF_DISABLE;
		return  true;
	}



	if( str == CTSR_D3DVBF_1WEIGHTS )
	{
		valOut = D3DVBF_1WEIGHTS;
		return  true;
	}


	if( str == CTSR_D3DVBF_2WEIGHTS )
	{
		valOut = D3DVBF_2WEIGHTS;
		return  true;
	}


	if( str == CTSR_D3DVBF_3WEIGHTS )
	{
		valOut = D3DVBF_3WEIGHTS;
		return  true;
	}



	if( str == CTSR_D3DVBF_TWEENING )
	{
		valOut = D3DVBF_TWEENING;
		return  true;
	}


	if( str == CTSR_D3DVBF_0WEIGHTS )
	{
		valOut = D3DVBF_0WEIGHTS;
		return  true;
	}


	   return false;
	};


*****************************************************/



//typedef enum D3DZBUFFERTYPE
//{
//    D3DZB_FALSE = 0,
//    D3DZB_TRUE = 1,
//    D3DZB_USEW = 2,
// 
//} D3DZBUFFERTYPE 
//

static const char CSTR_D3DZB_FALSE []   =  "D3DZB_FALSE" ; 
static const char CSTR_D3DZB_TRUE  []   =  "D3DZB_TRUE" ; 
static const char CSTR_D3DZB_USEW  []   =  "D3DZB_USEW" ; 


//===========================================================
GB_D3D9_API  std::string  D3DZBUFFERTYPE_tostr(const D3DZBUFFERTYPE val)
{
  std::string res;

   switch(val)
   {
     case D3DZB_FALSE :
	 {
	   res = CSTR_D3DZB_FALSE;
	 }
	 break;
	 
     case D3DZB_TRUE :
	 {
	   res = CSTR_D3DZB_TRUE;
	 }
	 break;	 
	 
     case D3DZB_USEW :
	 {
	   res = CSTR_D3DZB_USEW;
	 }
	 break;	 
	 
	 
   
      default:
	  {
	 
	  }
   }


   return res;
};
 
//===========================================================
GB_D3D9_API bool D3DZBUFFERTYPE_fromstr( D3DZBUFFERTYPE& valOut, const std::string& str)
{
 
  if( str == CSTR_D3DZB_FALSE )
  {
   valOut = D3DZB_FALSE ;
   return true;
  }

  if( str == CSTR_D3DZB_TRUE )
  {
   valOut = D3DZB_TRUE ;
   return true;
  }  
  
  if( str == CSTR_D3DZB_USEW )
  {
   valOut = D3DZB_USEW ;
   return true;
  }  

 
 return false;
};


//**********************************************************
		 
		 
		 
/*
typedef enum D3DPRIMITIVETYPE
{
    D3DPT_POINTLIST = 1,
    D3DPT_LINELIST = 2,
    D3DPT_LINESTRIP = 3,
    D3DPT_TRIANGLELIST = 4,
    D3DPT_TRIANGLESTRIP = 5,
    D3DPT_TRIANGLEFAN = 6,
	
} D3DPRIMITIVETYPE, *LPD3DPRIMITIVETYPE;
*/

static const char  CSTR_D3DPT_POINTLIST      []  = "D3DPT_POINTLIST" ;
static const char  CSTR_D3DPT_LINELIST       []  = "D3DPT_LINELIST" ;
static const char  CSTR_D3DPT_LINESTRIP      []  = "D3DPT_LINESTRIP" ;
static const char  CSTR_D3DPT_TRIANGLELIST   []  = "D3DPT_TRIANGLELIST" ;
static const char  CSTR_D3DPT_TRIANGLESTRIP  []  = "D3DPT_TRIANGLESTRIP" ;
static const char  CSTR_D3DPT_TRIANGLEFAN    []  = "D3DPT_TRIANGLEFAN" ;



//===================================================================================
GB_D3D9_API  std::string  D3DPRIMITIVETYPE_tostr(const D3DPRIMITIVETYPE val)
{
 std::string res;
 
  switch(val)
  {
	   case D3DPT_POINTLIST:
	   {
	    res = CSTR_D3DPT_POINTLIST;
	    return res;
	   }
	   break;
 
 
	   case D3DPT_LINELIST:
	   {
	    res = CSTR_D3DPT_LINELIST;
	    return res;
	   }
	   break;
 
	   case D3DPT_LINESTRIP:
	   {
	    res = CSTR_D3DPT_LINESTRIP;
	    return res;
	   }
	   break; 
 
 
	   case D3DPT_TRIANGLELIST:
	   {
	    res = CSTR_D3DPT_TRIANGLELIST;
	    return  res;
	   }
	   break;
 
 
 
	   case D3DPT_TRIANGLESTRIP:
	   {
	    res = CSTR_D3DPT_TRIANGLESTRIP;
	    return res;
	   }
	    break;
	 
 
	   case D3DPT_TRIANGLEFAN:
	   {
	    res = CSTR_D3DPT_TRIANGLEFAN;
	    return res;
	   }
	   break;	 
 

	 default: 
	 {
	 
	 }
 
 
  }
  // switch


  return false;
};
 
//=================================================================================== 
GB_D3D9_API bool D3DPRIMITIVETYPE_fromstr( D3DPRIMITIVETYPE& valOut, const std::string& str)
{
 
  if( str == CSTR_D3DPT_POINTLIST )
  {
  valOut = D3DPT_POINTLIST;
  return true;
  }
  
    if( str == CSTR_D3DPT_LINELIST )
  {
  valOut = D3DPT_LINELIST;
  return true;
  }
  
  
  if( str == CSTR_D3DPT_LINESTRIP )
  {
  valOut = D3DPT_LINESTRIP;
  return true;
  }  
  
  if( str == CSTR_D3DPT_TRIANGLELIST )
  {
  valOut = D3DPT_TRIANGLELIST;
  return true;
  }  

  if( str == CSTR_D3DPT_TRIANGLESTRIP )
  {
  valOut = D3DPT_TRIANGLESTRIP;
  return true;
  }

   if( str == CSTR_D3DPT_TRIANGLEFAN )
   {
   valOut = D3DPT_TRIANGLEFAN ;
   return true;
   }
  
  

  return false;
};



/*
typedef enum D3DSAMPLER_TEXTURE_TYPE
{
    D3DSTT_UNKNOWN,
    D3DSTT_1D,
    D3DSTT_2D,
    D3DSTT_CUBE,
    D3DSTT_VOLUME,
 
} D3DSAMPLER_TEXTURE_TYPE, *LPD3DSAMPLER_TEXTURE_TYPE;
*/

static const char  CSTR_D3DSTT_UNKNOWN    []    =  "D3DSTT_UNKNOWN";
//static const char  CSTR_D3DSTT_1D         []    =  "D3DSTT_1D";
static const char  CSTR_D3DSTT_2D         []    =  "D3DSTT_2D";
static const char  CSTR_D3DSTT_CUBE       []    =  "D3DSTT_CUBE";
static const char  CSTR_D3DSTT_VOLUME     []    =  "D3DSTT_VOLUME";


//==============================================================
GB_D3D9_API  std::string D3DSAMPLER_TEXTURE_TYPE_tostr(const D3DSAMPLER_TEXTURE_TYPE val)
{
  std::string res;
  
  
  switch(val)
  {
  
  case D3DSTT_UNKNOWN: 
  {
    res =  CSTR_D3DSTT_UNKNOWN;
	return res;
  }
  break;
  
  
  /*
  case D3DSTT_1D: 
  {
    res =  CSTR_D3DSTT_1D;
	return res;
  }
  break;  
  */
  
   case D3DSTT_2D: 
  {
    res =  CSTR_D3DSTT_2D;
	return res;
  }
  break; 
  
  
  case D3DSTT_CUBE: 
  {
    res =  CSTR_D3DSTT_CUBE;
	return res;
  }
  break;
  
  
  case D3DSTT_VOLUME: 
  {
    res =  CSTR_D3DSTT_VOLUME;
	return res;
  }
  break;
  
 
  
		  default:
		  {
		  
		  }
  
  }


 return res;
}; 

//==============================================================
GB_D3D9_API bool D3DSAMPLER_TEXTURE_TYPE_fromstr( D3DSAMPLER_TEXTURE_TYPE& valOut, const std::string& str)
{
 
   
   if( str == CSTR_D3DSTT_UNKNOWN )
   {
    valOut = D3DSTT_UNKNOWN;
     return true;
   }
   
	/*
   if( str == CSTR_D3DSTT_1D )
   {
    valOut = D3DSTT_1D;
     return true;
   }
   */
     
   if( str == CSTR_D3DSTT_2D )
   {
    valOut = D3DSTT_2D;
     return true;
   }
    
   
   if( str == CSTR_D3DSTT_CUBE )
   {
    valOut = D3DSTT_CUBE;
     return true;
   }
   
   
   if( str == CSTR_D3DSTT_VOLUME )
   {
    valOut = D3DSTT_VOLUME;
     return true;
   }
    
 

   return false;
};





/*
typedef enum D3DSAMPLERSTATETYPE
{
    D3DSAMP_ADDRESSU = 1,
    D3DSAMP_ADDRESSV = 2,
    D3DSAMP_ADDRESSW = 3,
    D3DSAMP_BORDERCOLOR = 4,
    D3DSAMP_MAGFILTER = 5,
	
    D3DSAMP_MINFILTER = 6,
    D3DSAMP_MIPFILTER = 7,
    D3DSAMP_MIPMAPLODBIAS = 8,
    D3DSAMP_MAXMIPLEVEL = 9,
    D3DSAMP_MAXANISOTROPY = 10,
	
    D3DSAMP_SRGBTEXTURE = 11,
    D3DSAMP_ELEMENTINDEX = 12,
    D3DSAMP_DMAPOFFSET = 13,
 
} D3DSAMPLERSTATETYPE, *LPD3DSAMPLERSTATETYPE;
*/


// 1
static const char CSTR_D3DSAMP_ADDRESSU        []    =  "D3DSAMP_ADDRESSU" ;
static const char CSTR_D3DSAMP_ADDRESSV        []    =  "D3DSAMP_ADDRESSV" ;
static const char CSTR_D3DSAMP_ADDRESSW        []    =  "D3DSAMP_ADDRESSW" ;
static const char CSTR_D3DSAMP_BORDERCOLOR     []    =  "D3DSAMP_BORDERCOLOR" ;
static const char CSTR_D3DSAMP_MAGFILTER       []    =  "D3DSAMP_MAGFILTER" ;
// 2
static const char CSTR_D3DSAMP_MINFILTER       []    =  "D3DSAMP_MINFILTER" ;
static const char CSTR_D3DSAMP_MIPFILTER       []    =  "D3DSAMP_MIPFILTER" ;
static const char CSTR_D3DSAMP_MIPMAPLODBIAS   []    =  "D3DSAMP_MIPMAPLODBIAS" ;
static const char CSTR_D3DSAMP_MAXMIPLEVEL     []    =  "D3DSAMP_MAXMIPLEVEL" ;
static const char CSTR_D3DSAMP_MAXANISOTROPY   []    =  "D3DSAMP_MAXANISOTROPY" ;
// 3
static const char CSTR_D3DSAMP_SRGBTEXTURE     []    =  "D3DSAMP_SRGBTEXTURE" ;
static const char CSTR_D3DSAMP_ELEMENTINDEX    []    =  "D3DSAMP_ELEMENTINDEX" ;
static const char CSTR_D3DSAMP_DMAPOFFSET      []    =  "D3DSAMP_DMAPOFFSET" ;







//==================================================================
GB_D3D9_API  std::string  D3DSAMPLERSTATETYPE_tostr(const D3DSAMPLERSTATETYPE val)
{
  std::string res;
  
 
  switch(val)
  {
 
  // 1
    case D3DSAMP_ADDRESSU:
	{
	  res = CSTR_D3DSAMP_ADDRESSU;
	  return res;
	}
	break;

  
    case D3DSAMP_ADDRESSV:
	{
	  res = CSTR_D3DSAMP_ADDRESSV;
	  return res;
	}
	break;  
  
    case D3DSAMP_ADDRESSW:
	{
	  res = CSTR_D3DSAMP_ADDRESSW;
	  return res;
	}
	break;  
  
    case D3DSAMP_BORDERCOLOR:
	{
	  res = CSTR_D3DSAMP_BORDERCOLOR;
	  return res;
	}
	break;  
  
  
    case D3DSAMP_MAGFILTER:
	{
	  res = CSTR_D3DSAMP_MAGFILTER;
	  return res;
	}
	break;


	
  
 // 2
   
     case D3DSAMP_MINFILTER:
	{
	  res = CSTR_D3DSAMP_MINFILTER;
	  return res;
	}
	break;
  
     case D3DSAMP_MIPFILTER:
	{
	  res = CSTR_D3DSAMP_MIPFILTER;
	  return res;
	}
	break;  
  
     case D3DSAMP_MIPMAPLODBIAS:
	{
	  res = CSTR_D3DSAMP_MIPMAPLODBIAS;
	  return res;
	}
	break;  
  
     case D3DSAMP_MAXMIPLEVEL:
	{
	  res = CSTR_D3DSAMP_MAXMIPLEVEL;
	  return res;
	}
	break;  
  
     case D3DSAMP_MAXANISOTROPY:
	{
	  res = CSTR_D3DSAMP_MAXANISOTROPY;
	  return res;
	}
	break;  
  
  
  // 3
  
    case D3DSAMP_SRGBTEXTURE:
	{
	  res = CSTR_D3DSAMP_SRGBTEXTURE;
	  return res;
	}
	break;   
  
  
    case D3DSAMP_ELEMENTINDEX:
	{
	  res = CSTR_D3DSAMP_ELEMENTINDEX;
	  return res;
	}
	break;   
  
    case D3DSAMP_DMAPOFFSET:
	{
	  res = CSTR_D3DSAMP_DMAPOFFSET;
	  return res;
	}
	break;   
  
   
  
  
	  default:
	  {
	  
	  }
	  
  }
  // switch
  
 
  return res;
}; 

//==================================================================
GB_D3D9_API bool D3DSAMPLERSTATETYPE_fromstr( D3DSAMPLERSTATETYPE& valOut, const std::string& str)
{
 
// 1

  if( str == CSTR_D3DSAMP_ADDRESSU )
  {
    valOut = D3DSAMP_ADDRESSU;
    return true;
  }

  
  if( str == CSTR_D3DSAMP_ADDRESSV )
  {
    valOut = D3DSAMP_ADDRESSV;
    return true;
  }
  
  
  if( str == CSTR_D3DSAMP_ADDRESSW )
  {
    valOut = D3DSAMP_ADDRESSW;
    return true;
  }
  
  
  if( str == CSTR_D3DSAMP_BORDERCOLOR )
  {
    valOut = D3DSAMP_BORDERCOLOR;
    return true;
  }
  
  
  if( str == CSTR_D3DSAMP_MAGFILTER )
  {
    valOut = D3DSAMP_MAGFILTER;
    return true;
  }
  
  
 
  // 2
  
  if( str == CSTR_D3DSAMP_MINFILTER )
  {
    valOut = D3DSAMP_MINFILTER;
    return true;
  }
  
  
  
  if( str == CSTR_D3DSAMP_MIPFILTER )
  {
    valOut = D3DSAMP_MIPFILTER;
    return true;
  }
  
  
  if( str == CSTR_D3DSAMP_MIPMAPLODBIAS )
  {
    valOut = D3DSAMP_MIPMAPLODBIAS;
    return true;
  }
  
  if( str == CSTR_D3DSAMP_MAXMIPLEVEL )
  {
    valOut = D3DSAMP_MAXMIPLEVEL;
    return true;
  }
  
 if( str == CSTR_D3DSAMP_MAXANISOTROPY )
  {
    valOut = D3DSAMP_MAXANISOTROPY;
    return true;
  } 
  
  

  // 3
  
  if( str == CSTR_D3DSAMP_SRGBTEXTURE )
  {
    valOut = D3DSAMP_SRGBTEXTURE;
    return true;
  }
  
  if( str == CSTR_D3DSAMP_ELEMENTINDEX )
  {
    valOut = D3DSAMP_ELEMENTINDEX;
    return true;
  }
  
  if( str == CSTR_D3DSAMP_DMAPOFFSET )
  {
    valOut = D3DSAMP_DMAPOFFSET;
    return true;
  }
  
  
 
  return false;
};




 
/*
typedef enum D3DSTATEBLOCKTYPE
{
    D3DSBT_ALL = 1,
    D3DSBT_PIXELSTATE = 2,
    D3DSBT_VERTEXSTATE = 2,
 
} D3DSTATEBLOCKTYPE, *LPD3DSTATEBLOCKTYPE;
*/

//======================================
GB_D3D9_API  std::string  D3DSTATEBLOCKTYPE_tostr(const D3DSTATEBLOCKTYPE val)
{
   std::string res;

      switch(val)
	  {
	  
	  case D3DSBT_ALL :
	  {
	    res = "D3DSBT_ALL";
		return res;
	  }
	  break;
	  
	  
	  case D3DSBT_PIXELSTATE :
	  {
	    res = "D3DSBT_PIXELSTATE";
		return res;
	  }
	  break;	  
	  
	  case D3DSBT_VERTEXSTATE :
	  {
	    res = "D3DSBT_VERTEXSTATE";
		return res;
	  }
	  break;	  
	  
	  
	  default:
	  {
	  
	  }
	  
	  }
	  
	  return res; 
}; 

//======================================
GB_D3D9_API bool D3DSTATEBLOCKTYPE_fromstr( D3DSTATEBLOCKTYPE& valOut, const std::string& str)
{
    if( str == "D3DSBT_ALL" )
	{
	   valOut = D3DSBT_ALL;
	   return true;
	}
	
    if( str == "D3DSBT_PIXELSTATE" )
	{
	   valOut = D3DSBT_PIXELSTATE;
	   return true;
	}	
	
    if( str == "D3DSBT_VERTEXSTATE" )
	{
	   valOut = D3DSBT_VERTEXSTATE;
	   return true;
	}	
 
 
	return false;
};

 
 


/*
 typedef enum D3DSWAPEFFECT
{
    D3DSWAPEFFECT_DISCARD = 1,
    D3DSWAPEFFECT_FLIP = 2,
    D3DSWAPEFFECT_COPY = 3,
 
} D3DSWAPEFFECT, *LPD3DSWAPEFFECT;
*/

//=====================================================
GB_D3D9_API  std::string  D3DSWAPEFFECT_tostr(const D3DSWAPEFFECT val)
{
 std::string res;

  switch(val)
  {
	  
	  case D3DSWAPEFFECT_DISCARD :
	  {
	   res = "D3DSWAPEFFECT_DISCARD";
	   return res;
	  }
	  break;
	  
	  case D3DSWAPEFFECT_FLIP :
	  {
	   res = "D3DSWAPEFFECT_FLIP";
	   return res;	  
	  }
	  break;	  
	  
	  case D3DSWAPEFFECT_COPY :
	  {
	   res = "D3DSWAPEFFECT_COPY";
	   return res;	  
	  }
	  break;	  
	  
 
		default:
		{
				  
		}
			
			
  }
  // switch
	  
	  
	  return res;

}; 

//=====================================================
GB_D3D9_API bool D3DSWAPEFFECT_fromstr( D3DSWAPEFFECT& valOut, const std::string& str)
{
    if( str == "D3DSWAPEFFECT_DISCARD" )
	{
	   valOut = D3DSWAPEFFECT_DISCARD;
	   return true;
	}
	
    if( str == "D3DSWAPEFFECT_FLIP" )
	{
	   valOut = D3DSWAPEFFECT_FLIP;
	   return true;
	}	
		
    if( str == "D3DSWAPEFFECT_COPY" )
	{
	   valOut = D3DSWAPEFFECT_COPY;
	   return true;
	}	
 
 
	return false;
};

/*
typedef enum D3DDECLTYPE
{
 // 1
    D3DDECLTYPE_FLOAT1 = 0,
    D3DDECLTYPE_FLOAT2 = 1,
    D3DDECLTYPE_FLOAT3 = 2,
    D3DDECLTYPE_FLOAT4 = 3,
    D3DDECLTYPE_D3DCOLOR = 4,
	
// 2	
    D3DDECLTYPE_UBYTE4 = 5,
    D3DDECLTYPE_SHORT2 = 6,
    D3DDECLTYPE_SHORT4 = 7,
    D3DDECLTYPE_UBYTE4N = 8,
    D3DDECLTYPE_SHORT2N = 9,
	
// 3	
    D3DDECLTYPE_SHORT4N = 10,
    D3DDECLTYPE_USHORT2N = 11,
    D3DDECLTYPE_USHORT4N = 12,
    D3DDECLTYPE_UDEC3 = 13,
    D3DDECLTYPE_DEC3N = 14,
	
 // 4	
    D3DDECLTYPE_FLOAT16_2 = 15,
    D3DDECLTYPE_FLOAT16_4 = 16,
	D3DDECLTYPE_UNUSED = 17,
	
	
} D3DDECLTYPE, *LPD3DDECLTYPE;
*/
 

static const char CSTR_D3DDECLTYPE_FLOAT1     []   =   "D3DDECLTYPE_FLOAT1";
static const char CSTR_D3DDECLTYPE_FLOAT2     []   =   "D3DDECLTYPE_FLOAT2";
static const char CSTR_D3DDECLTYPE_FLOAT3     []   =   "D3DDECLTYPE_FLOAT3";
static const char CSTR_D3DDECLTYPE_FLOAT4     []   =   "D3DDECLTYPE_FLOAT4";
static const char CSTR_D3DDECLTYPE_D3DCOLOR   []   =   "D3DDECLTYPE_D3DCOLOR";
 
static const char CSTR_D3DDECLTYPE_UBYTE4     []   =   "D3DDECLTYPE_UBYTE4";
static const char CSTR_D3DDECLTYPE_SHORT2     []   =   "D3DDECLTYPE_SHORT2";
static const char CSTR_D3DDECLTYPE_SHORT4     []   =   "D3DDECLTYPE_SHORT4";
static const char CSTR_D3DDECLTYPE_UBYTE4N    []   =   "D3DDECLTYPE_UBYTE4N";
static const char CSTR_D3DDECLTYPE_SHORT2N    []   =   "D3DDECLTYPE_SHORT2N";
 
static const char CSTR_D3DDECLTYPE_SHORT4N    []   =   "D3DDECLTYPE_SHORT4N";
static const char CSTR_D3DDECLTYPE_USHORT2N   []   =   "D3DDECLTYPE_USHORT2N";
static const char CSTR_D3DDECLTYPE_USHORT4N   []   =   "D3DDECLTYPE_USHORT4N";
static const char CSTR_D3DDECLTYPE_UDEC3      []   =   "D3DDECLTYPE_UDEC3";
static const char CSTR_D3DDECLTYPE_DEC3N      []   =   "D3DDECLTYPE_DEC3N";

static const char CSTR_D3DDECLTYPE_FLOAT16_2   []   =   "D3DDECLTYPE_FLOAT16_2";
static const char CSTR_D3DDECLTYPE_FLOAT16_4   []   =   "D3DDECLTYPE_FLOAT16_4";
static const char CSTR_D3DDECLTYPE_UNUSED   []   =   "D3DDECLTYPE_UNUSED";



//====================================================================
GB_D3D9_API  std::string  D3DDECLTYPEtostr(const D3DDECLTYPE val)
{
   std::string res;

 
   // 1
   switch(val)
   {
      case D3DDECLTYPE_FLOAT1:
	  {
	    res = CSTR_D3DDECLTYPE_FLOAT1;
	  }
	  break;
   
   
      case D3DDECLTYPE_FLOAT2:
	  {
	    res = CSTR_D3DDECLTYPE_FLOAT2;
	  }
	  break;   
   
   
       case D3DDECLTYPE_FLOAT3:
	  {
	    res = CSTR_D3DDECLTYPE_FLOAT3;
	  }
	  break;  
   
      case D3DDECLTYPE_FLOAT4:
	  {
	    res = CSTR_D3DDECLTYPE_FLOAT4;
	  }
	  break;   
   
       case D3DDECLTYPE_D3DCOLOR:
	  {
	    res = CSTR_D3DDECLTYPE_D3DCOLOR;
	  }
	  break;  
   
   
   
 
   
   // 2
      case D3DDECLTYPE_UBYTE4:
	  {
	    res = CSTR_D3DDECLTYPE_UBYTE4;
	  }
	  break;   
   
   
       case D3DDECLTYPE_SHORT2:
	  {
	    res = CSTR_D3DDECLTYPE_SHORT2;
	  }
	  break;  
   
       case D3DDECLTYPE_SHORT4:
	  {
	    res = CSTR_D3DDECLTYPE_SHORT4;
	  }
	  break;

      case D3DDECLTYPE_UBYTE4N:
	  {
	    res = CSTR_D3DDECLTYPE_UBYTE4N;
	  }
	  break;


      case D3DDECLTYPE_SHORT2N:
	  {
	    res = CSTR_D3DDECLTYPE_SHORT2N;
	  }
	  break;
	  
   
  
 
  
   
   // 3
      case D3DDECLTYPE_SHORT4N:
	  {
	    res = CSTR_D3DDECLTYPE_SHORT4N;
	  }
	  break;

      case D3DDECLTYPE_USHORT2N:
	  {
	    res = CSTR_D3DDECLTYPE_USHORT2N;
	  }
	  break;


      case D3DDECLTYPE_USHORT4N:
	  {
	    res = CSTR_D3DDECLTYPE_USHORT4N;
	  }
	  break;

      case D3DDECLTYPE_UDEC3:
	  {
	    res = CSTR_D3DDECLTYPE_UDEC3;
	  }
	  break;


      case D3DDECLTYPE_DEC3N:
	  {
	    res = CSTR_D3DDECLTYPE_DEC3N;
	  }
	  break;	  
	  
	  
	  
 
	  
	// 4  
      case D3DDECLTYPE_FLOAT16_2:
	  {
	    res = CSTR_D3DDECLTYPE_FLOAT16_2;
	  }
	  break;	  
	  
      case D3DDECLTYPE_FLOAT16_4:
	  {
	    res = CSTR_D3DDECLTYPE_FLOAT16_4;
	  }
	  break;

      case D3DDECLTYPE_UNUSED:
	  {
	    res = CSTR_D3DDECLTYPE_UNUSED;
	  }
	  break;


	  
	  
   

		 default:
		 {

		 }
   
   }
   // switch
   
   
   return res;
}; 

//====================================================================
GB_D3D9_API bool D3DDECLTYPE_fromstr( D3DDECLTYPE& valOut, const std::string& str)
{
 
 
  // 1
    if( str == CSTR_D3DDECLTYPE_FLOAT1 )
	{
	 valOut = D3DDECLTYPE_FLOAT1;
	 return true;
	}
	
    if( str == CSTR_D3DDECLTYPE_FLOAT2 )
	{
	 valOut = D3DDECLTYPE_FLOAT2;
	 return true;
	}	
	
	
	
    if( str == CSTR_D3DDECLTYPE_FLOAT3 )
	{
	 valOut = D3DDECLTYPE_FLOAT3;
	 return true;
	}	
	
	
    if( str == CSTR_D3DDECLTYPE_FLOAT4 )
	{
	 valOut = D3DDECLTYPE_FLOAT4;
	 return true;
	}	
	
    if( str == CSTR_D3DDECLTYPE_D3DCOLOR )
	{
	 valOut = D3DDECLTYPE_D3DCOLOR;
	 return true;
	}		
	
 
 
 
  // 2
    if( str == CSTR_D3DDECLTYPE_UBYTE4 )
	{
	 valOut = D3DDECLTYPE_UBYTE4;
	 return true;
	}
	
    if( str == CSTR_D3DDECLTYPE_SHORT2 )
	{
	 valOut = D3DDECLTYPE_SHORT2;
	 return true;
	}	
	
	
	
    if( str == CSTR_D3DDECLTYPE_SHORT4 )
	{
	 valOut = D3DDECLTYPE_SHORT4;
	 return true;
	}	
	
	
    if( str == CSTR_D3DDECLTYPE_UBYTE4N )
	{
	 valOut = D3DDECLTYPE_UBYTE4N;
	 return true;
	}	
	
    if( str == CSTR_D3DDECLTYPE_SHORT2N )
	{
	 valOut = D3DDECLTYPE_SHORT2N;
	 return true;
	}		
	
	
	

 
  // 3
    if( str == CSTR_D3DDECLTYPE_SHORT4N )
	{
	 valOut = D3DDECLTYPE_SHORT4N;
	 return true;
	}
	
    if( str == CSTR_D3DDECLTYPE_USHORT2N )
	{
	 valOut = D3DDECLTYPE_USHORT2N;
	 return true;
	}	
	
	
	
    if( str == CSTR_D3DDECLTYPE_USHORT4N )
	{
	 valOut = D3DDECLTYPE_USHORT4N;
	 return true;
	}	
	
	
    if( str == CSTR_D3DDECLTYPE_UDEC3 )
	{
	 valOut = D3DDECLTYPE_UDEC3;
	 return true;
	}	
	
    if( str == CSTR_D3DDECLTYPE_DEC3N )
	{
	 valOut = D3DDECLTYPE_DEC3N;
	 return true;
	}		
	
	
	
 // 4
    if( str == CSTR_D3DDECLTYPE_FLOAT16_2 )
	{
	 valOut = D3DDECLTYPE_FLOAT16_2;
	 return true;
	}	
	
    if( str == CSTR_D3DDECLTYPE_FLOAT16_4 )
	{
	 valOut = D3DDECLTYPE_FLOAT16_4;
	 return true;
	}
	
    if( str == CSTR_D3DDECLTYPE_UNUSED )
	{
	 valOut = D3DDECLTYPE_UNUSED;
	 return true;
	}		
	
	
 

 return false;
};

/*
typedef enum D3DDECLMETHOD
{
    D3DDECLMETHOD_DEFAULT = 0,
    D3DDECLMETHOD_PARTIALU = 1,
    D3DDECLMETHOD_PARTIALV = 2,
    D3DDECLMETHOD_CROSSUV = 3,
    D3DDECLMETHOD_UV = 4,
    D3DDECLMETHOD_LOOKUP = 5,
    D3DDECLMETHOD_LOOKUPPRESAMPLED = 6,
	
} D3DDECLMETHOD, *LPD3DDECLMETHOD;
*/

//============================================================
GB_D3D9_API  std::string  D3DDECLMETHOD_tostr(const D3DDECLMETHOD val)
{
  std::string res;
 
  switch(val)
  {
 
     case D3DDECLMETHOD_DEFAULT :
	 {
	   res = "D3DDECLMETHOD_DEFAULT"; 
	 }
	 break;
  
  
     case D3DDECLMETHOD_PARTIALU :
	 {
	   res = "D3DDECLMETHOD_PARTIALU"; 
	 }
	 break;  
  
  
      case D3DDECLMETHOD_PARTIALV :
	 {
	   res = D3DDECLMETHOD_PARTIALV; 
	 }
	 break; 
  
      case D3DDECLMETHOD_CROSSUV :
	 {
	   res = "D3DDECLMETHOD_CROSSUV"; 
	 }
	 break; 
	 
 
	 case D3DDECLMETHOD_UV :
	 {
	   res = "D3DDECLMETHOD_UV"; 
	 }
	 break; 
  
  
     case D3DDECLMETHOD_LOOKUP :
	 {
	   res = "D3DDECLMETHOD_LOOKUP"; 
	 }
	 break;  
  
  
     case D3DDECLMETHOD_LOOKUPPRESAMPLED :
	 {
	   res = "D3DDECLMETHOD_LOOKUPPRESAMPLED"; 
	 }
	 break; 
  
  
  
		    default:
			{
			
			}
  
  }
  
 
  return res;
}; 

//============================================================
GB_D3D9_API bool D3DDECLMETHOD_fromstr( D3DDECLMETHOD& valOut, const std::string& str)
{
 
   if(  str ==  "D3DDECLMETHOD_DEFAULT" )
   {
    valOut = D3DDECLMETHOD_DEFAULT;
	return true;
   }

   if(  str ==  "D3DDECLMETHOD_PARTIALU" )
   {
    valOut = D3DDECLMETHOD_PARTIALU;
	return true;
   }  
   
   if(  str ==  "D3DDECLMETHOD_PARTIALV" )
   {
    valOut = D3DDECLMETHOD_PARTIALV;
	return true;
   }  
   
   if(  str ==  "D3DDECLMETHOD_CROSSUV" )
   {
    valOut = D3DDECLMETHOD_CROSSUV;
	return true;
   }  
   
   
   if(  str ==  "D3DDECLMETHOD_UV" )
   {
    valOut = D3DDECLMETHOD_UV;
	return true;
   }  
   
   if(  str ==  "D3DDECLMETHOD_LOOKUP" )
   {
    valOut = D3DDECLMETHOD_LOOKUP;
	return true;
   }     
   
   if(  str ==  "D3DDECLMETHOD_LOOKUPPRESAMPLED" )
   {
    valOut = D3DDECLMETHOD_LOOKUPPRESAMPLED;
	return true;
   }  
   
 return false;
};


//=========================================================

}
}
}
}



#endif // #if ( defined(GB_D3D9) && defined(WIN32) )
// end file