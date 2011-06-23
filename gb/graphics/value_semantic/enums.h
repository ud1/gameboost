/** \file
 \brief  Перечисления для семантик.
 
 
  \author  ksacvet777

*/


#pragma once

namespace gb
{
 namespace graphics
 {

  namespace value_semantic
  {  
  
//---------------------------------------------------------------  
  
//! \brief Тип,   размерность параметра
struct type_e 
{
	  enum e
	  {
		  UNDEFINED  = 0 ,   ///<  не определён

		  FLOAT,	///< float
		  FLOAT2,	///< 2d vector
		  FLOAT3,	///< 3d vector
		  FLOAT4,	///< 4d vector/color
		  FLOAT3x3,	///<  matrix 3x3
		  FLOAT4x4, ///<  matrix 4x4
		  
		  UNUSED_DECL_LAST,
		  UNUSED_FROCE32  =  0x7f000000
	  };
};
  
//!  семантика параметра типа  float
  #pragma message("ks777 Перенос почти всего в fmath "  __FILE__ )
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


		

		UNUSED_DECLARED_LAST,
		
		
		UNUSED_FORCE32 = 0x7f000000		
	};
}; 


//!  семантика параметра 2d-вектора 
struct float2_type_e
{
	enum e
	{
		// UNDEFINED  =  0,

		 VIEWPORTDIMENSIONS = float_type_e::UNUSED_DECLARED_LAST ,
		 VIEWPORTDIMENSIONSINVERSE,
		 MOUSECOORDINATEXY,
		 MOUSECOORDINATEXYNDC,

		 TEXCOORDOFFSET,
		 TEXCOORDSCALE,

		 SCREENCOORD,
		 SCREENRELATIVECOORD,

		

		 
		 UNUSED_DECLARED_LAST,
		 UNUSED_FORCE32 = 0x7f000000		 
		 

	};
}; 

 #pragma message("KS777: некоторые параметры для векторов уже определены в fmath  "  __FILE__ )

//!  семантика параметра 3d-вектора   
struct float3_type_e
{
	enum e
	{

		//UNDEFINED = 0,

		POSITION = float2_type_e::UNUSED_DECLARED_LAST,
		LIGHTPOSITION,
		VIEWDIRECTION,
		VIEWPOSITION,
		VIEWSIDEUP,
		VIEWUPVECTOR,
		MOUSECOORDCAMERAUNPROJECT,
		DIRECTION,



		UNUSED_DECLARED_LAST,
	    UNUSED_FORCE32 = 0x7f000000	
	}; 
}; 

//!  семантика параметра 4d-вектора 
struct float4_type_e
{
	enum e
	{
		//UNDEFINED  = 0 ,

		TIME0_X_PACKED = float3_type_e::UNUSED_DECLARED_LAST ,
		TIME0_1_PACKED,
		TIME0_2PI_PACKED,
		MOUSEBUTTONSPACKED,
		MOUSECOORDPACKED,

		VIEWDIRECTION,


		VIEWPOSITION,


		VIEWSIDEUP,
		VIEWSIDE,

		VIEWUPVECTOR,



		UNUSED_DECLARED_LAST,
	    UNUSED_FORCE32 = 0x7f000000	
	};
};

//!  семантика параметра 2d-вектора трактуемого как цвет 
struct float4_color_type_e
{
	enum e
	{
		 //UNDEFINED = 0,
		  
		 AMBIENT = float4_type_e::UNUSED_DECLARED_LAST,
		 DIFFUSE,
		 SPECULAR,
		 LIGHTSOURCE,

		 LIGHTMAP,



		 UNUSED_DECLARED_LAST,
		 UNUSED_FORCE32 = 0x7f000000	
	};
};
 
//!  семантика параметра 3x3-матрицы 
struct matrix3x3_type_e
{
	enum e 
	{
		//UNDEFINED  =  0,

		ROTATION = float4_color_type_e::UNUSED_DECLARED_LAST,


		UNUSED_DECLARED_LAST,
		UNUSED_FORCE32 = 0x7f000000		

	};
};  
  
 #pragma message("KS777: те параметры  уже определены в fmath  "  __FILE__ ) 
  
//!  семантика параметра 4x4-матрицы    
struct matrix4x4_type_e
{
	enum e
	{ 	
		//  UNDEFINED  = 0,

		  VIEWPROJECTION = matrix3x3_type_e::UNUSED_DECLARED_LAST,

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
 

 
         UNUSED_DECLARED_LAST,
		 UNUSED_FORCE32 = 0x7f000000			 
		 
	};
};
  
  
  
  
  
  
  
  
  
//---------------------------------------------------------------   
  
  }
 }
}

// end file