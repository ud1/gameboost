/** \file
 \brief  Определение имён  семантик
 
 
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
  
  
  


  //*** сделать семантики (такие есть в fx от нвидии)
//	string resourcename = "nvlobby_cube_mipmap.dds";
	//string resourcetype = "cube";
  //* ДОБАВИТЬ   FLOAT_BUMPHEIGHT , BUMPNESS
 
 
//
///  FLOAT  (55)     
//

static const int  FLOAT_COUNT  = 55;

//* \brief текущее время рендера
static const char*   FLOAT_TIME0           =   "TIME";
static const char*   FLOAT_TIME            =   "TIME";
static const char*   FLOAT_TIME0_X         =   "TIME0_X";

static const char*   FLOAT_COSTIME0_X      =   "COSTIME0_X";
static const char*   FLOAT_SINTIME0_X      =   "SINTIME0_X";
static const char*   FLOAT_TANTIME0_X      =   "TANTIME0_X";
static const char*   FLOAT_TIME0_1         =   "TIME0_1";
static const char*   FLOAT_COSTIME0_1      =   "COSTIME0_1";
static const char*   FLOAT_SINTIME0_1      =   "SINTIME0_1";
static const char*   FLOAT_TANTIME0_1      =   "TANTIME0_1";
// 10

//* \brief скорость течения времени
static const char*   FLOAT_TIMESPEED        =   "TIMESPEED";

static const char*   FLOAT_TAN0_2PI         =   "TAN0_2PI";
static const char*   FLOAT_COSTIME0_2PI     =   "COSTIME0_2PI";
static const char*   FLOAT_SINTIME0_PI      =   "SINTIME0_PI";
static const char*   FLOAT_TANTIME0_2PI     =   "TANTIME0_2PI";
static const char*   FLOAT_TIMECYCLEPERIOD  =  "TIMECYCLEPERIOD";
//  16
static const char*   FLOAT_FPS                 =       "FPS";
//* \brief текущее значение задержки между кадром
static const char*   FLOAT_TIMEELAPSED         =       "TIMEELAPSED";
static const char*   FLOAT_TIMEELAPSED2        =       "ELAPSED";

static const char*   FLOAT_VIEWPORTWIDTH          =    "VIEWPORTWIDTH";
static const char*   FLOAT_VIEWPORTHEIGHT         =    "VIEWPORTHEIGHT";
static const char*   FLOAT_VIEWPORTWIDTHINVERSE   =    "VIEWPORTWIDTHINVERSE";
static const char*   FLOAT_VIEWPORTHEIGHTINVERSE  =    "VIEWPORTHEIGHTINVERSE";
// 23
static const char*   FLOAT_FOV                    =    "FOV";

static const char*   FLOAT_FARCLIPPLANE           =    "FARCLIPPLANE";
static const char*   FLOAT_FARCLIPPLANE2          =    "ZF";

static const char*   FLOAT_NEARCLIPPLANE          =    "NEARCLIPPLANE";
static const char*   FLOAT_NEARCLIPPLANE2         =    "ZN";
  //  28
static const char*   FLOAT_RANDOMFRACTION1PERPASS   =     "RANDOMFRACTION1PERPASS";
static const char*   FLOAT_RANDOMFRACTION2PERPASS   =     "RANDOMFRACTION2PERPASS";
static const char*   FLOAT_RANDOMFRACTION3PERPASS   =     "RANDOMFRACTION3PERPASS";
static const char*   FLOAT_RANDOMFRACTION4PERPASS   =     "RANDOMFRACTION4PERPASS";

static const char*   FLOAT_RANDOMFRACTION1PEREFFECT  =    "RANDOMFRACTION1PEREFFECT";
static const char*   FLOAT_RANDOMFRACTION2PEREFFECT  =    "RANDOMFRACTION2PEREFFECT";
static const char*   FLOAT_RANDOMFRACTION3PEREFFECT  =    "RANDOMFRACTION3PEREFFECT";
static const char*   FLOAT_RANDOMFRACTION4PEREFFECT  =    "RANDOMFRACTION4PEREFFECT";
//  36
static const char*   FLOAT_PASSINDEX               =     "PASSINDEX";
static const char*   FLOAT_RIGTHMOUSEBUTTON        =     "RIGTHMOUSEBUTTON";
static const char*   FLOAT_MIDDLEMOUSEBUTTON       =     "MIDDLEMOUSEBUTTON";
static const char*   FLOAT_LEFTMOUSEBUTTON         =     "LEFTMOUSEBUTTON";
static const char*   FLOAT_MOUSECOORDINATEX        =     "MOUSECOORDINATEX";
static const char*   FLOAT_MOUSECOORDINATEY        =     "MOUSECOORDINATEY";
static const char*   FLOAT_MOUSECOORDINATEXNDC     =     "MOUSECOORDINATEXNDC";
static const char*   FLOAT_MOUSECOORDINATEYNDC     =     "MOUSECOORDINATEYNDC";
static const char*   FLOAT_MODELBOUNDINGSPHERERADIUS =   "MODELBOUNDINGSPHERERADIUS";
 // 45
static const char*   FLOAT_ASPECT               =        "ASPECT";

static const char*   FLOAT_SPECULARPOWER        =        "SPECULARPOWER";
static const char*   FLOAT_SPECULARPOWER2       =        "SPECPOWER";

static const char*   FLOAT_ROTATEZ              =        "ROTATEZ";

static const char*   FLOAT_BRIGHTNESS    =   "BRIGHTNESS";
static const char*   FLOAT_BRIGHTNESS2   =   "BRIGHT";

static const char*   FLOAT_CONTRAST      =   "CONTRAST";

static const char*   FLOAT_ALPHA               =   "ALPHA";
static const char*   FLOAT_LIGTHMAPINTENSITY   =   "LIGTHMAPINTENSITY";
static const char*   FLOAT_ANIMATESPEED        =   "ANIMATESPEED";
 //  55

 
 
 
 //
 // 
 
 
 //------------------------------------------------------
 //  FLOAT2 
 //------------------------------------------------------
 
static const int     FLOAT2_COUNT  =  8;

static const char*   FLOAT2_VIEWPORTDIMENSIONS      =    "VIEWPORTDIMENSIONS";
static const char*   FLOAT2_VIEWPORTDIMENSIONSINVERSE =  "VIEWPORTDIMENSIONSINVERSE";
static const char*   FLOAT2_MOUSECOORDINATEXY        =   "MOUSECOORDINATEXY";
static const char*   FLOAT2_MOUSECOORDINATEXYNDC     =   "MOUSECOORDINATEXYNDC";

static const char*   FLOAT2_TEXCOORDOFFSET           =   "TEXCOORDOFFSET";
static const char*   FLOAT2_TEXCOORDSCALE            =   "TEXCOORDSCALE";

static const char*   FLOAT2_SCREENCOORD              =   "SCREENCOORD";
static const char*   FLOAT2_SCREENRELATIVECOORD      =   "SCREENRELATIVECOORD";
 
 //
 //

 //------------------------------------------------------
 //  FLOAT3  (14)
 //------------------------------------------------------
 
static const int     FLOAT3_COUNT  = 15; 

static const char*   FLOAT3_POSITION       =   "POSITION";
 
static const char*   FLOAT3_LIGHTPOSITION   =  "LIGHTPOSITION";
static const char*   FLOAT3_LIGHTPOSITION2  =  "LIGHTPOS";

static const char*   FLOAT3_VIEWDIRECTION   =  "VIEWDIRECTION";
static const char*   FLOAT3_VIEWDIRECTION2  =  "VIEWDIR";
static const char*   FLOAT3_VIEWDIRECTION3  =  "EYEDIR";

static const char*   FLOAT3_VIEWPOSITION    =  "VIEWPOSITION";
static const char*   FLOAT3_VIEWPOSITION2   =  "VIEWPOS";
static const char*   FLOAT3_VIEWPOSITION3   =  "EYEPOS";

static const char*   FLOAT3_VIEWSIDEUP      =  "VIEWSIDEUP";

static const char*   FLOAT3_VIEWUPVECTOR    =  "VIEWUPVECTOR";
static const char*   FLOAT3_VIEWUPVECTOR2   =  "VIEWUP";
static const char*   FLOAT3_VIEWUPVECTOR3   =  "EYEUP";

static const char*   FLOAT3_MOUSECOORDCAMERAUNPROJECT  = "MOUSECOORDCAMERAUNPROJECT";

static const char*   FLOAT3_DIRECTION   =  "DIRECTION";

 
//
//
//

//------------------------------------------------------
//   FLOAT4    (16)
//------------------------------------------------------

    static const int     FLOAT4_COUNT  = 16;
	
static const char*   FLOAT4_TIME0_X_PACKED     =  "TIME0_X_PACKED";
static const char*   FLOAT4_TIME0_1_PACKED     =  "TIME0_1_PACKED";
static const char*   FLOAT4_TIME0_2PI_PACKED   =  "TIME0_2PI_PACKED";
static const char*   FLOAT4_MOUSEBUTTONSPACKED =  "MOUSEBUTTONSPACKED";
static const char*   FLOAT4_MOUSECOORDPACKED   =  "MOUSECOORDPACKED";

static const char*   FLOAT4_VIEWDIRECTION      =  "VIEWDIRECTION";
static const char*   FLOAT4_VIEWDIRECTION2     =  "VIEWDIR";
static const char*   FLOAT4_VIEWDIRECTION3     =  "EYEDIR";

static const char*   FLOAT4_VIEWPOSITION       =  "VIEWPOSITION";
static const char*   FLOAT4_VIEWPOSITION2      =  "VIEWPOS";
static const char*   FLOAT4_VIEWPOSITION3      =  "EYEPOS";

static const char*   FLOAT4_VIEWSIDEUP         =  "VIEWSIDEUP";
static const char*   FLOAT4_VIEWSIDE           =  "VIEWSIDE";

static const char*   FLOAT4_VIEWUPVECTOR       =  "VIEWUPVECTOR";
static const char*   FLOAT4_VIEWUPVECTOR2      =  "VIEWUP";
static const char*   FLOAT4_VIEWUPVECTOR3      =  "EYEUP";



//------------------------------------------------------
//  COLOR (FLOAT4)     
//------------------------------------------------------

  static const int      COLOR_FLOAT4_COUNT  =   5;
  
static const char*   COLOR_AMBIENT            =  "AMBIENT";
static const char*   COLOR_DIFFUSE            =  "DIFFUSE";
static const char*   COLOR_SPECULAR           =  "SPECULAR";
static const char*   COLOR_LIGHTSOURCECOLOR   =  "LIGHTSOURCECOLOR";
//* \BRIEF ЦВЕТ ЛАЙТМАПЫ
static const char*   COLOR_LIGHTMAP      =  "LIGHTMAP";


 
//------------------------------------------------------
//  FLOAT4X4   
//------------------------------------------------------

  static const int      FLOAT4X4_COUNT  =  47;
  
static const char*   FLOAT4X4_VIEWPROJECTION                 =    "VIEWPROJECTION";
static const char*   FLOAT4X4_VIEWPROJECTION2                =    "VIEWPROJ";

static const char*   FLOAT4X4_VIEWPROJECTIONINVERSE          =    "VIEWPROJECTIONINVERSE";
static const char*   FLOAT4X4_VIEWPROJECTIONINVERSE2         =    "VIEWPROJINV";

static const char*   FLOAT4X4_VIEWPROJECTIONINVERSETRANSPONE  =   "VIEWPROJECTIONINVERSETRANSPONE";
static const char*   FLOAT4X4_VIEWPROJECTIONINVERSETRANSPONE2 =   "VIEWPROJINVTRANSP";

static const char*   FLOAT4X4_VIEWPROJECTIONTRANSPONE       =  "VIEWPROJECTIONTRANSPONE";
static const char*   FLOAT4X4_VIEWPROJECTIONTRANSPONE2      =  "VIEWPROJTRANSP";

 
static const char*   FLOAT4X4_VIEW                    =    "VIEW";
static const char*   FLOAT4X4_VIEWTRANSPONE           =    "VIEWTRANSPONE";
static const char*   FLOAT4X4_VIEWTRANSPONE2          =    "VIEWTRANSP";

static const char*   FLOAT4X4_VIEWINVERSE             =    "VIEWINVERSE";
static const char*   FLOAT4X4_VIEWINVERSE2            =    "VIEWINV";

static const char*   FLOAT4X4_VIEWINVERSETRANSPONE    =    "VIEWINVERSETRANSPONE";
static const char*   FLOAT4X4_VIEWINVERSETRANSPONE2   =    "VIEWINVTRANSP";
// 15 
 
 
static const char*   FLOAT4X4_PROJECTION                  =    "PROJECTION";
static const char*   FLOAT4X4_PROJECTION2                 =    "PROJ";

static const char*   FLOAT4X4_PROJECTIONINVERSE           =    "PROJECTIONINVERSE";
static const char*   FLOAT4X4_PROJECTIONINVERSE2          =    "PROJINV";

static const char*   FLOAT4X4_PROJECTIONTRANSPONE         =    "PROJECTIONTRANSPONE";
static const char*   FLOAT4X4_PROJECTIONTRANSPONE2        =    "PROJTRANSP";

static const char*   FLOAT4X4_PROJECTIONINVERSETRANSPONE  =    "PROJECTIONINVERSETRANSPONE";
static const char*   FLOAT4X4_PROJECTIONINVERSETRANSPONE2 =    "PROJINVTRANSP";
 // 23
 
static const char*   FLOAT4X4_WORLDVIEWPROJECTION                   =  "WORLDVIEWPROJECTION";
static const char*   FLOAT4X4_WORLDVIEWPROJECTION2                  =  "WORLDVIEWPROJ";

static const char*   FLOAT4X4_WORLDVIEWPROJECTIONTRANSPONE          =  "WORLDVIEWPROJECTIONTRANSPONE";
static const char*   FLOAT4X4_WORLDVIEWPROJECTIONTRANSPONE2         =  "WORLDVIEWPROJTRANSP";

static const char*   FLOAT4X4_WORLDVIEWPROJECTIONINVERSE            =  "WORLDVIEWPROJECTIONINVERSE";
static const char*   FLOAT4X4_WORLDVIEWPROJECTIONINVERSE2           =  "WORLDVIEWPROJINV";

static const char*   FLOAT4X4_WORLDVIEWPROJECTIONINVERSETRANSPONE   =  "WORLDVIEWPROJECTIONINVERSETRANSPONE";
static const char*   FLOAT4X4_WORLDVIEWPROJECTIONINVERSETRANSPONE2  =  "WORLDVIEWPROJINVTRANSP";
// 31


static const char*   FLOAT4X4_WORLD                      =  "WORLD";
static const char*   FLOAT4X4_WORLD2                     =  "TRANSFORM";
static const char*   FLOAT4X4_WORLD3                     =  "TRANSF";
static const char*   FLOAT4X4_WORLDTRANSPONE             =  "WORLDTRANSPONE";
static const char*   FLOAT4X4_WORLDTRANSPONE2            =  "WORLDTRANSP";
static const char*   FLOAT4X4_WORLDINVERSE               =  "WORLDINVERSE";
static const char*   FLOAT4X4_WORLDINVERSE2              =  "WORLDINV";
static const char*   FLOAT4X4_WORLDINVERSETRANSPONE      =  "WORLDINVERSETRANSPONE";
static const char*   FLOAT4X4_WORLDINVERSETRANSPONE2     =  "WORLDINVTRANSP";
static const char*   FLOAT4X4_WORLDVIEW                  =  "WORLDVIEW";
static const char*   FLOAT4X4_WORLDVIEWTRANSPONE         =  "WORLDVIEWTRANSPONE";
static const char*   FLOAT4X4_WORLDVIEWTRANSPONE2        =  "WORLDVIEWTRANSP";
static const char*   FLOAT4X4_WORLDVIEWINVERSE           =  "WORLDVIEWINVERSE";
static const char*   FLOAT4X4_WORLDVIEWINVERSE2          =  "WORLDVIEWINV";
static const char*   FLOAT4X4_WORLDVIEWINVERSETRANSPONE  =  "WORLDVIEWINVERSETRANSPONE";
static const char*   FLOAT4X4_WORLDVIEWINVERSETRANSPONE2 =  "WORLDVIEWINVTRANSP";

//
//
 
//------------------------------------------------------
//     TEXTURES     
//------------------------------------------------------

    static const int   TEXTURE_COUNT  = 29;
	 
//* \brief основная карта
static const char*   TXTR_DIFFUSEMAP          =   "DIFFUSEMAP";
static const char*   TXTR_DIFFUSEMAP2         =   "DIFFUSE";
static const char*   TXTR_DIFFUSEMAP3         =   "DIFFUSETEXTURE";
//* \brief собственно нормалмапа
static const char*   TXTR_NORMALMAP         =     "NORMALMAP";
static const char*   TXTR_NORMALMAP2        =     "NORMAL";
static const char*   TXTR_NORMALMAP3        =     "NORMALTEXTURE";
//* \brief карта самосвечения
static const char*   TXTR_SELFILUMINATIONMAP   =  "SELFILUMINATIONMAP";
static const char*   TXTR_SELFILUMINATIONMAP2  =  "SELFILUMINATION";
static const char*   TXTR_SELFILUMINATIONMAP3  =  "SELFILUMIN";
static const char*   TXTR_SELFILUMINATIONMAP4  =  "ILUMINTEXTURE";
//* \brief карта интенсивности отражения
static const char*   TXTR_REFLECTIONMAP     =       "REFLECTIONMAP";
static const char*   TXTR_REFLECTIONMAP2    =       "REFLECTION";
static const char*   TXTR_REFLECTIONMAP3    =       "REFLECTIONTEXTURE";
//* \brief карта рельефности
static const char*   TXTR_BUMPMAP           =     "BUMPMAP";
static const char*   TXTR_BUMPMAP2          =     "BUMP";
static const char*   TXTR_BUMPMAP3          =     "BUMPTEXTURE";
//* \brief  собственно лайтмап
static const char*   TXTR_LIGHTMAP          =     "LIGHTMAP";
static const char*   TXTR_LIGHTMAP2         =     "LIGHT";
static const char*   TXTR_LIGHTMAP3         =     "LIGHTTEXTURE";
//* \brief карта высоты
static const char*   TXTR_HEIGHTMAP         =     "HEIGHTMAP";
static const char*   TXTR_HEIGHTMAP2        =     "HEIGHT";
static const char*   TXTR_HEIGHTMAP3        =     "HEIGHTTEXTURE";
//* \brief карта интенсивности блика
static const char*   TXTR_SPECULARMAP       =     "SPECULARMAP";
static const char*   TXTR_SPECULARMAP2      =     "SPECULAR";
static const char*   TXTR_SPECULARMAP3      =     "SPECULARTEXTURE";
//* \brief кубическая карта окружения
static const char*    TXTR_ENVIRMAP      =    "ENVIRMAP";
static const char*    TXTR_ENVIRMAP2     =    "ENVIRONMENT";
static const char*    TXTR_ENVIRMAP3     =    "ENVIR";
static const char*    TXTR_ENVIRMAP4     =    "ENVIRONMENTTEXTURE";
 
 
 
//

//
// STRINGS	   (5)
// 
     #define  STRING_COUNT   6
static const char*   STRING_FILENAME       =    "FILENAME";
static const char*   STRING_MODELDATA      =    "MODELDATA"
static const char*   STRING_RESOURCENAME   =    "RESOURCENAME";


static const char*   STRING_RESOURCEID     =    "RESOURCEID";
static const char*   STRING_PASSINFO       =    "PASSINFO";
static const char*   STRING_RESOURCETYPE   =	 "RESOURCETYPE";


 
 
 
  
//---------------------------------------------------------------   
  
  }
 }
}

// end file