/**  \file
 \brief ??????


*/

#pragma once

#ifndef __GB_FMATH_H__
    #error НЕ ВКЛЮЧАЙТЕ ЭТОТ ФАЙЛ. ВКЛЮЧАЙТЕ:   #include <gb/fmath/math.h>  
#endif


namespace gb 
{

	namespace fmath
	{
	
#pragma message("NEED RENAME  "   __FILE__ )

	/** \brief  Углы Элера. Сборка углов поворота по всем трём осям. */
	class EulerAngles {
	public:
		float yaw;    ///<   Yaw around the y-axis, in radians. 
		float pitch;  ///<   Pitch around the x-axis, in radians.
		float roll;   ///<   Roll around the z-axis, in radians.
 
		inline EulerAngles() {}
		inline EulerAngles(const EulerAngles& ea  ) {yaw=ea.yaw; pitch=ea.pitch; roll=ea.roll; };
		inline EulerAngles(float fYaw, float fPitch, float fRoll) { yaw=fYaw;  pitch=fPitch;  roll=fRoll; };
 


	};



	
	
	
	
	
	
	
	
	
	}
}
