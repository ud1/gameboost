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
	
	

	  //! \brief  Сборка из данных перспективной проекции.
	  struct PerspectiveProjData  
	  {
		float fovy;
		float aspect;
		float zn;
		float zf;

		//! \brief Извлечь проекционные данные из левосторонней перспективной матрицы .
		inline void extractProjPerspectLH(const mat44& mPerspectProjLH)
		{
			aspect = mPerspectProjLH._22/mPerspectProjLH._11;
			fovy   = 2.0f  * atan(1.0f/mPerspectProjLH._22);
			zn = -mPerspectProjLH._43/mPerspectProjLH._33; 
			zf =  mPerspectProjLH._43/(1.0f-mPerspectProjLH._33);
		}



	  };

	
	
	
	
	}
}
