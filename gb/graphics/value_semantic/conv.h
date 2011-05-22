/** \file
 \brief  Конвертаци типот из строчки в строчку .

 \author ksacvet777
*/

#pragma once
#include <gb/xxxxxxxx/enums.h>

#include <string>

namespace gb
{
namespace graphics
{
namespace value_semantic
{  
  
//---------------------------------------------------------------  

std::string float_type_e _tostr(const float_type_e::e val)
{
std::string res;

 switch(val)
 {
 
 






		FPS,

		TIMEELAPSED,


		VIEWPORTWIDTH,
		VIEWPORTHEIGHT,
		VIEWPORTWIDTHINVERSE,
		VIEWPORTHEIGHTINVERSE,

		FOV,

		FARCLIPPLANE,


		NEARCLIPPLANE,


		RANDOMFRACTION1PERPASS,
		RANDOMFRACTION2PERPASS,
		RANDOMFRACTION3PERPASS,
		RANDOMFRACTION4PERPASS,

		RANDOMFRACTION1PEREFFECT,
		RANDOMFRACTION2PEREFFECT,
		RANDOMFRACTION3PEREFFECT,
		RANDOMFRACTION4PEREFFECT,

		PASSINDEX,
		RIGTHMOUSEBUTTON,
		MIDDLEMOUSEBUTTON,
		LEFTMOUSEBUTTON,
		MOUSECOORDINATEX,
		MOUSECOORDINATEY,
		MOUSECOORDINATEXNDC,
		MOUSECOORDINATEYNDC,
		MODELBOUNDINGSPHERERADIUS,

		ASPECT,

		SPECULARPOWER,

		ROTATEZ,

		BRIGHTNESS,

		CONTRAST,

		ALPHA,
		LIGTHMAPINTENSITY,
		ANIMATESPEED,


 
 
 case TIME0:
 {
 res = "TIME0";
 
 } break;
 
 case TIME:
 {
 res = "TIME";
 
 } break; 
 
 case TIME0_X:
 {
 res = "TIME0_X";
 
 } break;
  
 case COSTIME0_X:
 {
 res = "COSTIME0_X";
 
 } break;
 
 case SINTIME0_X:
 {
 res = "SINTIME0_X";
 
 } break;
 

 
 case TANTIME0_X:
 {
 res = "TANTIME0_X";
 
 } break;
 
 case TIME0_1:
 {
 res = "TIME0_1";
 
 } break; 
 
 case COSTIME0_1:
 {
 res = "COSTIME0_1";
 
 } break;
 
 case SINTIME0_1:
 {
 res = "SINTIME0_1";
 
 } break;
 
 case TANTIME0_1:
 {
 res = "TANTIME0_1";
 
 } break;
  
 
 xcxxczcxcxczxcxczxczx
 
 case TIMESPEED:
 {
 res = "TIMESPEED";
 
 } break; 
 
 case TAN0_2PI:
 {
 res = "TAN0_2PI";
 
 } break;  
 
  case COSTIME0_2PI:
 {
 res = "COSTIME0_2PI";
 
 } break; 
 
  case SINTIME0_PI:
 {
 res = "SINTIME0_PI";
 
 } break; 
 
  case TANTIME0_2PI:
 {
 res = "TANTIME0_2PI";
 
 } break; 
 
  case TIMECYCLEPERIOD:
 {
 res = "TIMECYCLEPERIOD";
 
 } break; 
 
  case xxxxx:
 {
 res = "xxxxxxx";
 
 } break; 
 
  case xxxxx:
 {
 res = "xxxxxxx";
 
 } break; 
 
  case xxxxx:
 {
 res = "xxxxxxx";
 
 } break; 
 
  case xxxxx:
 {
 res = "xxxxxxx";
 
 } break; 
 
  case xxxxx:
 {
 res = "xxxxxxx";
 
 } break; 
 
  case xxxxx:
 {
 res = "xxxxxxx";
 
 } break; 
 
 
 
 
 
	 default:
	 {
	 
	 }
	 
 }

 return res;
}




//--------------------------------------------------------------- 

}
}
}

// end file