/** \file
 \brief Семантики(смысл) параметров отрисовки. Аналогично семантикам праметров RenderMonkey
 
 
 
  \author  ksacvet777

*/


#pragma once

namespace gb
{
 namespace graphics
 {

  //! \brief Семантики(смысл) параметров отрисовки. Аналогично семантикам праметров RenderMonkey
  namespace value_semantic
  {  
  
//---------------------------------------------------------------  
  
  
struct float_type_e
{
	enum e
	{
		UNDEFINED  =  0,

		TIME0,
		TIME,
		TIME0_X,

		COSTIME0_X,
		SINTIME0_X,
		TANTIME0_X,
		TIME0_1,
		COSTIME0_1,
		SINTIME0_1,
		TANTIME0_1,

		TIMESPEED,

		TAN0_2PI,
		COSTIME0_2PI,
		SINTIME0_PI,
		TANTIME0_2PI,
		TIMECYCLEPERIOD,

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


		

		UNUSED_DECLARED_LAST
	};
}; 



struct float2_type_e
{
	enum e
	{
		 UNDEFINED  =  0,

		 VIEWPORTDIMENSIONS,
		 VIEWPORTDIMENSIONSINVERSE,
		 MOUSECOORDINATEXY,
		 MOUSECOORDINATEXYNDC,

		 TEXCOORDOFFSET,
		 TEXCOORDSCALE,

		 SCREENCOORD,
		 SCREENRELATIVECOORD,

		 
		 
		 UNUSED_DECLARED_LAST

	};
}; 


  
struct float3_type_e
{
	enum e
	{

		UNDEFINED = 0,

		POSITION,
		LIGHTPOSITION,
		VIEWDIRECTION,
		VIEWPOSITION,
		VIEWSIDEUP,
		VIEWUPVECTOR,
		MOUSECOORDCAMERAUNPROJECT,
		DIRECTION,

		UNUSED_DECLARED_LAST

	}; 
}; 


struct float4_type_e
{
	enum e
	{
		UNDEFINED  = 0 ,

		TIME0_X_PACKED,
		TIME0_1_PACKED,
		TIME0_2PI_PACKED,
		MOUSEBUTTONSPACKED,
		MOUSECOORDPACKED,

		VIEWDIRECTION,


		VIEWPOSITION,


		VIEWSIDEUP,
		VIEWSIDE,

		VIEWUPVECTOR,


		UNUSED_DECLARED_LAST
	};
};


struct float4_color_type_e
{
	enum e
	{
		 UNDEFINED = 0,
		  
		 AMBIENT,
		 DIFFUSE,
		 SPECULAR,
		 LIGHTSOURCE,

		 LIGHTMAP,

		 UNUSE_DECLARED_LAST
	};
};
  
struct matrix3x3_type_e
{

};  
  
  
struct matrix4x4_type_e
{
	enum e
	{ 	
		  UNDEFINED  = 0,

          VIEWPROJECTION,
          VIEWPROJECTIONINVERSE,
          VIEWPROJECTIONINVERSETRANSPONE,
          VIEWPROJECTIONTRANSPONE,
          VIEW,
          VIEWTRANSPONE,
          VIEWINVERSE,
          VIEWINVERSETRANSPONE,
          PROJECTION,
          PROJECTIONINVERSE,
          PROJECTIONTRANSPONE,
          PROJECTIONINVERSETRANSPONE,
          WORLDVIEWPROJECTION,
          WORLDVIEWPROJECTIONTRANSPONE,
          WORLDVIEWPROJECTIONINVERSE,
          WORLDVIEWPROJECTIONINVERSETRANSPONE,
          WORLD,
          WORLDTRANSPONE,
          WORLDINVERSE,
          WORLDINVERSETRANSPONE,
          WORLDVIEW,
          WORLDVIEWTRANSPONE,
          WORLDVIEWINVERSE,
          WORLDVIEWINVERSETRANSPONE,
 

 
         UNUSED_DECLARED_LAST
	};
};
  
  
  
  
  
  
  
  
  
//---------------------------------------------------------------   
  
  }
 }
}

// end file