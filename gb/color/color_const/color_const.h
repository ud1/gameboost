/** \file
 \brief  Цветовые константы.
*/

#pragma once

#include "..\color.h"
#include "..\color_integer.h"
#include "..\color4.h"

namespace gb
{

 namespace color
 {
 
    //! \brief  Дочернее пространство от gb::color.  Цветовые константы.
   namespace color_const
   {
   
   	


//-------------------------------------------------------------------------
//                   COLOR CONST	 Color4f
//-------------------------------------------------------------------------


static const Color4f  COLOR4F_WHITE                 = Color4f( 1.0f,       1.0f,       1.0f,       1.0f );
static const Color4f  COLOR4F_BLACK                 = Color4f( 0.0f,       0.0f,       0.0f,       1.0f );
static const Color4f  COLOR4F_DIMGRAY               = Color4f( 0.329412f,  0.329412f,  0.329412f,  1.0f );
static const Color4f  COLOR4F_GRAY                  = Color4f( 0.752941f,  0.752941f,  0.752941f,  1.0f );
static const Color4f  COLOR4F_LIGHTGRAY             = Color4f( 0.658824f,  0.658824f,  0.658824f,  1.0f );
static const Color4f  COLOR4F_AQUAMARINE            = Color4f( 0.439216f,  0.858824f,  0.576471f,  1.0f );
static const Color4f  COLOR4F_BLUEVIOLET            = Color4f( 0.62352f,   0.372549f,  0.623529f,  1.0f );
static const Color4f  COLOR4F_BROWN                 = Color4f( 0.647059f,  0.164706f,  0.164706f,  1.0f );
static const Color4f  COLOR4F_CADETBLUE             = Color4f( 0.372549f,  0.623529f,  0.623529f,  1.0f );
static const Color4f  COLOR4F_CORAL                 = Color4f( 1.0f,       0.498039f,  0.0f,       1.0f );
static const Color4f  COLOR4F_CORNFLOWERBLUE        = Color4f( 0.258824f,  0.258824f,  0.435294f,  1.0f );
static const Color4f  COLOR4F_DARKGREEN             = Color4f( 0.184314f,  0.309804f,  0.184314f,  1.0f );
static const Color4f  COLOR4F_DARKOLIVEGREEN        = Color4f( 0.309804f,  0.309804f,  0.184314f,  1.0f );
static const Color4f  COLOR4F_DARKORCHID            = Color4f( 0.6f,       0.196078f,  0.8f,       1.0f );
static const Color4f  COLOR4F_DARKSLATEBLUE         = Color4f( 0.419608f,  0.137255f,  0.556863f,  1.0f );
static const Color4f  COLOR4F_DARKSLATEGRAY         = Color4f( 0.184314f,  0.309804f,  0.309804f,  1.0f );
static const Color4f  COLOR4F_DARKSLATEGREY         = Color4f( 0.184314f,  0.309804f,  0.309804f,  1.0f );
static const Color4f  COLOR4F_DARKTURQUOISE         = Color4f( 0.439216f,  0.576471f,  0.858824f,  1.0f );
static const Color4f  COLOR4F_FIREBRICK             = Color4f( 0.556863f,  0.137255f,  0.137255f,  1.0f );
static const Color4f  COLOR4F_FORESTGREEN           = Color4f( 0.137255f,  0.556863f,  0.137255f,  1.0f );
static const Color4f  COLOR4F_GOLD                  = Color4f( 0.8f,       0.498039f,  0.196078f,  1.0f );
static const Color4f  COLOR4F_GOLDENROD             = Color4f( 0.858824f,  0.858824f,  0.439216f,  1.0f );
static const Color4f  COLOR4F_GREENYELLOW           = Color4f( 0.576471f,  0.858824f,  0.439216f,  1.0f );
static const Color4f  COLOR4F_INDIAN                = Color4f( 0.309804f,  0.184314f,  0.184314f,  1.0f );
static const Color4f  COLOR4F_KHAKI                 = Color4f( 0.623529f,  0.623529f,  0.372549f,  1.0f );
static const Color4f  COLOR4F_LIGHTBLUE             = Color4f( 0.74902f,   0.847059f,  0.847059f,  1.0f );
static const Color4f  COLOR4F_LIGHTSTEELBLUE        = Color4f( 0.560784f,  0.560784f,  0.737255f,  1.0f );
static const Color4f  COLOR4F_LIMEGREEN             = Color4f( 0.196078f,  0.8f,       0.196078f,  1.0f );
static const Color4f  COLOR4F_MAROON                = Color4f( 0.556863f,  0.137255f,  0.419608f,  1.0f );
static const Color4f  COLOR4F_MEDIUMAQUAMARINE      = Color4f( 0.196078f,  0.8f,       0.6f,       1.0f );
static const Color4f  COLOR4F_MEDIUMBLUE            = Color4f( 0.196078f,  0.196078f,  0.8f,       1.0f );
static const Color4f  COLOR4F_MEDIUMFORESTGREEN     = Color4f( 0.419608f,  0.556863f,  0.137255f,  1.0f );
static const Color4f  COLOR4F_MEDIUMGOLDENROD       = Color4f( 0.917647f,  0.917647f,  0.678431f,  1.0f );
static const Color4f  COLOR4F_MEDIUMORCHID          = Color4f( 0.576471f,  0.439216f,  0.858824f,  1.0f );
static const Color4f  COLOR4F_MEDIUMSEAGREEN        = Color4f( 0.258824f,  0.435294f,  0.258824f,  1.0f );
static const Color4f  COLOR4F_MEDIUMSLATEBLUE       = Color4f( 0.498039f,  0.0f,       1.0f,       1.0f );
static const Color4f  COLOR4F_MEDIUMSPRINGGREEN     = Color4f( 0.498039f,  1.0f,       0.0f,       1.0f );
static const Color4f  COLOR4F_MEDIUMTURQUOISE       = Color4f( 0.439216f,  0.858824f,  0.858824f,  1.0f );
static const Color4f  COLOR4F_MEDIUMVIOLET          = Color4f( 0.858824f,  0.439216f,  0.576471f,  1.0f );
static const Color4f  COLOR4F_MIDNIGHTBLUE          = Color4f( 0.184314f,  0.184314f,  0.309804f,  1.0f );
static const Color4f  COLOR4F_NAVY                  = Color4f( 0.137255f,  0.137255f,  0.556863f,  1.0f );
static const Color4f  COLOR4F_NAVYBLUE              = Color4f( 0.137255f,  0.137255f,  0.556863f,  1.0f );
static const Color4f  COLOR4F_ORANGE                = Color4f( 1.0f,       0.5f,       0.0f,       1.0f );
static const Color4f  COLOR4F_ORANGERED             = Color4f( 1.0f,       0.25f,      0.0f,       1.0f );
static const Color4f  COLOR4F_ORCHID                = Color4f( 0.858824f,  0.439216f,  0.858824f,  1.0f );
static const Color4f  COLOR4F_PALEGREEN             = Color4f( 0.560784f,  0.737255f,  0.560784f,  1.0f );
static const Color4f  COLOR4F_PINK                  = Color4f( 0.737255f,  0.560784f,  0.560784f,  1.0f );
static const Color4f  COLOR4F_PLUM                  = Color4f( 0.917647f,  0.678431f,  0.917647f,  1.0f );
static const Color4f  Color4fALMON                  = Color4f( 0.435294f,  0.258824f,  0.258824f,  1.0f );
static const Color4f  Color4fEAGREEN                = Color4f( 0.137255f,  0.556863f,  0.419608f,  1.0f );
static const Color4f  Color4fIENNA                  = Color4f( 0.556863f,  0.419608f,  0.137255f,  1.0f );
static const Color4f  Color4fKYBLUE                 = Color4f( 0.196078f,  0.6f,       0.8f,       1.0f );
static const Color4f  Color4fLATEBLUE               = Color4f( 0.0f,       0.498039f,  1.0f,       1.0f );
static const Color4f  Color4fPRINGGREEN             = Color4f( 0.0f,       1.0f,       0.498039f,  1.0f );
static const Color4f  Color4fTEELBLUE               = Color4f( 0.137255f,  0.419608f,  0.556863f,  1.0f );
static const Color4f  COLOR4F_TAN                   = Color4f( 0.858824f,  0.576471f,  0.439216f,  1.0f );
static const Color4f  COLOR4F_THISTLE               = Color4f( 0.847059f,  0.74902f,   0.847059f,  1.0f );
static const Color4f  COLOR4F_TURQUOISE             = Color4f( 0.678431f,  0.917647f,  0.917647f,  1.0f );
static const Color4f  COLOR4F_VIOLET                = Color4f( 0.309804f,  0.184314f,  0.309804f,  1.0f );
static const Color4f  COLOR4F_VIOLETRED             = Color4f( 0.8f,       0.196078f,  0.6f,       1.0f );
static const Color4f  COLOR4F_WHEAT                 = Color4f( 0.847059f,  0.847059f,  0.74902f,   1.0f );
static const Color4f  COLOR4F_YELLOWGREEN           = Color4f( 0.6f,       0.8f,       0.196078f,  1.0f );
static const Color4f  Color4fUMMERSKY               = Color4f( 0.22f,      0.69f,      0.87f,      1.0f );
static const Color4f  COLOR4F_RICHBLUE              = Color4f( 0.35f,      0.35f,      0.67f,      1.0f );
static const Color4f  COLOR4F_BRASS                 = Color4f( 0.71f,      0.65f,      0.26f,      1.0f );
static const Color4f  COLOR4F_COPPER                = Color4f( 0.72f,      0.45f,      0.20f,      1.0f );
static const Color4f  COLOR4F_BRONZE                = Color4f( 0.55f,      0.47f,      0.14f,      1.0f );
static const Color4f  COLOR4F_BRONZE2               = Color4f( 0.65f,      0.49f,      0.24f,      1.0f );
static const Color4f  Color4fILVER                  = Color4f( 0.90f,      0.91f,      0.98f,      1.0f );
static const Color4f  COLOR4F_BRIGHTGOLD            = Color4f( 0.85f,      0.85f,      0.10f,      1.0f );
static const Color4f  COLOR4F_OLDGOLD               = Color4f( 0.81f,      0.71f,      0.23f,      1.0f );
static const Color4f  COLOR4F_FELDSPAR              = Color4f( 0.82f,      0.57f,      0.46f,      1.0f );
static const Color4f  COLOR4F_QUARTZ                = Color4f( 0.85f,      0.85f,      0.95f,      1.0f );
static const Color4f  COLOR4F_NEONPINK              = Color4f( 1.00f,      0.43f,      0.78f,      1.0f );
static const Color4f  COLOR4F_DARKPURPLE            = Color4f( 0.53f,      0.12f,      0.47f,      1.0f );
static const Color4f  COLOR4F_NEONBLUE              = Color4f( 0.30f,      0.30f,      1.00f,      1.0f );
static const Color4f  COLOR4F_COOLCOPPER            = Color4f( 0.85f,      0.53f,      0.10f,      1.0f );
static const Color4f  COLOR4F_MANDARINORANGE        = Color4f( 0.89f,      0.47f,      0.20f,      1.0f );
static const Color4f  COLOR4F_LIGHTWOOD             = Color4f( 0.91f,      0.76f,      0.65f,      1.0f );
static const Color4f  COLOR4F_MEDIUMWOOD            = Color4f( 0.65f,      0.50f,      0.39f,      1.0f );
static const Color4f  COLOR4F_DARKWOOD              = Color4f( 0.52f,      0.37f,      0.26f,      1.0f );
static const Color4f  Color4fPICYPINK               = Color4f( 1.00f,      0.11f,      0.68f,      1.0f );
static const Color4f  Color4fEMISWEETCHOC           = Color4f( 0.42f,      0.26f,      0.15f,      1.0f );
static const Color4f  COLOR4F_BAKERSCHOC            = Color4f( 0.36f,      0.20f,      0.09f,      1.0f );
static const Color4f  COLOR4F_FLESH                 = Color4f( 0.96f,      0.80f,      0.69f,      1.0f );
static const Color4f  COLOR4F_NEWTAN                = Color4f( 0.92f,      0.78f,      0.62f,      1.0f );
static const Color4f  COLOR4F_NEWMIDNIGHTBLUE       = Color4f( 0.00f,      0.00f,      0.61f,      1.0f );
static const Color4f  COLOR4F_VERYDARKBROWN         = Color4f( 0.35f,      0.16f,      0.14f,      1.0f );
static const Color4f  COLOR4F_DARKBROWN             = Color4f( 0.36f,      0.25f,      0.20f,      1.0f );
static const Color4f  COLOR4F_DARKTAN               = Color4f( 0.59f,      0.41f,      0.31f,      1.0f );
static const Color4f  COLOR4F_GREENCOPPER           = Color4f( 0.32f,      0.49f,      0.46f,      1.0f );
static const Color4f  COLOR4F_DKGREENCOPPER         = Color4f( 0.29f,      0.46f,      0.43f,      1.0f );
static const Color4f  COLOR4F_DUSTYROSE             = Color4f( 0.52f,      0.39f,      0.39f,      1.0f );
static const Color4f  COLOR4F_HUNTERSGREEN          = Color4f( 0.13f,      0.37f,      0.31f,      1.0f );
static const Color4f  Color4fCARLET                 = Color4f( 0.55f,      0.09f,      0.09f,      1.0f );
static const Color4f  COLOR4F_MEDIUMPURPLE          = Color4f( 0.73f,      0.16f,      0.96f,      1.0f );
static const Color4f  COLOR4F_LIGHTPURPLE           = Color4f( 0.87f,      0.58f,      0.98f,      1.0f );
static const Color4f  COLOR4F_VERYLIGHTPURPLE       = Color4f( 0.94f,      0.81f,      0.99f,      1.0f );
static const Color4f  COLOR4F_GREEN                 = Color4f( 0.0f,       0.5f,       0.0f,       1.0f );
static const Color4f  COLOR4F_OLIVE                 = Color4f( 0.5f,       0.5f,       1.0f,       1.0f );
static const Color4f  COLOR4F_PURPLE                = Color4f( 1.0f,       0.0f,       1.0f,       1.0f );
static const Color4f  COLOR4F_TEAL                  = Color4f( 0.0f,       0.5f,       0.5f,       1.0f );
static const Color4f  COLOR4F_RED                   = Color4f( 1.0f,       0.0f,       0.0f,       1.0f );
static const Color4f  COLOR4F_LIME                  = Color4f( 0.0f,       1.0f,       0.0f,       1.0f );
static const Color4f  COLOR4F_YELLOW                = Color4f( 1.0f,       1.0f,       0.0f,       1.0f );
static const Color4f  COLOR4F_BLUE                  = Color4f( 0.0f,       0.0f,       1.0f,       1.0f );
static const Color4f  COLOR4F_FUCHSIA               = Color4f( 1.0f,       0.0f,       1.0f,       1.0f );
static const Color4f  COLOR4F_AQUA                  = Color4f( 0.0f,       1.0f,       1.0f,       1.0f );




//-------------------------------------------------------------------------
//                   COLOR CONST	 uicolor32_t
//-------------------------------------------------------------------------

static const color32_t      CUICOLOR_ALICEBLUE        = 0xFFF0F8FF;
static const color32_t      CUICOLOR_ANTIQUEWHITE     = 0xFFFAEBD7;
static const color32_t      CUICOLOR_AQUA             = 0xFF00FFFF;
static const color32_t      CUICOLOR_AQUAMARINE       = 0xFF7FFFD4;
static const color32_t      CUICOLOR_AZURE            = 0xFFF0FFFF;
static const color32_t      CUICOLOR_BEIGE            = 0xFFF5F5DC;
static const color32_t      CUICOLOR_BISQUE           = 0xFFFFE4C4;
static const color32_t      CUICOLOR_BLACK            = 0xFF000000;
static const color32_t      CUICOLOR_BLANCHEDALMOND   = 0xFFFFEBCD;
static const color32_t      CUICOLOR_BLUE             = 0xFF0000FF;
static const color32_t      CUICOLOR_BLUEVIOLET       = 0xFF8A2BE2;
static const color32_t      CUICOLOR_BROWN            = 0xFFA52A2A;
static const color32_t      CUICOLOR_BURLYWOOD        = 0xFFDEB887;
static const color32_t      CUICOLOR_CADETBLUE        = 0xFF5F9EA0;
static const color32_t      CUICOLOR_CHARTREUSE       = 0xFF7FFF00;
static const color32_t      CUICOLOR_CHOCOLATE        = 0xFFD2691E;
static const color32_t      CUICOLOR_CORAL            = 0xFFFF7F50;
static const color32_t      CUICOLOR_CORNFLOWERBLUE   = 0xFF6495ED;
static const color32_t      CUICOLOR_CORNSILK         = 0xFFFFF8DC;
static const color32_t      CUICOLOR_CRIMSON          = 0xFFDC143C;
static const color32_t      CUICOLOR_CYAN             = 0xFF00FFFF;
static const color32_t      CUICOLOR_DARKBLUE         = 0xFF00008B;
static const color32_t      CUICOLOR_DARKCYAN         = 0xFF008B8B;
static const color32_t      CUICOLOR_DARKGOLDENROD    = 0xFFB8860B;
static const color32_t      CUICOLOR_DARKGRAY         = 0xFFA9A9A9;
static const color32_t      CUICOLOR_DARKGREEN        = 0xFF006400;
static const color32_t      CUICOLOR_DARKKHAKI        = 0xFFBDB76B;
static const color32_t      CUICOLOR_DARKMAGENTA      = 0xFF8B008B;
static const color32_t      CUICOLOR_DARKOLIVEGREEN   = 0xFF556B2F;
static const color32_t      CUICOLOR_DARKORANGE       = 0xFFFF8C00;
static const color32_t      CUICOLOR_DARKORCHID       = 0xFF9932CC;
static const color32_t      CUICOLOR_DARKRED          = 0xFF8B0000;
static const color32_t      CUICOLOR_DARKSALMON       = 0xFFE9967A;
static const color32_t      CUICOLOR_DARKSEAGREEN     = 0xFF8FBC8B;
static const color32_t      CUICOLOR_DARKSLATEBLUE    = 0xFF483D8B;
static const color32_t      CUICOLOR_DARKSLATEGRAY    = 0xFF2F4F4F;
static const color32_t      CUICOLOR_DARKTURQUOISE    = 0xFF00CED1;
static const color32_t      CUICOLOR_DARKVIOLET       = 0xFF9400D3;
static const color32_t      CUICOLOR_DEEPPINK         = 0xFFFF1493;
static const color32_t      CUICOLOR_DEEPSKYBLUE      = 0xFF00BFFF;
static const color32_t      CUICOLOR_DIMGRAY          = 0xFF696969;
static const color32_t      CUICOLOR_DODGERBLUE       = 0xFF1E90FF;
static const color32_t      CUICOLOR_FIREBRICK        = 0xFFB22222;
static const color32_t      CUICOLOR_FLORALWHITE      = 0xFFFFFAF0;
static const color32_t      CUICOLOR_FORESTGREEN      = 0xFF228B22;
static const color32_t      CUICOLOR_FUCHSIA          = 0xFFFF00FF;
static const color32_t      CUICOLOR_GAINSBORO        = 0xFFDCDCDC;
static const color32_t      CUICOLOR_GHOSTWHITE       = 0xFFF8F8FF;
static const color32_t      CUICOLOR_GOLD             = 0xFFFFD700;
static const color32_t      CUICOLOR_GOLDENROD        = 0xFFDAA520;
static const color32_t      CUICOLOR_GRAY             = 0xFF808080;
static const color32_t      CUICOLOR_GREEN            = 0xFF008000;
static const color32_t      CUICOLOR_GREENYELLOW      = 0xFFADFF2F;
static const color32_t      CUICOLOR_GROW             = 0xFF808080;
static const color32_t      CUICOLOR_HONEYDEW         = 0xFFF0FFF0;
static const color32_t      CUICOLOR_HOTPINK          = 0xFFFF69B4;
static const color32_t      CUICOLOR_INDIANRED        = 0xFFCD5C5C;
static const color32_t      CUICOLOR_INDIGO           = 0xFF4B0082;
static const color32_t      CUICOLOR_IVORY            = 0xFFFFFFF0;
static const color32_t      CUICOLOR_KHAKI            = 0xFFF0E68C;
static const color32_t      CUICOLOR_LAVENDER         = 0xFFE6E6FA;
static const color32_t      CUICOLOR_LAVENDERBLUSH    = 0xFFFFF0F5;
static const color32_t      CUICOLOR_LAWNGREEN        = 0xFF7CFC00;
static const color32_t      CUICOLOR_LEMONCHIFFON     = 0xFFFFFACD;
static const color32_t      CUICOLOR_LIGHTBLUE        = 0xFFADD8E6;
static const color32_t      CUICOLOR_LIGHTCORAL       = 0xFFF08080;
static const color32_t      CUICOLOR_LIGHTCYAN        = 0xFFE0FFFF;
static const color32_t      CUICOLOR_LIGHTGOLDENRODYELLOW = 0xFFFAFAD2;
static const color32_t      CUICOLOR_LIGHTGRAY        = 0xFFD3D3D3;
static const color32_t      CUICOLOR_LIGHTGREEN       = 0xFF90EE90;
static const color32_t      CUICOLOR_LIGHTPINK        = 0xFFFFB6C1;
static const color32_t      CUICOLOR_LIGHTSALMON      = 0xFFFFA07A;
static const color32_t      CUICOLOR_LIGHTSEAGREEN    = 0xFF20B2AA;
static const color32_t      CUICOLOR_LIGHTSKYBLUE     = 0xFF87CEFA;
static const color32_t      CUICOLOR_LIGHTSLATEGRAY   = 0xFF778899;
static const color32_t      CUICOLOR_LIGHTSTEELBLUE   = 0xFFB0C4DE;
static const color32_t      CUICOLOR_LIGHTYELLOW      = 0xFFFFFFE0;
static const color32_t      CUICOLOR_LIME             = 0xFF00FF00;
static const color32_t      CUICOLOR_LIMEGREEN        = 0xFF32CD32;
static const color32_t      CUICOLOR_LINEN            = 0xFFFAF0E6;
static const color32_t      CUICOLOR_MAGENTA          = 0xFFFF00FF;
static const color32_t      CUICOLOR_MAROON           = 0xFF800000;
static const color32_t      CUICOLOR_MEDIUMAQUAMARINE     = 0xFF66CDAA;
static const color32_t      CUICOLOR_MEDIUMBLUE           = 0xFF0000CD;
static const color32_t      CUICOLOR_MEDIUMORCHID         = 0xFFBA55D3;
static const color32_t      CUICOLOR_MEDIUMPURPLE         = 0xFF9370DB;
static const color32_t      CUICOLOR_MEDIUMSEAGREEN       = 0xFF3CB371;
static const color32_t      CUICOLOR_MEDIUMSLATEBLUE      = 0xFF7B68EE;
static const color32_t      CUICOLOR_MEDIUMSPRINGGREEN    = 0xFF00FA9A;
static const color32_t      CUICOLOR_MEDIUMTURQUOISE      = 0xFF48D1CC;
static const color32_t      CUICOLOR_MEDIUMVIOLETRED      = 0xFFC71585;
static const color32_t      CUICOLOR_MIDNIGHTBLUE         = 0xFF191970;
static const color32_t      CUICOLOR_MINTCREAM        = 0xFFF5FFFA;
static const color32_t      CUICOLOR_MISTYROSE        = 0xFFFFE4E1;
static const color32_t      CUICOLOR_MOCCASIN         = 0xFFFFE4B5;
static const color32_t      CUICOLOR_NAVAJOWHITE      = 0xFFFFDEAD;
static const color32_t      CUICOLOR_NAVY             = 0xFF000080;
static const color32_t      CUICOLOR_OLDLACE          = 0xFFFDF5E6;
static const color32_t      CUICOLOR_OLIVE            = 0xFF808000;
static const color32_t      CUICOLOR_OLIVEDRAB        = 0xFF6B8E23;
static const color32_t      CUICOLOR_ORANGE           = 0xFFFFA500;
static const color32_t      CUICOLOR_ORANGERED        = 0xFFFF4500;
static const color32_t      CUICOLOR_ORCHID           = 0xFFDA70D6;
static const color32_t      CUICOLOR_PALEGOLDENR      = 0xFFEEE8AA;
static const color32_t      CUICOLOR_PALEGREEN        = 0xFF98FB98;
static const color32_t      CUICOLOR_PALETURQUOI      = 0xFFAFEEEE;
static const color32_t      CUICOLOR_PALEVIOLETR      = 0xFFDB7093;
static const color32_t      CUICOLOR_PAPAYAWHIP       = 0xFFFFEFD5;
static const color32_t      CUICOLOR_PEACHPUFF        = 0xFFFFDAB9;
static const color32_t      CUICOLOR_PERU             = 0xFFCD853F;
static const color32_t      CUICOLOR_PINK             = 0xFFFFC0CB;
static const color32_t      CUICOLOR_PLUM             = 0xFFDDA0DD;
static const color32_t      CUICOLOR_POWDERBLUE       = 0xFFB0E0E6;
static const color32_t      CUICOLOR_PURPLE           = 0xFF800080;
static const color32_t      CUICOLOR_RED              = 0xFFFF0000;
static const color32_t      CUICOLOR_ROSYBROWN        = 0xFFBC8F8F;
static const color32_t      CUICOLOR_ROYALBLUE        = 0xFF4169E1;
static const color32_t      CUICOLOR_SADDLEBROWN      = 0xFF8B4513;
static const color32_t      CUICOLOR_SALMON           = 0xFFFA8072;
static const color32_t      CUICOLOR_SANDYBROWN       = 0xFFF4A460;
static const color32_t      CUICOLOR_SEAGREEN         = 0xFF2E8B57;
static const color32_t      CUICOLOR_SEASHELL         = 0xFFFFF5EE;
static const color32_t      CUICOLOR_SIENNA           = 0xFFA0522D;
static const color32_t      CUICOLOR_SILVER           = 0xFFC0C0C0;
static const color32_t      CUICOLOR_SKYBLUE          = 0xFF87CEEB;
static const color32_t      CUICOLOR_SLATEBLUE        = 0xFF6A5ACD;
static const color32_t      CUICOLOR_SLATEGRAY        = 0xFF708090;
static const color32_t      CUICOLOR_SNOW             = 0xFFFFFAFA;
static const color32_t      CUICOLOR_SPRINGGREEN      = 0xFF00FF7F;
static const color32_t      CUICOLOR_STEELBLUE        = 0xFF4682B4;
static const color32_t      CUICOLOR_TAN              = 0xFFD2B48C;
static const color32_t      CUICOLOR_TEAL             = 0xFF008080;
static const color32_t      CUICOLOR_THISTLE          = 0xFFD8BFD8;
static const color32_t      CUICOLOR_TOMATO           = 0xFFFF6347;
static const color32_t      CUICOLOR_TRANSPARENT      = 0x00FFFFFF;
static const color32_t      CUICOLOR_TURQUOISE        = 0xFF40E0D0;
static const color32_t      CUICOLOR_VIOLET           = 0xFFEE82EE;
static const color32_t      CUICOLOR_WHEAT            = 0xFFF5DEB3;
static const color32_t      CUICOLOR_WHITE            = 0xFFFFFFFF;
static const color32_t      CUICOLOR_WHITESMOKE       = 0xFFF5F5F5;
static const color32_t      CUICOLOR_YELLOW           = 0xFFFFFF00;
static const color32_t      CUICOLOR_YELLOWGREEN      = 0xFF9ACD32;


   
   
   }
 }
}
