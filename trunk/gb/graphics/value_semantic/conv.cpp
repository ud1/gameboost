 
#include <gb/graphics/value_semantic/conv.h>

namespace gb
{
namespace graphics
{
namespace value_semantic
{ 

//=================================================================
 

static const char* CSTR_VIEWPROJECTION = "VIEWPROJECTION";
static const char* CSTR_VIEWPROJECTIONINVERSE = "VIEWPROJECTIONINVERSE";
static const char* CSTR_VIEWPROJECTIONINVERSETRANSPONE = "VIEWPROJECTIONINVERSETRANSPONE";
static const char* CSTR_VIEWPROJECTIONTRANSPONE = "VIEWPROJECTIONTRANSPONE";
static const char* CSTR_VIEW = "VIEW";
static const char* CSTR_VIEWTRANSPONE = "VIEWTRANSPONE";
static const char* CSTR_VIEWINVERSE = "VIEWINVERSE";
static const char* CSTR_VIEWINVERSETRANSPONE = "VIEWINVERSETRANSPONE";
static const char* CSTR_PROJECTION = "PROJECTION";
static const char* CSTR_PROJECTIONINVERSE = "PROJECTIONINVERSE";
static const char* CSTR_PROJECTIONTRANSPONE = "PROJECTIONTRANSPONE";
static const char* CSTR_PROJECTIONINVERSETRANSPONE = "PROJECTIONINVERSETRANSPONE";
static const char* CSTR_WORLDVIEWPROJECTION = "WORLDVIEWPROJECTION";
static const char* CSTR_WORLDVIEWPROJECTIONTRANSPONE = "WORLDVIEWPROJECTIONTRANSPONE";
static const char* CSTR_WORLDVIEWPROJECTIONINVERSE = "WORLDVIEWPROJECTIONINVERSE";
static const char* CSTR_WORLDVIEWPROJECTIONINVERSETRANSPONE = "WORLDVIEWPROJECTIONINVERSETRANSPONE";
static const char* CSTR_WORLD = "WORLD";
static const char* CSTR_WORLDTRANSPONE = "WORLDTRANSPONE";
static const char* CSTR_WORLDINVERSE = "WORLDINVERSE";
static const char* CSTR_WORLDINVERSETRANSPONE = "WORLDINVERSETRANSPONE";
static const char* CSTR_WORLDVIEW = "WORLDVIEW";
static const char* CSTR_WORLDVIEWTRANSPONE = "WORLDVIEWTRANSPONE";
static const char* CSTR_WORLDVIEWINVERSE = "WORLDVIEWINVERSE";
static const char* CSTR_WORLDVIEWINVERSETRANSPONE = "WORLDVIEWINVERSETRANSPONE";

 

//=================================================================
std::string  matrix4x4_type_e_tostr(const matrix4x4_type_e::e val)
{
	std::string res;
 

 switch(val)
 {

 case matrix4x4_type_e::VIEWPROJECTION:
	 {
		 res =  CSTR_VIEWPROJECTION;
	 }
	 break;

 case matrix4x4_type_e::VIEWPROJECTIONINVERSE:
	 {
		 res = CSTR_VIEWPROJECTIONINVERSE;
	 }
	 break;

 case matrix4x4_type_e::VIEWPROJECTIONINVERSETRANSPONE:
	 {
		 res = CSTR_VIEWPROJECTIONINVERSETRANSPONE;
	 }
	 break;

 case matrix4x4_type_e::VIEWPROJECTIONTRANSPONE:
	 {
		 res = CSTR_VIEWPROJECTIONTRANSPONE;
	 }
	 break;

 case matrix4x4_type_e::VIEW:
	 {
		 res = CSTR_VIEW;
	 }
	 break;

 case matrix4x4_type_e::VIEWTRANSPONE:
	 {
		 res = CSTR_VIEWTRANSPONE;
	 }
	 break;

 case matrix4x4_type_e::VIEWINVERSE:
	 {
		 res = CSTR_VIEWINVERSE;
	 }
	 break;

 case matrix4x4_type_e::VIEWINVERSETRANSPONE:
	 {
		 res = CSTR_VIEWINVERSETRANSPONE;
	 }
	 break;

 case matrix4x4_type_e::PROJECTION:
	 {
		 res = CSTR_PROJECTION;
	 }
	 break;

 case matrix4x4_type_e::PROJECTIONINVERSE:
	 {
		 res = CSTR_PROJECTIONINVERSE;
	 }
	 break;

 case matrix4x4_type_e::PROJECTIONTRANSPONE:
	 {
		 res = CSTR_PROJECTIONTRANSPONE;
	 }
	 break;

 case matrix4x4_type_e::PROJECTIONINVERSETRANSPONE:
	 {
		 res = CSTR_PROJECTIONINVERSETRANSPONE;
	 }
	 break;
 

 case matrix4x4_type_e::WORLDVIEWPROJECTION:
	 {
		 res = CSTR_WORLDVIEWPROJECTION;
	 }
	 break;

 case matrix4x4_type_e::WORLDVIEWPROJECTIONTRANSPONE:
	 {
		 res = CSTR_WORLDVIEWPROJECTIONTRANSPONE;
	 }
	 break;

 case matrix4x4_type_e::WORLDVIEWPROJECTIONINVERSE:
	 {
		 res = CSTR_WORLDVIEWPROJECTIONINVERSE;
	 }
	 break;

 case matrix4x4_type_e::WORLDVIEWPROJECTIONINVERSETRANSPONE:
	 {
		 res = CSTR_WORLDVIEWPROJECTIONINVERSETRANSPONE;
	 }
	 break;


    

 case matrix4x4_type_e::WORLD:
	 {
		 res = CSTR_WORLD;
	 }
	 break;


 case matrix4x4_type_e::WORLDTRANSPONE:
	 {
		 res = CSTR_WORLDTRANSPONE;
	 }
	 break;

 case matrix4x4_type_e::WORLDINVERSE:
	 {
		 res = CSTR_WORLDINVERSE;
	 }
	 break;

 case matrix4x4_type_e::WORLDINVERSETRANSPONE:
	 {
		 res = CSTR_WORLDINVERSETRANSPONE;
	 }
	 break;

 case matrix4x4_type_e::WORLDVIEW:
	 {
		 res = CSTR_WORLDVIEW;
	 }
	 break;

 case matrix4x4_type_e::WORLDVIEWTRANSPONE:
	 {
		 res = CSTR_WORLDVIEWTRANSPONE;
	 }
	 break;

 case matrix4x4_type_e::WORLDVIEWINVERSE:
	 {
		 res = CSTR_WORLDVIEWINVERSE;
	 }
	 break;

 case matrix4x4_type_e::WORLDVIEWINVERSETRANSPONE:
	 {
		 res = CSTR_WORLDVIEWINVERSETRANSPONE;
	 }
	 break;

	/*
 case XXXXXXXXXXXXXXXXX:
	 {
		 res = CSTR_XXXXXXXXXXXXX;
	 }
	 break;

 case XXXXXXXXXXXXXXXXX:
	 {
		 res = CSTR_XXXXXXXXXXXXX;
	 }
	 break;
	 */

 

 default:
	 {
	 
	 }
 
 }

  return res;
}

//=================================================================
bool  matrix4x4_type_e_fromstr( matrix4x4_type_e::e& valOut, 
										const std::string& str)
{
 

	if( (str == CSTR_VIEWPROJECTION)||(str=="VIEWPROJ")||(str=="VP") )
	{
		valOut = matrix4x4_type_e::VIEWPROJECTION;
		return true;
	}

	if( (str==CSTR_VIEWPROJECTIONINVERSE)||(str=="VIEWPROJINV")||(str=="VPI") )
	{
		valOut = matrix4x4_type_e::VIEWPROJECTIONINVERSE;
		return true;
	}

	if( (str == CSTR_VIEWPROJECTIONINVERSETRANSPONE) ||
		(str=="CSTR_VIEWPROJINVTRANSP") || (str=="VPIT")  )
	{
		valOut = matrix4x4_type_e::VIEWPROJECTIONINVERSETRANSPONE;
		return true;
	}





	// VIEWPROJECTIONTRANSPONE

	if( (str == CSTR_VIEWPROJECTIONTRANSPONE) || (str=="VIEWPROJTRANSP") 
		|| (str=="VPT") )
	{
		valOut = matrix4x4_type_e::VIEWPROJECTIONTRANSPONE;
		return true;
	}


	if( str == CSTR_VIEW )
	{
		valOut = matrix4x4_type_e::VIEW;
		return true;
	}

	if( (str == CSTR_VIEWTRANSPONE) || (str=="VIEWTRANSP") || (str=="VT") )
	{
		valOut = matrix4x4_type_e::VIEWTRANSPONE;
		return true;
	}

	//	VIEWINVERSE

	if( (str == CSTR_VIEWINVERSE) || (str=="VIEWINV") || (str=="VI") )
	{
		valOut = matrix4x4_type_e::VIEWINVERSE;
		return true;
	}


 



	// VIEWINVERSETRANSPONE

	if( (str == CSTR_VIEWINVERSETRANSPONE) || ( str == "VIEWINVTRANSP" )
		 || (str=="VIT"))
	{
		valOut = matrix4x4_type_e::VIEWINVERSETRANSPONE;
		return true;
	}
 
 
	if( (str == CSTR_PROJECTION) || ( str == "PROJ" ) )
	{
		valOut = matrix4x4_type_e::PROJECTION;
		return true;
	}
 



	if((str==CSTR_PROJECTIONINVERSE)||(str=="PROJINV")||(str=="PI") )
	{
		valOut = matrix4x4_type_e::PROJECTIONINVERSE;
		return true;
	}
 



	if( (str==CSTR_PROJECTIONTRANSPONE)||(str=="PROJTRANSP")||(str=="PT") )
	{
		valOut = matrix4x4_type_e::PROJECTIONTRANSPONE;
		return true;
	}


	if( (str==CSTR_PROJECTIONINVERSETRANSPONE) || (str=="CSTR_PROJINVTRANSP")
		|| (str=="PIT") )
	{
		valOut = matrix4x4_type_e::PROJECTIONINVERSETRANSPONE;
		return true;
	}

	if( (str == CSTR_WORLDVIEWPROJECTION)||(str=="WORLDVIEWPROJ")||(str=="WVP") )
	{
		valOut = matrix4x4_type_e::WORLDVIEWPROJECTION;
		return true;
	}
 

	if( (str==CSTR_WORLDVIEWPROJECTIONTRANSPONE)||(str=="WORLDVIEWPROJTRANSP")
		|| (str=="WVPT") )
	{
		valOut = matrix4x4_type_e::WORLDVIEWPROJECTIONTRANSPONE;
		return true;
	}
 



	if( (str==CSTR_WORLDVIEWPROJECTIONINVERSE) || (str=="WORLDVIEWPROJINV")
		 || (str=="WVPI") )
	{
		valOut = matrix4x4_type_e::WORLDVIEWPROJECTIONINVERSE;
		return true;
	}
 
 
   // WORLDVIEWPROJECTIONINVERSETRANSPONE

	if( (str == CSTR_WORLDVIEWPROJECTIONINVERSETRANSPONE)
		|| (str == "WORLDVIEWPROJINVTRANSP" )
		|| (str=="WVPIT") )
	{
		valOut = matrix4x4_type_e::WORLDVIEWPROJECTIONINVERSETRANSPONE;
		return true;
	}
 




	if( str == CSTR_WORLD )
	{
		valOut = matrix4x4_type_e::WORLD;
		return true;
	}




	if( (str == CSTR_WORLDTRANSPONE) || (str == "WORLDTRANSP")||(str=="WT") )
	{
		valOut = matrix4x4_type_e::WORLDTRANSPONE;
		return true;
	}

 



	if( (str==CSTR_WORLDINVERSE)||(str=="WORLDINV")||(str=="WI") )
	{
		valOut = matrix4x4_type_e::WORLDINVERSE;
		return true;
	}
 


   // WORLDINVERSETRANSPONE


	if( (str==CSTR_WORLDINVERSETRANSPONE)||(str=="WORLDINVTRANSP")||(str=="WIT") )
	{
		valOut = matrix4x4_type_e::WORLDINVERSETRANSPONE;
		return true;
	}
 

 

	if( (str==CSTR_WORLDVIEW)||(str=="WV") )
	{
		valOut = matrix4x4_type_e::WORLDVIEW;
		return true;
	}
 

	if( (str==CSTR_WORLDVIEWTRANSPONE)||(str == "WORLDVIEWTRANSP")||(str=="WVT") )
	{
		valOut = matrix4x4_type_e::WORLDVIEWTRANSPONE;
		return true;
	}
 


	if( (str==CSTR_WORLDVIEWINVERSE)||(str=="WORLDVIEWINV")||(str=="WVI") )
	{
		valOut = matrix4x4_type_e::WORLDVIEWINVERSE;
		return true;
	}
 

   //  WORLDVIEWINVERSETRANSPONE

 	if( str == CSTR_WORLDVIEWINVERSETRANSPONE )
	{
		valOut = matrix4x4_type_e::WORLDVIEWINVERSETRANSPONE;
		return true;
	}

 	if( str == "WORLDVIEWINVTRANSP" )
	{
		valOut = matrix4x4_type_e::WORLDVIEWINVERSETRANSPONE;
		return true;
	}

	if(str=="WVIT")
	{
		valOut = matrix4x4_type_e::WORLDVIEWINVERSETRANSPONE;
		return true;	
	}


 
   return false;
}






//=================================================================

}
}
}


// end file