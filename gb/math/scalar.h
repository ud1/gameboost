/** \file
* \brief Операции с   float/double
*
*
*
*
*/

#pragma once

#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdexcept>

#include <gb/base/Constants.h>

namespace gb 
{

  namespace math
  {
  
    /** \brief  Операции  с  вещественными типами  (float/double).  */
    namespace scalar
	{
	

		// Константы добавлять и брать в gb/base/Constants.h

// 	static const float CPI       = 3.1415926536f; ///<   PI
// 	static const float C1BYPI    = 0.3183098862f; ///<   1/PI	
	
// 	static const float C2PI         =  6.283185307f; ///<  	2pi
// 	static const float CPIDIV2      =  1.570796326f; ///<   pi/2
// 	static const float CPIDIV4      =  0.785398163f; ///<   pi/4
// 	static const float CPIDIV6      =  0.523598776f; ///<   pi/6
// 
// 	static const float CPIDIV180    =  0.017453292f; ///<   pi/180
// 	static const float C180DIVPI    =  57.29577951f; ///<   180/pi
// 
// 	static const float C3PIDIV4     = 2.35619449f;   ///<   3/4 pi
// 	static const float CINV2PI      = 0.159154943f;  ///<   1/(2pi)
// 	static const float CINV360      = 0.002777778f;  ///<   1/360
// 	static const float C180         = 180.0f;
// 	static const float C360         = 360.0f;
// 	static const float CONEHALF     = 0.5f;
// 	static const float CTWO         = 2.0f;
// 	static const float CLN10        = 2.302585093f;
// 
// 	static const float CSQRT2       = 1.4142135624f; ///< sqrt(2)
// 	static const float CSQRTHALF    = 0.7071067812f; ///< sqrt(1/2)
// 	
// 	static const float CE           = 2.718281828459f; ///<  e
	
	
	/**  \brief Возвращает единицу с соответствующим знаком или ноль если параметр ноль   */
    inline float  sign (const float val) { if(val>=0.0f) return 1.0f; return -1.0f; };

	inline float sincos(const float a, float& outSin, float& outCos) {  outSin = sin(a); outCos = cos(a); };
	
    #if defined (_MSC_VER)	
	/** \brief ассемблерный способ полученить синус и косинус */
	inline void sincosAsm (float a, float& s, float& c) {
		__asm  {
			fld a;
			fsincos;
			mov eax, [c];
			fstp [eax];
			mov eax, [s];
			fstp [eax];  
			};
	};
	#endif
	
	/** \brief Вычислить арк котангенс */
    inline float arccot(float f) //throw() 
	{ 
	   //if(0.0f==f) 
	     // throw std::runtime_error("Inv arg"); 
	   return atan(1.0f / f); 
	};
	
	/**  \brief Вычислить котангенс  */
    inline float cotan(const float f) {  return   1.0f / tanf(f); };
	
	/** \brief Угол в радианах в градусы */
	inline float radiansToDegree(float rad)  { return rad * ( 180.0f / gb::constPi <float>() ); };
	/** \brief Угол в градусах в радианы */	
	inline float degreeToRadians(float dgr)  { return dgr * (gb::constPi <float>() / 180.0f); };
	
	/**  \brief  Вычисленить линейную интерполяцию между f1 и f2 по коэф. k */
    inline float lerp(const float f1, const float f2, const float k) { return f1 + (f2 - f1) * k; };
	
	/** \brief Округление . */
	int round(float f);
	
   #if defined (_MSC_VER)

	/** \brief ассемблерный способ округления.  */
	inline int roundAsm(float a) 
	{
	   register int retval;
		 __asm fld a
		 __asm fistp retval
			   return retval;
	};
	#endif
	
	/** \brief Проверка на корректное значение */
	inline bool check(float f) 
	{
       if( f == 0.0f ) return true;
       if( (f < FLT_MAX) && (f > FLT_MIN) ) return true;
	       return false;
    };
	
	
	
	
	}
	
  }

}

// end file